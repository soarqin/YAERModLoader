#include "dinput8.h"
#include "log.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct dinput8_dll {
    HMODULE dll;
    FARPROC OriginalDirectInput8Create;
    FARPROC OriginalDllCanUnloadNow;
    FARPROC OriginalDllGetClassObject;
    FARPROC OriginalDllRegisterServer;
    FARPROC OriginalDllUnregisterServer;
    FARPROC OriginalGetdfDIJoystick;
} dinput8;

#if defined(__cplusplus)
extern "C" {
#endif

void *dinput8_FakeDirectInput8Create() { return (void *)dinput8.OriginalDirectInput8Create(); }
void *dinput8_FakeDllRegisterServer() { return (void *)dinput8.OriginalDllRegisterServer(); }
void *dinput8_FakeDllUnregisterServer() { return (void *)dinput8.OriginalDllUnregisterServer(); }
void *dinput8_FakeGetdfDIJoystick() { return (void *)dinput8.OriginalGetdfDIJoystick(); }

HRESULT dinput8_DllCanUnloadNow(void) {
    typedef HRESULT (STDAPICALLTYPE *function_t)(void);
    return dinput8.OriginalDllCanUnloadNow == NULL ? E_NOINTERFACE : ((function_t)dinput8.OriginalDllCanUnloadNow)();
}

HRESULT dinput8_DllGetClassObject(REFCLSID class_id, REFIID interface_id, void **object) {
    typedef HRESULT (STDAPICALLTYPE *function_t)(REFCLSID, REFIID, void **);
    return dinput8.OriginalDllGetClassObject == NULL
        ? E_NOINTERFACE
        : ((function_t)dinput8.OriginalDllGetClassObject)(class_id, interface_id, object);
}

bool load_dinput8_proxy() {
    wchar_t path[MAX_PATH], syspath[MAX_PATH];
    GetSystemDirectoryW(syspath, MAX_PATH);
    _snwprintf(path, MAX_PATH, L"%ls\\dinput8.dll", syspath);
    path[MAX_PATH - 1] = L'\0';
    dinput8.dll = LoadLibraryW(path);
    if (!dinput8.dll) {
        ML_LOG_ERROR(L"proxy", L"cannot load original dinput8.dll library");
        return false;
    }
    dinput8.OriginalDirectInput8Create = GetProcAddress(dinput8.dll, "DirectInput8Create");
    dinput8.OriginalDllCanUnloadNow = GetProcAddress(dinput8.dll, "DllCanUnloadNow");
    dinput8.OriginalDllGetClassObject = GetProcAddress(dinput8.dll, "DllGetClassObject");
    dinput8.OriginalDllRegisterServer = GetProcAddress(dinput8.dll, "DllRegisterServer");
    dinput8.OriginalDllUnregisterServer = GetProcAddress(dinput8.dll, "DllUnregisterServer");
    dinput8.OriginalGetdfDIJoystick = GetProcAddress(dinput8.dll, "GetdfDIJoystick");
    return true;
}

#if defined(__cplusplus)
}
#endif
