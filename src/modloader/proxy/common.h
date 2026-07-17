#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

HRESULT WINAPI proxy_DllCanUnloadNow(void);
HRESULT WINAPI proxy_DllGetClassObject(REFCLSID class_id, REFIID interface_id, void **object);

#ifdef __cplusplus
}
#endif
