#include "common.h"

#include "dinput8.h"
#include "winhttp.h"

#include <shlwapi.h>

static bool proxy_is_named(const wchar_t *name) {
    HMODULE module;
    wchar_t path[MAX_PATH];
    if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                            (LPCWSTR)proxy_DllCanUnloadNow, &module)) return false;
    if (GetModuleFileNameW(module, path, MAX_PATH) == 0) return false;
    return lstrcmpiW(PathFindFileNameW(path), name) == 0;
}

HRESULT WINAPI proxy_DllCanUnloadNow(void) {
    if (proxy_is_named(L"dinput8.dll")) return dinput8_DllCanUnloadNow();
    if (proxy_is_named(L"winhttp.dll")) return winhttp_DllCanUnloadNow();
    return E_NOINTERFACE;
}

HRESULT WINAPI proxy_DllGetClassObject(REFCLSID class_id, REFIID interface_id, void **object) {
    if (proxy_is_named(L"dinput8.dll")) return dinput8_DllGetClassObject(class_id, interface_id, object);
    if (proxy_is_named(L"winhttp.dll")) return winhttp_DllGetClassObject(class_id, interface_id, object);
    return E_NOINTERFACE;
}
