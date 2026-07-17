#include "log.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static ml_log_level_t compatibility_level_a(FILE *stream, const char **format) {
    if (strncmp(*format, "TRACE: ", 7) == 0) {
        *format += 7;
        return ML_LOG_LEVEL_TRACE;
    }
    if (strncmp(*format, "DEBUG: ", 7) == 0) {
        *format += 7;
        return ML_LOG_LEVEL_DEBUG;
    }
    if (strncmp(*format, "WARNING: ", 9) == 0) {
        *format += 9;
        return ML_LOG_LEVEL_WARN;
    }
    if (strncmp(*format, "NOTE: ", 6) == 0) {
        *format += 6;
        return ML_LOG_LEVEL_INFO;
    }
    return stream == stderr ? ML_LOG_LEVEL_ERROR : ML_LOG_LEVEL_INFO;
}

static ml_log_level_t compatibility_level_w(FILE *stream, const wchar_t **format) {
    if (wcsncmp(*format, L"TRACE: ", 7) == 0) {
        *format += 7;
        return ML_LOG_LEVEL_TRACE;
    }
    if (wcsncmp(*format, L"DEBUG: ", 7) == 0) {
        *format += 7;
        return ML_LOG_LEVEL_DEBUG;
    }
    if (wcsncmp(*format, L"WARNING: ", 9) == 0) {
        *format += 9;
        return ML_LOG_LEVEL_WARN;
    }
    if (wcsncmp(*format, L"NOTE: ", 6) == 0) {
        *format += 6;
        return ML_LOG_LEVEL_INFO;
    }
    return stream == stderr ? ML_LOG_LEVEL_ERROR : ML_LOG_LEVEL_INFO;
}

int ml_log_fprintf(FILE *stream, const char *format, ...) {
    ml_log_level_t level;
    va_list args;
    va_list count_args;
    char *message;
    wchar_t *wide;
    int length;
    int wide_length;
    if (format == NULL) return -1;
    level = compatibility_level_a(stream, &format);
    if (!ml_log_enabled(level)) return 0;
    va_start(args, format);
    va_copy(count_args, args);
    length = _vscprintf(format, count_args);
    va_end(count_args);
    if (length < 0) {
        va_end(args);
        return -1;
    }
    message = malloc((size_t)length + 1);
    if (message == NULL) {
        va_end(args);
        return -1;
    }
    vsnprintf(message, (size_t)length + 1, format, args);
    va_end(args);
    while (length > 0 && (message[length - 1] == '\n' || message[length - 1] == '\r')) message[--length] = '\0';
    wide_length = MultiByteToWideChar(CP_ACP, 0, message, -1, NULL, 0);
    if (wide_length <= 0) {
        free(message);
        return -1;
    }
    wide = malloc((size_t)wide_length * sizeof(*wide));
    if (wide == NULL || MultiByteToWideChar(CP_ACP, 0, message, -1, wide, wide_length) == 0) {
        free(wide);
        free(message);
        return -1;
    }
    ml_log_write(level, NULL, L"%ls", wide);
    free(wide);
    free(message);
    return length;
}

int ml_log_fwprintf(FILE *stream, const wchar_t *format, ...) {
    ml_log_level_t level;
    va_list args;
    int result = 0;
    bool has_newline;
    if (format == NULL) return -1;
    level = compatibility_level_w(stream, &format);
    if (!ml_log_enabled(level)) return 0;
    has_newline = format[0] != L'\0' && format[wcslen(format) - 1] == L'\n';
    AcquireSRWLockExclusive(&output_lock);
    result += fwprintf(level >= ML_LOG_LEVEL_WARN ? stderr : stdout, L"%ls: ", ml_log_level_name(level));
    va_start(args, format);
    result += vfwprintf(level >= ML_LOG_LEVEL_WARN ? stderr : stdout, format, args);
    va_end(args);
    if (!has_newline) result += fputwc(L'\n', level >= ML_LOG_LEVEL_WARN ? stderr : stdout);
    fflush(level >= ML_LOG_LEVEL_WARN ? stderr : stdout);
    ReleaseSRWLockExclusive(&output_lock);
    return result;
}
