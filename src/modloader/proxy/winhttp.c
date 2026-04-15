#include "winhttp.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

struct winhttp_dll {
    HMODULE dll;
    FARPROC OriginalDllCanUnloadNow;
    FARPROC OriginalDllGetClassObject;
    FARPROC OriginalPrivate1;
    FARPROC OriginalSvchostPushServiceGlobals;
    FARPROC OriginalWinHttpAddRequestHeaders;
    FARPROC OriginalWinHttpAddRequestHeadersEx;
    FARPROC OriginalWinHttpAutoProxySvcMain;
    FARPROC OriginalWinHttpCheckPlatform;
    FARPROC OriginalWinHttpCloseHandle;
    FARPROC OriginalWinHttpConnect;
    FARPROC OriginalWinHttpConnectionDeletePolicyEntries;
    FARPROC OriginalWinHttpConnectionDeleteProxyInfo;
    FARPROC OriginalWinHttpConnectionFreeNameList;
    FARPROC OriginalWinHttpConnectionFreeProxyInfo;
    FARPROC OriginalWinHttpConnectionFreeProxyList;
    FARPROC OriginalWinHttpConnectionGetNameList;
    FARPROC OriginalWinHttpConnectionGetProxyInfo;
    FARPROC OriginalWinHttpConnectionGetProxyList;
    FARPROC OriginalWinHttpConnectionOnlyConvert;
    FARPROC OriginalWinHttpConnectionOnlyReceive;
    FARPROC OriginalWinHttpConnectionOnlySend;
    FARPROC OriginalWinHttpConnectionSetPolicyEntries;
    FARPROC OriginalWinHttpConnectionSetProxyInfo;
    FARPROC OriginalWinHttpConnectionUpdateIfIndexTable;
    FARPROC OriginalWinHttpCrackUrl;
    FARPROC OriginalWinHttpCreateProxyResolver;
    FARPROC OriginalWinHttpCreateUrl;
    FARPROC OriginalWinHttpDetectAutoProxyConfigUrl;
    FARPROC OriginalWinHttpFreeProxyResult;
    FARPROC OriginalWinHttpFreeProxyResultEx;
    FARPROC OriginalWinHttpFreeProxySettings;
    FARPROC OriginalWinHttpFreeProxySettingsEx;
    FARPROC OriginalWinHttpFreeQueryConnectionGroupResult;
    FARPROC OriginalWinHttpGetDefaultProxyConfiguration;
    FARPROC OriginalWinHttpGetIEProxyConfigForCurrentUser;
    FARPROC OriginalWinHttpGetProxyForUrl;
    FARPROC OriginalWinHttpGetProxyForUrlEx;
    FARPROC OriginalWinHttpGetProxyForUrlEx2;
    FARPROC OriginalWinHttpGetProxyForUrlHvsi;
    FARPROC OriginalWinHttpGetProxyResult;
    FARPROC OriginalWinHttpGetProxyResultEx;
    FARPROC OriginalWinHttpGetProxySettingsEx;
    FARPROC OriginalWinHttpGetProxySettingsResultEx;
    FARPROC OriginalWinHttpGetProxySettingsVersion;
    FARPROC OriginalWinHttpGetTunnelSocket;
    FARPROC OriginalWinHttpOpen;
    FARPROC OriginalWinHttpOpenRequest;
    FARPROC OriginalWinHttpPacJsWorkerMain;
    FARPROC OriginalWinHttpProbeConnectivity;
    FARPROC OriginalWinHttpQueryAuthSchemes;
    FARPROC OriginalWinHttpQueryConnectionGroup;
    FARPROC OriginalWinHttpQueryDataAvailable;
    FARPROC OriginalWinHttpQueryHeaders;
    FARPROC OriginalWinHttpQueryHeadersEx;
    FARPROC OriginalWinHttpQueryOption;
    FARPROC OriginalWinHttpReadData;
    FARPROC OriginalWinHttpReadDataEx;
    FARPROC OriginalWinHttpReadProxySettings;
    FARPROC OriginalWinHttpReadProxySettingsHvsi;
    FARPROC OriginalWinHttpReceiveResponse;
    FARPROC OriginalWinHttpRegisterProxyChangeNotification;
    FARPROC OriginalWinHttpResetAutoProxy;
    FARPROC OriginalWinHttpSaveProxyCredentials;
    FARPROC OriginalWinHttpSendRequest;
    FARPROC OriginalWinHttpSetCredentials;
    FARPROC OriginalWinHttpSetDefaultProxyConfiguration;
    FARPROC OriginalWinHttpSetOption;
    FARPROC OriginalWinHttpSetProxySettingsPerUser;
    FARPROC OriginalWinHttpSetSecureLegacyServersAppCompat;
    FARPROC OriginalWinHttpSetStatusCallback;
    FARPROC OriginalWinHttpSetTimeouts;
    FARPROC OriginalWinHttpTimeFromSystemTime;
    FARPROC OriginalWinHttpTimeToSystemTime;
    FARPROC OriginalWinHttpUnregisterProxyChangeNotification;
    FARPROC OriginalWinHttpWebSocketClose;
    FARPROC OriginalWinHttpWebSocketCompleteUpgrade;
    FARPROC OriginalWinHttpWebSocketQueryCloseStatus;
    FARPROC OriginalWinHttpWebSocketReceive;
    FARPROC OriginalWinHttpWebSocketSend;
    FARPROC OriginalWinHttpWebSocketShutdown;
    FARPROC OriginalWinHttpWriteData;
    FARPROC OriginalWinHttpWriteProxySettings;
} winhttp;

#if defined(__cplusplus)
extern "C" {
#endif

void *winhttp_FakeDllCanUnloadNow() { return (void *)winhttp.OriginalDllCanUnloadNow(); }
void *winhttp_FakeDllGetClassObject() { return (void *)winhttp.OriginalDllGetClassObject(); }
void *winhttp_FakePrivate1() { return (void *)winhttp.OriginalPrivate1(); }
void *winhttp_FakeSvchostPushServiceGlobals() { return (void *)winhttp.OriginalSvchostPushServiceGlobals(); }
void *winhttp_FakeWinHttpAddRequestHeaders() { return (void *)winhttp.OriginalWinHttpAddRequestHeaders(); }
void *winhttp_FakeWinHttpAddRequestHeadersEx() { return (void *)winhttp.OriginalWinHttpAddRequestHeadersEx(); }
void *winhttp_FakeWinHttpAutoProxySvcMain() { return (void *)winhttp.OriginalWinHttpAutoProxySvcMain(); }
void *winhttp_FakeWinHttpCheckPlatform() { return (void *)winhttp.OriginalWinHttpCheckPlatform(); }
void *winhttp_FakeWinHttpCloseHandle() { return (void *)winhttp.OriginalWinHttpCloseHandle(); }
void *winhttp_FakeWinHttpConnect() { return (void *)winhttp.OriginalWinHttpConnect(); }
void *winhttp_FakeWinHttpConnectionDeletePolicyEntries() { return (void *)winhttp.OriginalWinHttpConnectionDeletePolicyEntries(); }
void *winhttp_FakeWinHttpConnectionDeleteProxyInfo() { return (void *)winhttp.OriginalWinHttpConnectionDeleteProxyInfo(); }
void *winhttp_FakeWinHttpConnectionFreeNameList() { return (void *)winhttp.OriginalWinHttpConnectionFreeNameList(); }
void *winhttp_FakeWinHttpConnectionFreeProxyInfo() { return (void *)winhttp.OriginalWinHttpConnectionFreeProxyInfo(); }
void *winhttp_FakeWinHttpConnectionFreeProxyList() { return (void *)winhttp.OriginalWinHttpConnectionFreeProxyList(); }
void *winhttp_FakeWinHttpConnectionGetNameList() { return (void *)winhttp.OriginalWinHttpConnectionGetNameList(); }
void *winhttp_FakeWinHttpConnectionGetProxyInfo() { return (void *)winhttp.OriginalWinHttpConnectionGetProxyInfo(); }
void *winhttp_FakeWinHttpConnectionGetProxyList() { return (void *)winhttp.OriginalWinHttpConnectionGetProxyList(); }
void *winhttp_FakeWinHttpConnectionOnlyConvert() { return (void *)winhttp.OriginalWinHttpConnectionOnlyConvert(); }
void *winhttp_FakeWinHttpConnectionOnlyReceive() { return (void *)winhttp.OriginalWinHttpConnectionOnlyReceive(); }
void *winhttp_FakeWinHttpConnectionOnlySend() { return (void *)winhttp.OriginalWinHttpConnectionOnlySend(); }
void *winhttp_FakeWinHttpConnectionSetPolicyEntries() { return (void *)winhttp.OriginalWinHttpConnectionSetPolicyEntries(); }
void *winhttp_FakeWinHttpConnectionSetProxyInfo() { return (void *)winhttp.OriginalWinHttpConnectionSetProxyInfo(); }
void *winhttp_FakeWinHttpConnectionUpdateIfIndexTable() { return (void *)winhttp.OriginalWinHttpConnectionUpdateIfIndexTable(); }
void *winhttp_FakeWinHttpCrackUrl() { return (void *)winhttp.OriginalWinHttpCrackUrl(); }
void *winhttp_FakeWinHttpCreateProxyResolver() { return (void *)winhttp.OriginalWinHttpCreateProxyResolver(); }
void *winhttp_FakeWinHttpCreateUrl() { return (void *)winhttp.OriginalWinHttpCreateUrl(); }
void *winhttp_FakeWinHttpDetectAutoProxyConfigUrl() { return (void *)winhttp.OriginalWinHttpDetectAutoProxyConfigUrl(); }
void *winhttp_FakeWinHttpFreeProxyResult() { return (void *)winhttp.OriginalWinHttpFreeProxyResult(); }
void *winhttp_FakeWinHttpFreeProxyResultEx() { return (void *)winhttp.OriginalWinHttpFreeProxyResultEx(); }
void *winhttp_FakeWinHttpFreeProxySettings() { return (void *)winhttp.OriginalWinHttpFreeProxySettings(); }
void *winhttp_FakeWinHttpFreeProxySettingsEx() { return (void *)winhttp.OriginalWinHttpFreeProxySettingsEx(); }
void *winhttp_FakeWinHttpFreeQueryConnectionGroupResult() { return (void *)winhttp.OriginalWinHttpFreeQueryConnectionGroupResult(); }
void *winhttp_FakeWinHttpGetDefaultProxyConfiguration() { return (void *)winhttp.OriginalWinHttpGetDefaultProxyConfiguration(); }
void *winhttp_FakeWinHttpGetIEProxyConfigForCurrentUser() { return (void *)winhttp.OriginalWinHttpGetIEProxyConfigForCurrentUser(); }
void *winhttp_FakeWinHttpGetProxyForUrl() { return (void *)winhttp.OriginalWinHttpGetProxyForUrl(); }
void *winhttp_FakeWinHttpGetProxyForUrlEx() { return (void *)winhttp.OriginalWinHttpGetProxyForUrlEx(); }
void *winhttp_FakeWinHttpGetProxyForUrlEx2() { return (void *)winhttp.OriginalWinHttpGetProxyForUrlEx2(); }
void *winhttp_FakeWinHttpGetProxyForUrlHvsi() { return (void *)winhttp.OriginalWinHttpGetProxyForUrlHvsi(); }
void *winhttp_FakeWinHttpGetProxyResult() { return (void *)winhttp.OriginalWinHttpGetProxyResult(); }
void *winhttp_FakeWinHttpGetProxyResultEx() { return (void *)winhttp.OriginalWinHttpGetProxyResultEx(); }
void *winhttp_FakeWinHttpGetProxySettingsEx() { return (void *)winhttp.OriginalWinHttpGetProxySettingsEx(); }
void *winhttp_FakeWinHttpGetProxySettingsResultEx() { return (void *)winhttp.OriginalWinHttpGetProxySettingsResultEx(); }
void *winhttp_FakeWinHttpGetProxySettingsVersion() { return (void *)winhttp.OriginalWinHttpGetProxySettingsVersion(); }
void *winhttp_FakeWinHttpGetTunnelSocket() { return (void *)winhttp.OriginalWinHttpGetTunnelSocket(); }
void *winhttp_FakeWinHttpOpen() { return (void *)winhttp.OriginalWinHttpOpen(); }
void *winhttp_FakeWinHttpOpenRequest() { return (void *)winhttp.OriginalWinHttpOpenRequest(); }
void *winhttp_FakeWinHttpPacJsWorkerMain() { return (void *)winhttp.OriginalWinHttpPacJsWorkerMain(); }
void *winhttp_FakeWinHttpProbeConnectivity() { return (void *)winhttp.OriginalWinHttpProbeConnectivity(); }
void *winhttp_FakeWinHttpQueryAuthSchemes() { return (void *)winhttp.OriginalWinHttpQueryAuthSchemes(); }
void *winhttp_FakeWinHttpQueryConnectionGroup() { return (void *)winhttp.OriginalWinHttpQueryConnectionGroup(); }
void *winhttp_FakeWinHttpQueryDataAvailable() { return (void *)winhttp.OriginalWinHttpQueryDataAvailable(); }
void *winhttp_FakeWinHttpQueryHeaders() { return (void *)winhttp.OriginalWinHttpQueryHeaders(); }
void *winhttp_FakeWinHttpQueryHeadersEx() { return (void *)winhttp.OriginalWinHttpQueryHeadersEx(); }
void *winhttp_FakeWinHttpQueryOption() { return (void *)winhttp.OriginalWinHttpQueryOption(); }
void *winhttp_FakeWinHttpReadData() { return (void *)winhttp.OriginalWinHttpReadData(); }
void *winhttp_FakeWinHttpReadDataEx() { return (void *)winhttp.OriginalWinHttpReadDataEx(); }
void *winhttp_FakeWinHttpReadProxySettings() { return (void *)winhttp.OriginalWinHttpReadProxySettings(); }
void *winhttp_FakeWinHttpReadProxySettingsHvsi() { return (void *)winhttp.OriginalWinHttpReadProxySettingsHvsi(); }
void *winhttp_FakeWinHttpReceiveResponse() { return (void *)winhttp.OriginalWinHttpReceiveResponse(); }
void *winhttp_FakeWinHttpRegisterProxyChangeNotification() { return (void *)winhttp.OriginalWinHttpRegisterProxyChangeNotification(); }
void *winhttp_FakeWinHttpResetAutoProxy() { return (void *)winhttp.OriginalWinHttpResetAutoProxy(); }
void *winhttp_FakeWinHttpSaveProxyCredentials() { return (void *)winhttp.OriginalWinHttpSaveProxyCredentials(); }
void *winhttp_FakeWinHttpSendRequest() { return (void *)winhttp.OriginalWinHttpSendRequest(); }
void *winhttp_FakeWinHttpSetCredentials() { return (void *)winhttp.OriginalWinHttpSetCredentials(); }
void *winhttp_FakeWinHttpSetDefaultProxyConfiguration() { return (void *)winhttp.OriginalWinHttpSetDefaultProxyConfiguration(); }
void *winhttp_FakeWinHttpSetOption() { return (void *)winhttp.OriginalWinHttpSetOption(); }
void *winhttp_FakeWinHttpSetProxySettingsPerUser() { return (void *)winhttp.OriginalWinHttpSetProxySettingsPerUser(); }
void *winhttp_FakeWinHttpSetSecureLegacyServersAppCompat() { return (void *)winhttp.OriginalWinHttpSetSecureLegacyServersAppCompat(); }
void *winhttp_FakeWinHttpSetStatusCallback() { return (void *)winhttp.OriginalWinHttpSetStatusCallback(); }
void *winhttp_FakeWinHttpSetTimeouts() { return (void *)winhttp.OriginalWinHttpSetTimeouts(); }
void *winhttp_FakeWinHttpTimeFromSystemTime() { return (void *)winhttp.OriginalWinHttpTimeFromSystemTime(); }
void *winhttp_FakeWinHttpTimeToSystemTime() { return (void *)winhttp.OriginalWinHttpTimeToSystemTime(); }
void *winhttp_FakeWinHttpUnregisterProxyChangeNotification() { return (void *)winhttp.OriginalWinHttpUnregisterProxyChangeNotification(); }
void *winhttp_FakeWinHttpWebSocketClose() { return (void *)winhttp.OriginalWinHttpWebSocketClose(); }
void *winhttp_FakeWinHttpWebSocketCompleteUpgrade() { return (void *)winhttp.OriginalWinHttpWebSocketCompleteUpgrade(); }
void *winhttp_FakeWinHttpWebSocketQueryCloseStatus() { return (void *)winhttp.OriginalWinHttpWebSocketQueryCloseStatus(); }
void *winhttp_FakeWinHttpWebSocketReceive() { return (void *)winhttp.OriginalWinHttpWebSocketReceive(); }
void *winhttp_FakeWinHttpWebSocketSend() { return (void *)winhttp.OriginalWinHttpWebSocketSend(); }
void *winhttp_FakeWinHttpWebSocketShutdown() { return (void *)winhttp.OriginalWinHttpWebSocketShutdown(); }
void *winhttp_FakeWinHttpWriteData() { return (void *)winhttp.OriginalWinHttpWriteData(); }
void *winhttp_FakeWinHttpWriteProxySettings() { return (void *)winhttp.OriginalWinHttpWriteProxySettings(); }

bool load_winhttp_proxy() {
    wchar_t path[MAX_PATH], syspath[MAX_PATH];
    GetSystemDirectoryW(syspath, MAX_PATH);
    _snwprintf(path, MAX_PATH, L"%ls\\winhttp.dll", syspath);
    path[MAX_PATH - 1] = L'\0';
    winhttp.dll = LoadLibraryW(path);
    if (!winhttp.dll) {
        fprintf(stderr, "Cannot load original winhttp.dll library\n");
        return false;
    }
    winhttp.OriginalDllCanUnloadNow = GetProcAddress(winhttp.dll, "DllCanUnloadNow");
    winhttp.OriginalDllGetClassObject = GetProcAddress(winhttp.dll, "DllGetClassObject");
    winhttp.OriginalPrivate1 = GetProcAddress(winhttp.dll, "Private1");
    winhttp.OriginalSvchostPushServiceGlobals = GetProcAddress(winhttp.dll, "SvchostPushServiceGlobals");
    winhttp.OriginalWinHttpAddRequestHeaders = GetProcAddress(winhttp.dll, "WinHttpAddRequestHeaders");
    winhttp.OriginalWinHttpAddRequestHeadersEx = GetProcAddress(winhttp.dll, "WinHttpAddRequestHeadersEx");
    winhttp.OriginalWinHttpAutoProxySvcMain = GetProcAddress(winhttp.dll, "WinHttpAutoProxySvcMain");
    winhttp.OriginalWinHttpCheckPlatform = GetProcAddress(winhttp.dll, "WinHttpCheckPlatform");
    winhttp.OriginalWinHttpCloseHandle = GetProcAddress(winhttp.dll, "WinHttpCloseHandle");
    winhttp.OriginalWinHttpConnect = GetProcAddress(winhttp.dll, "WinHttpConnect");
    winhttp.OriginalWinHttpConnectionDeletePolicyEntries = GetProcAddress(winhttp.dll, "WinHttpConnectionDeletePolicyEntries");
    winhttp.OriginalWinHttpConnectionDeleteProxyInfo = GetProcAddress(winhttp.dll, "WinHttpConnectionDeleteProxyInfo");
    winhttp.OriginalWinHttpConnectionFreeNameList = GetProcAddress(winhttp.dll, "WinHttpConnectionFreeNameList");
    winhttp.OriginalWinHttpConnectionFreeProxyInfo = GetProcAddress(winhttp.dll, "WinHttpConnectionFreeProxyInfo");
    winhttp.OriginalWinHttpConnectionFreeProxyList = GetProcAddress(winhttp.dll, "WinHttpConnectionFreeProxyList");
    winhttp.OriginalWinHttpConnectionGetNameList = GetProcAddress(winhttp.dll, "WinHttpConnectionGetNameList");
    winhttp.OriginalWinHttpConnectionGetProxyInfo = GetProcAddress(winhttp.dll, "WinHttpConnectionGetProxyInfo");
    winhttp.OriginalWinHttpConnectionGetProxyList = GetProcAddress(winhttp.dll, "WinHttpConnectionGetProxyList");
    winhttp.OriginalWinHttpConnectionOnlyConvert = GetProcAddress(winhttp.dll, "WinHttpConnectionOnlyConvert");
    winhttp.OriginalWinHttpConnectionOnlyReceive = GetProcAddress(winhttp.dll, "WinHttpConnectionOnlyReceive");
    winhttp.OriginalWinHttpConnectionOnlySend = GetProcAddress(winhttp.dll, "WinHttpConnectionOnlySend");
    winhttp.OriginalWinHttpConnectionSetPolicyEntries = GetProcAddress(winhttp.dll, "WinHttpConnectionSetPolicyEntries");
    winhttp.OriginalWinHttpConnectionSetProxyInfo = GetProcAddress(winhttp.dll, "WinHttpConnectionSetProxyInfo");
    winhttp.OriginalWinHttpConnectionUpdateIfIndexTable = GetProcAddress(winhttp.dll, "WinHttpConnectionUpdateIfIndexTable");
    winhttp.OriginalWinHttpCrackUrl = GetProcAddress(winhttp.dll, "WinHttpCrackUrl");
    winhttp.OriginalWinHttpCreateProxyResolver = GetProcAddress(winhttp.dll, "WinHttpCreateProxyResolver");
    winhttp.OriginalWinHttpCreateUrl = GetProcAddress(winhttp.dll, "WinHttpCreateUrl");
    winhttp.OriginalWinHttpDetectAutoProxyConfigUrl = GetProcAddress(winhttp.dll, "WinHttpDetectAutoProxyConfigUrl");
    winhttp.OriginalWinHttpFreeProxyResult = GetProcAddress(winhttp.dll, "WinHttpFreeProxyResult");
    winhttp.OriginalWinHttpFreeProxyResultEx = GetProcAddress(winhttp.dll, "WinHttpFreeProxyResultEx");
    winhttp.OriginalWinHttpFreeProxySettings = GetProcAddress(winhttp.dll, "WinHttpFreeProxySettings");
    winhttp.OriginalWinHttpFreeProxySettingsEx = GetProcAddress(winhttp.dll, "WinHttpFreeProxySettingsEx");
    winhttp.OriginalWinHttpFreeQueryConnectionGroupResult = GetProcAddress(winhttp.dll, "WinHttpFreeQueryConnectionGroupResult");
    winhttp.OriginalWinHttpGetDefaultProxyConfiguration = GetProcAddress(winhttp.dll, "WinHttpGetDefaultProxyConfiguration");
    winhttp.OriginalWinHttpGetIEProxyConfigForCurrentUser = GetProcAddress(winhttp.dll, "WinHttpGetIEProxyConfigForCurrentUser");
    winhttp.OriginalWinHttpGetProxyForUrl = GetProcAddress(winhttp.dll, "WinHttpGetProxyForUrl");
    winhttp.OriginalWinHttpGetProxyForUrlEx = GetProcAddress(winhttp.dll, "WinHttpGetProxyForUrlEx");
    winhttp.OriginalWinHttpGetProxyForUrlEx2 = GetProcAddress(winhttp.dll, "WinHttpGetProxyForUrlEx2");
    winhttp.OriginalWinHttpGetProxyForUrlHvsi = GetProcAddress(winhttp.dll, "WinHttpGetProxyForUrlHvsi");
    winhttp.OriginalWinHttpGetProxyResult = GetProcAddress(winhttp.dll, "WinHttpGetProxyResult");
    winhttp.OriginalWinHttpGetProxyResultEx = GetProcAddress(winhttp.dll, "WinHttpGetProxyResultEx");
    winhttp.OriginalWinHttpGetProxySettingsEx = GetProcAddress(winhttp.dll, "WinHttpGetProxySettingsEx");
    winhttp.OriginalWinHttpGetProxySettingsResultEx = GetProcAddress(winhttp.dll, "WinHttpGetProxySettingsResultEx");
    winhttp.OriginalWinHttpGetProxySettingsVersion = GetProcAddress(winhttp.dll, "WinHttpGetProxySettingsVersion");
    winhttp.OriginalWinHttpGetTunnelSocket = GetProcAddress(winhttp.dll, "WinHttpGetTunnelSocket");
    winhttp.OriginalWinHttpOpen = GetProcAddress(winhttp.dll, "WinHttpOpen");
    winhttp.OriginalWinHttpOpenRequest = GetProcAddress(winhttp.dll, "WinHttpOpenRequest");
    winhttp.OriginalWinHttpPacJsWorkerMain = GetProcAddress(winhttp.dll, "WinHttpPacJsWorkerMain");
    winhttp.OriginalWinHttpProbeConnectivity = GetProcAddress(winhttp.dll, "WinHttpProbeConnectivity");
    winhttp.OriginalWinHttpQueryAuthSchemes = GetProcAddress(winhttp.dll, "WinHttpQueryAuthSchemes");
    winhttp.OriginalWinHttpQueryConnectionGroup = GetProcAddress(winhttp.dll, "WinHttpQueryConnectionGroup");
    winhttp.OriginalWinHttpQueryDataAvailable = GetProcAddress(winhttp.dll, "WinHttpQueryDataAvailable");
    winhttp.OriginalWinHttpQueryHeaders = GetProcAddress(winhttp.dll, "WinHttpQueryHeaders");
    winhttp.OriginalWinHttpQueryHeadersEx = GetProcAddress(winhttp.dll, "WinHttpQueryHeadersEx");
    winhttp.OriginalWinHttpQueryOption = GetProcAddress(winhttp.dll, "WinHttpQueryOption");
    winhttp.OriginalWinHttpReadData = GetProcAddress(winhttp.dll, "WinHttpReadData");
    winhttp.OriginalWinHttpReadDataEx = GetProcAddress(winhttp.dll, "WinHttpReadDataEx");
    winhttp.OriginalWinHttpReadProxySettings = GetProcAddress(winhttp.dll, "WinHttpReadProxySettings");
    winhttp.OriginalWinHttpReadProxySettingsHvsi = GetProcAddress(winhttp.dll, "WinHttpReadProxySettingsHvsi");
    winhttp.OriginalWinHttpReceiveResponse = GetProcAddress(winhttp.dll, "WinHttpReceiveResponse");
    winhttp.OriginalWinHttpRegisterProxyChangeNotification = GetProcAddress(winhttp.dll, "WinHttpRegisterProxyChangeNotification");
    winhttp.OriginalWinHttpResetAutoProxy = GetProcAddress(winhttp.dll, "WinHttpResetAutoProxy");
    winhttp.OriginalWinHttpSaveProxyCredentials = GetProcAddress(winhttp.dll, "WinHttpSaveProxyCredentials");
    winhttp.OriginalWinHttpSendRequest = GetProcAddress(winhttp.dll, "WinHttpSendRequest");
    winhttp.OriginalWinHttpSetCredentials = GetProcAddress(winhttp.dll, "WinHttpSetCredentials");
    winhttp.OriginalWinHttpSetDefaultProxyConfiguration = GetProcAddress(winhttp.dll, "WinHttpSetDefaultProxyConfiguration");
    winhttp.OriginalWinHttpSetOption = GetProcAddress(winhttp.dll, "WinHttpSetOption");
    winhttp.OriginalWinHttpSetProxySettingsPerUser = GetProcAddress(winhttp.dll, "WinHttpSetProxySettingsPerUser");
    winhttp.OriginalWinHttpSetSecureLegacyServersAppCompat = GetProcAddress(winhttp.dll, "WinHttpSetSecureLegacyServersAppCompat");
    winhttp.OriginalWinHttpSetStatusCallback = GetProcAddress(winhttp.dll, "WinHttpSetStatusCallback");
    winhttp.OriginalWinHttpSetTimeouts = GetProcAddress(winhttp.dll, "WinHttpSetTimeouts");
    winhttp.OriginalWinHttpTimeFromSystemTime = GetProcAddress(winhttp.dll, "WinHttpTimeFromSystemTime");
    winhttp.OriginalWinHttpTimeToSystemTime = GetProcAddress(winhttp.dll, "WinHttpTimeToSystemTime");
    winhttp.OriginalWinHttpUnregisterProxyChangeNotification = GetProcAddress(winhttp.dll, "WinHttpUnregisterProxyChangeNotification");
    winhttp.OriginalWinHttpWebSocketClose = GetProcAddress(winhttp.dll, "WinHttpWebSocketClose");
    winhttp.OriginalWinHttpWebSocketCompleteUpgrade = GetProcAddress(winhttp.dll, "WinHttpWebSocketCompleteUpgrade");
    winhttp.OriginalWinHttpWebSocketQueryCloseStatus = GetProcAddress(winhttp.dll, "WinHttpWebSocketQueryCloseStatus");
    winhttp.OriginalWinHttpWebSocketReceive = GetProcAddress(winhttp.dll, "WinHttpWebSocketReceive");
    winhttp.OriginalWinHttpWebSocketSend = GetProcAddress(winhttp.dll, "WinHttpWebSocketSend");
    winhttp.OriginalWinHttpWebSocketShutdown = GetProcAddress(winhttp.dll, "WinHttpWebSocketShutdown");
    winhttp.OriginalWinHttpWriteData = GetProcAddress(winhttp.dll, "WinHttpWriteData");
    winhttp.OriginalWinHttpWriteProxySettings = GetProcAddress(winhttp.dll, "WinHttpWriteProxySettings");
    return true;
}

#if defined(__cplusplus)
}
#endif
