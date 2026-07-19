#pragma once

#include <stdbool.h>
#include <stdarg.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ml_log_level_e {
    ML_LOG_LEVEL_TRACE = 0,
    ML_LOG_LEVEL_DEBUG,
    ML_LOG_LEVEL_INFO,
    ML_LOG_LEVEL_WARN,
    ML_LOG_LEVEL_ERROR,
    ML_LOG_LEVEL_OFF
} ml_log_level_t;

extern volatile ml_log_level_t current_level;

bool ml_log_level_parse(const char *value, ml_log_level_t *level);
const wchar_t *ml_log_level_name(ml_log_level_t level);
void ml_log_enable_file(const wchar_t *path);
void ml_log_enable_console();
void ml_log_set_level(ml_log_level_t level);
ml_log_level_t ml_log_get_level();
void ml_log_write(ml_log_level_t level, const wchar_t *component,
                  const wchar_t *format, ...);

#define ML_LOG_TRACE(component, ...) if (current_level <= ML_LOG_LEVEL_TRACE) ml_log_write(ML_LOG_LEVEL_TRACE, (component), __VA_ARGS__)
#define ML_LOG_DEBUG(component, ...) if (current_level <= ML_LOG_LEVEL_DEBUG) ml_log_write(ML_LOG_LEVEL_DEBUG, (component), __VA_ARGS__)
#define ML_LOG_INFO(component, ...) if (current_level <= ML_LOG_LEVEL_INFO) ml_log_write(ML_LOG_LEVEL_INFO, (component), __VA_ARGS__)
#define ML_LOG_WARN(component, ...) if (current_level <= ML_LOG_LEVEL_WARN) ml_log_write(ML_LOG_LEVEL_WARN, (component), __VA_ARGS__)
#define ML_LOG_ERROR(component, ...) if (current_level <= ML_LOG_LEVEL_ERROR) ml_log_write(ML_LOG_LEVEL_ERROR, (component), __VA_ARGS__)

#ifdef __cplusplus
}
#endif
