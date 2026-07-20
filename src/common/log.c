#include "log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <shlwapi.h>

#include <stdio.h>
#include <wchar.h>

volatile ml_log_level_t current_level = ML_LOG_LEVEL_INFO;
static SRWLOCK console_lock = SRWLOCK_INIT;
static SRWLOCK file_lock = SRWLOCK_INIT;
static const wchar_t *level_names_w[] = { L"TRACE", L"DEBUG", L"INFO", L"WARN", L"ERROR", L"OFF" };
static FILE *log_stream = NULL;
static bool log_console = false;

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

void ml_log_enable_file(const wchar_t *path) {
    log_stream = _wfopen(path, L"a, ccs=UTF-8");
}

void ml_log_enable_console() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);
    log_console = true;
}

void ml_log_set_level(ml_log_level_t level) {
    if (level < ML_LOG_LEVEL_TRACE || level > ML_LOG_LEVEL_OFF) return;
    current_level = level;
}

ml_log_level_t ml_log_get_level() {
    return current_level;
}

void ml_log_vwrite(ml_log_level_t level, const wchar_t *component,
                   const wchar_t *format, va_list args) {
    if (format == NULL) return;
    if (log_console) {
        FILE *stream;
        stream = level >= ML_LOG_LEVEL_WARN ? stderr : stdout;
        AcquireSRWLockExclusive(&console_lock);
        fwprintf(stream, L"%ls: ", ml_log_level_name(level));
        if (component != NULL && component[0] != L'\0') fwprintf(stream, L"[%ls] ", component);
        vfwprintf(stream, format, args);
        fputwc(L'\n', stream);
        fflush(stream);
        ReleaseSRWLockExclusive(&console_lock);
    }
    if (log_stream) {
        AcquireSRWLockExclusive(&file_lock);
        fwprintf(log_stream, L"%ls: ", ml_log_level_name(level));
        if (component != NULL && component[0] != L'\0') fwprintf(log_stream, L"[%ls] ", component);
        vfwprintf(log_stream, format, args);
        fputwc(L'\n', log_stream);
        fflush(log_stream);
        ReleaseSRWLockExclusive(&file_lock);
    }
}
