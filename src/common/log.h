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

bool ml_log_level_parse(const char *value, ml_log_level_t *level);
const wchar_t *ml_log_level_name(ml_log_level_t level);
void ml_log_set_level(ml_log_level_t level);
ml_log_level_t ml_log_get_level(void);
bool ml_log_enabled(ml_log_level_t level);
void ml_log_vwrite(ml_log_level_t level, const wchar_t *component,
                   const wchar_t *format, va_list args);
void ml_log_write(ml_log_level_t level, const wchar_t *component,
                  const wchar_t *format, ...);

#define ML_LOG_TRACE(component, ...) ml_log_write(ML_LOG_LEVEL_TRACE, (component), __VA_ARGS__)
#define ML_LOG_DEBUG(component, ...) ml_log_write(ML_LOG_LEVEL_DEBUG, (component), __VA_ARGS__)
#define ML_LOG_INFO(component, ...) ml_log_write(ML_LOG_LEVEL_INFO, (component), __VA_ARGS__)
#define ML_LOG_WARN(component, ...) ml_log_write(ML_LOG_LEVEL_WARN, (component), __VA_ARGS__)
#define ML_LOG_ERROR(component, ...) ml_log_write(ML_LOG_LEVEL_ERROR, (component), __VA_ARGS__)

#ifdef __cplusplus
}
#endif
