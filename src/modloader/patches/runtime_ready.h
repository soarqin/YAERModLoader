#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <stdbool.h>

typedef BOOL (CALLBACK *ml_runtime_ready_callback_t)(PINIT_ONCE once, PVOID parameter,
                                                      PVOID *context);

bool ml_runtime_ready_hook_install(const wchar_t *log_scope,
                                   ml_runtime_ready_callback_t callback);
bool ml_runtime_ready_hook_uninstall(const wchar_t *log_scope);
