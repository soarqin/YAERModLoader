#include "log.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>
#include <wchar.h>

static volatile LONG current_level = ML_LOG_LEVEL_INFO;
static SRWLOCK output_lock = SRWLOCK_INIT;
static const wchar_t *level_names_w[] = { L"TRACE", L"DEBUG", L"INFO", L"WARN", L"ERROR", L"OFF" };

bool ml_log_level_parse(const char *value, ml_log_level_t *level) {
    static const char *names[] = { "trace", "debug", "info", "warn", "error", "off" };
    if (value == NULL || level == NULL) return false;
    for (size_t i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
        if (_stricmp(value, names[i]) == 0) {
            *level = (ml_log_level_t)i;
            return true;
        }
    }
    return false;
}

const wchar_t *ml_log_level_name(ml_log_level_t level) {
    return level >= ML_LOG_LEVEL_TRACE && level <= ML_LOG_LEVEL_OFF ? level_names_w[level] : L"UNKNOWN";
}

void ml_log_set_level(ml_log_level_t level) {
    if (level < ML_LOG_LEVEL_TRACE || level > ML_LOG_LEVEL_OFF) return;
    InterlockedExchange(&current_level, (LONG)level);
}

ml_log_level_t ml_log_get_level(void) {
    return (ml_log_level_t)InterlockedCompareExchange(&current_level, 0, 0);
}

bool ml_log_enabled(ml_log_level_t level) {
    ml_log_level_t threshold = ml_log_get_level();
    return level >= ML_LOG_LEVEL_TRACE && level < ML_LOG_LEVEL_OFF && level >= threshold;
}

void ml_log_vwrite(ml_log_level_t level, const wchar_t *component,
                   const wchar_t *format, va_list args) {
    FILE *stream;
    if (!ml_log_enabled(level) || format == NULL) return;
    stream = level >= ML_LOG_LEVEL_WARN ? stderr : stdout;
    AcquireSRWLockExclusive(&output_lock);
    fwprintf(stream, L"%ls: ", ml_log_level_name(level));
    if (component != NULL && component[0] != L'\0') fwprintf(stream, L"[%ls] ", component);
    vfwprintf(stream, format, args);
    fputwc(L'\n', stream);
    fflush(stream);
    ReleaseSRWLockExclusive(&output_lock);
}

void ml_log_write(ml_log_level_t level, const wchar_t *component,
                  const wchar_t *format, ...) {
    va_list args;
    va_start(args, format);
    ml_log_vwrite(level, component, format, args);
    va_end(args);
}
