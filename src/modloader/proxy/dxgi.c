#include "dxgi.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

struct dxgi_dll {
    HMODULE dll;
    FARPROC OriginalApplyCompatResolutionQuirking;
    FARPROC OriginalCompatString;
    FARPROC OriginalCompatValue;
    FARPROC OriginalCreateDXGIFactory;
    FARPROC OriginalCreateDXGIFactory1;
    FARPROC OriginalCreateDXGIFactory2;
    FARPROC OriginalDXGID3D10CreateDevice;
    FARPROC OriginalDXGID3D10CreateLayeredDevice;
    FARPROC OriginalDXGID3D10GetLayeredDeviceSize;
    FARPROC OriginalDXGID3D10RegisterLayers;
    FARPROC OriginalDXGIDeclareAdapterRemovalSupport;
    FARPROC OriginalDXGIDisableVBlankVirtualization;
    FARPROC OriginalDXGIDumpJournal;
    FARPROC OriginalDXGIGetDebugInterface1;
    FARPROC OriginalDXGIReportAdapterConfiguration;
    FARPROC OriginalPIXBeginCapture;
    FARPROC OriginalPIXEndCapture;
    FARPROC OriginalPIXGetCaptureState;
    FARPROC OriginalSetAppCompatStringPointer;
    FARPROC OriginalUpdateHMDEmulationStatus;
} dxgi;

#if defined(__cplusplus)
extern "C" {
#endif

void *dxgi_FakeApplyCompatResolutionQuirking() { return (void *)dxgi.OriginalApplyCompatResolutionQuirking(); }
void *dxgi_FakeCompatString() { return (void *)dxgi.OriginalCompatString(); }
void *dxgi_FakeCompatValue() { return (void *)dxgi.OriginalCompatValue(); }
void *dxgi_FakeCreateDXGIFactory() { return (void *)dxgi.OriginalCreateDXGIFactory(); }
void *dxgi_FakeCreateDXGIFactory1() { return (void *)dxgi.OriginalCreateDXGIFactory1(); }
void *dxgi_FakeCreateDXGIFactory2() { return (void *)dxgi.OriginalCreateDXGIFactory2(); }
void *dxgi_FakeDXGID3D10CreateDevice() { return (void *)dxgi.OriginalDXGID3D10CreateDevice(); }
void *dxgi_FakeDXGID3D10CreateLayeredDevice() { return (void *)dxgi.OriginalDXGID3D10CreateLayeredDevice(); }
void *dxgi_FakeDXGID3D10GetLayeredDeviceSize() { return (void *)dxgi.OriginalDXGID3D10GetLayeredDeviceSize(); }
void *dxgi_FakeDXGID3D10RegisterLayers() { return (void *)dxgi.OriginalDXGID3D10RegisterLayers(); }
void *dxgi_FakeDXGIDeclareAdapterRemovalSupport() { return (void *)dxgi.OriginalDXGIDeclareAdapterRemovalSupport(); }
void *dxgi_FakeDXGIDisableVBlankVirtualization() { return (void *)dxgi.OriginalDXGIDisableVBlankVirtualization(); }
void *dxgi_FakeDXGIDumpJournal() { return (void *)dxgi.OriginalDXGIDumpJournal(); }
void *dxgi_FakeDXGIGetDebugInterface1() { return (void *)dxgi.OriginalDXGIGetDebugInterface1(); }
void *dxgi_FakeDXGIReportAdapterConfiguration() { return (void *)dxgi.OriginalDXGIReportAdapterConfiguration(); }
void *dxgi_FakePIXBeginCapture() { return (void *)dxgi.OriginalPIXBeginCapture(); }
void *dxgi_FakePIXEndCapture() { return (void *)dxgi.OriginalPIXEndCapture(); }
void *dxgi_FakePIXGetCaptureState() { return (void *)dxgi.OriginalPIXGetCaptureState(); }
void *dxgi_FakeSetAppCompatStringPointer() { return (void *)dxgi.OriginalSetAppCompatStringPointer(); }
void *dxgi_FakeUpdateHMDEmulationStatus() { return (void *)dxgi.OriginalUpdateHMDEmulationStatus(); }

bool load_dxgi_proxy() {
    wchar_t path[MAX_PATH], syspath[MAX_PATH];
    GetSystemDirectoryW(syspath, MAX_PATH);
    _snwprintf(path, MAX_PATH, L"%ls\\dxgi.dll", syspath);
    path[MAX_PATH - 1] = L'\0';
    dxgi.dll = LoadLibraryW(path);
    if (!dxgi.dll) {
        fprintf(stderr, "Cannot load original dxgi.dll library\n");
        return false;
    }
    dxgi.OriginalApplyCompatResolutionQuirking = GetProcAddress(dxgi.dll, "ApplyCompatResolutionQuirking");
    dxgi.OriginalCompatString = GetProcAddress(dxgi.dll, "CompatString");
    dxgi.OriginalCompatValue = GetProcAddress(dxgi.dll, "CompatValue");
    dxgi.OriginalCreateDXGIFactory = GetProcAddress(dxgi.dll, "CreateDXGIFactory");
    dxgi.OriginalCreateDXGIFactory1 = GetProcAddress(dxgi.dll, "CreateDXGIFactory1");
    dxgi.OriginalCreateDXGIFactory2 = GetProcAddress(dxgi.dll, "CreateDXGIFactory2");
    dxgi.OriginalDXGID3D10CreateDevice = GetProcAddress(dxgi.dll, "DXGID3D10CreateDevice");
    dxgi.OriginalDXGID3D10CreateLayeredDevice = GetProcAddress(dxgi.dll, "DXGID3D10CreateLayeredDevice");
    dxgi.OriginalDXGID3D10GetLayeredDeviceSize = GetProcAddress(dxgi.dll, "DXGID3D10GetLayeredDeviceSize");
    dxgi.OriginalDXGID3D10RegisterLayers = GetProcAddress(dxgi.dll, "DXGID3D10RegisterLayers");
    dxgi.OriginalDXGIDeclareAdapterRemovalSupport = GetProcAddress(dxgi.dll, "DXGIDeclareAdapterRemovalSupport");
    dxgi.OriginalDXGIDisableVBlankVirtualization = GetProcAddress(dxgi.dll, "DXGIDisableVBlankVirtualization");
    dxgi.OriginalDXGIDumpJournal = GetProcAddress(dxgi.dll, "DXGIDumpJournal");
    dxgi.OriginalDXGIGetDebugInterface1 = GetProcAddress(dxgi.dll, "DXGIGetDebugInterface1");
    dxgi.OriginalDXGIReportAdapterConfiguration = GetProcAddress(dxgi.dll, "DXGIReportAdapterConfiguration");
    dxgi.OriginalPIXBeginCapture = GetProcAddress(dxgi.dll, "PIXBeginCapture");
    dxgi.OriginalPIXEndCapture = GetProcAddress(dxgi.dll, "PIXEndCapture");
    dxgi.OriginalPIXGetCaptureState = GetProcAddress(dxgi.dll, "PIXGetCaptureState");
    dxgi.OriginalSetAppCompatStringPointer = GetProcAddress(dxgi.dll, "SetAppCompatStringPointer");
    dxgi.OriginalUpdateHMDEmulationStatus = GetProcAddress(dxgi.dll, "UpdateHMDEmulationStatus");
    return true;
}

#if defined(__cplusplus)
}
#endif
