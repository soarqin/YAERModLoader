#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <strsafe.h>
#include <intsafe.h>
#include <stdbool.h>

#if defined(_X86_)
#define DETOURS_X86
#define DETOURS_OPTION_BITS 64

#elif defined(_AMD64_)
#define DETOURS_X64
#define DETOURS_OPTION_BITS 32

#elif defined(_IA64_)
#define DETOURS_IA64
#define DETOURS_OPTION_BITS 32

#elif defined(_ARM_)
#define DETOURS_ARM

#elif defined(_ARM64_)
#define DETOURS_ARM64

#else
#error Unknown architecture (x86, amd64, ia64, arm, arm64)
#endif

#ifdef _WIN64
#undef DETOURS_32BIT
#define DETOURS_64BIT 1
#define DETOURS_BITS 64
// If all 64bit kernels can run one and only one 32bit architecture.
//#define DETOURS_OPTION_BITS 32
#else
#define DETOURS_32BIT 1
#undef DETOURS_64BIT
#define DETOURS_BITS 32
// If all 64bit kernels can run one and only one 32bit architecture.
//#define DETOURS_OPTION_BITS 32
#endif

#ifndef DETOUR_TRACE
#if DETOUR_DEBUG
#define DETOUR_TRACE(x) printf x
#define DETOUR_BREAK()  __debugbreak()
#include <stdio.h>
#include <limits.h>
#else
#define DETOUR_TRACE(x)
#define DETOUR_BREAK()
#endif
#endif

#define DETOURS_STRINGIFY_(x)    #x
#define DETOURS_STRINGIFY(x)    DETOURS_STRINGIFY_(x)

extern const GUID DETOUR_EXE_RESTORE_GUID;

const GUID DETOUR_EXE_RESTORE_GUID = {
    0xbda26f34, 0xbc82, 0x4829,
    {0x9e, 0x64, 0x74, 0x2c, 0x4, 0xc8, 0x4f, 0xa0}};

#define MM_ALLOCATION_GRANULARITY 0x10000
#ifndef DETOUR_MAX_SUPPORTED_IMAGE_SECTION_HEADERS
#define DETOUR_MAX_SUPPORTED_IMAGE_SECTION_HEADERS      32
#endif // !DETOUR_MAX_SUPPORTED_IMAGE_SECTION_HEADERS

#define DETOUR_SECTION_HEADER_SIGNATURE         0x00727444   // "Dtr\0"

#pragma pack(push, 8)
typedef struct _DETOUR_SECTION_HEADER {
    DWORD cbHeaderSize;
    DWORD nSignature;
    DWORD nDataOffset;
    DWORD cbDataSize;

    DWORD nOriginalImportVirtualAddress;
    DWORD nOriginalImportSize;
    DWORD nOriginalBoundImportVirtualAddress;
    DWORD nOriginalBoundImportSize;

    DWORD nOriginalIatVirtualAddress;
    DWORD nOriginalIatSize;
    DWORD nOriginalSizeOfImage;
    DWORD cbPrePE;

    DWORD nOriginalClrFlags;
    DWORD reserved1;
    DWORD reserved2;
    DWORD reserved3;

    // Followed by cbPrePE bytes of data.
} DETOUR_SECTION_HEADER, *PDETOUR_SECTION_HEADER;

typedef struct _DETOUR_SECTION_RECORD {
    DWORD cbBytes;
    DWORD nReserved;
    GUID guid;
} DETOUR_SECTION_RECORD, *PDETOUR_SECTION_RECORD;

typedef struct _DETOUR_CLR_HEADER {
    // Header versioning
    ULONG cb;
    USHORT MajorRuntimeVersion;
    USHORT MinorRuntimeVersion;

    // Symbol table and startup information
    IMAGE_DATA_DIRECTORY MetaData;
    ULONG Flags;

    // Followed by the rest of the IMAGE_COR20_HEADER
} DETOUR_CLR_HEADER, *PDETOUR_CLR_HEADER;

typedef struct _DETOUR_EXE_RESTORE {
    DWORD cb;
    DWORD cbidh;
    DWORD cbinh;
    DWORD cbclr;

    PBYTE pidh;
    PBYTE pinh;
    PBYTE pclr;

    IMAGE_DOS_HEADER idh;
    union {
        IMAGE_NT_HEADERS inh;        // all environments have this
#ifdef IMAGE_NT_OPTIONAL_HDR32_MAGIC    // some environments do not have this
        IMAGE_NT_HEADERS32 inh32;
#endif
#ifdef IMAGE_NT_OPTIONAL_HDR64_MAGIC    // some environments do not have this
        IMAGE_NT_HEADERS64 inh64;
#endif
#ifdef IMAGE_NT_OPTIONAL_HDR64_MAGIC    // some environments do not have this
        BYTE raw[sizeof(IMAGE_NT_HEADERS64) +
                 sizeof(IMAGE_SECTION_HEADER) * DETOUR_MAX_SUPPORTED_IMAGE_SECTION_HEADERS];
#else
        BYTE                raw[0x108 + sizeof(IMAGE_SECTION_HEADER) * DETOUR_MAX_SUPPORTED_IMAGE_SECTION_HEADERS];
#endif
    };
    DETOUR_CLR_HEADER clr;

} DETOUR_EXE_RESTORE, *PDETOUR_EXE_RESTORE;

#ifdef IMAGE_NT_OPTIONAL_HDR64_MAGIC
C_ASSERT(sizeof(IMAGE_NT_HEADERS64) == 0x108);
#endif

// The size can change, but assert for clarity due to the muddying #ifdefs.
#ifdef _WIN64
C_ASSERT(sizeof(DETOUR_EXE_RESTORE) == 0x688);
#else
C_ASSERT(sizeof(DETOUR_EXE_RESTORE) == 0x678);
#endif

#pragma pack(pop)

#define IMPORT_DIRECTORY OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT]
#define BOUND_DIRECTORY OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT]
#define CLR_DIRECTORY OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR]
#define IAT_DIRECTORY OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT]

static BOOL IsWow64ProcessHelper(HANDLE hProcess,
                                 PBOOL Wow64Process) {
#ifdef _X86_
    if (Wow64Process == NULL) {
        return FALSE;
    }

    // IsWow64Process is not available on all supported versions of Windows.
    //
    HMODULE hKernel32 = LoadLibraryW(L"KERNEL32.DLL");
    if (hKernel32 == NULL) {
        DETOUR_TRACE(("LoadLibraryW failed: %lu\n", GetLastError()));
        return FALSE;
    }

    LPFN_ISWOW64PROCESS pfnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
        hKernel32, "IsWow64Process");

    if (pfnIsWow64Process == NULL) {
        DETOUR_TRACE(("GetProcAddress failed: %lu\n", GetLastError()));
        return FALSE;
    }
    return pfnIsWow64Process(hProcess, Wow64Process);
#else
    return IsWow64Process(hProcess, Wow64Process);
#endif
}

#define DETOUR_PAGE_EXECUTE_ALL    (PAGE_EXECUTE |              \
                                    PAGE_EXECUTE_READ |         \
                                    PAGE_EXECUTE_READWRITE |    \
                                    PAGE_EXECUTE_WRITECOPY)

#define DETOUR_PAGE_NO_EXECUTE_ALL (PAGE_NOACCESS |             \
                                    PAGE_READONLY |             \
                                    PAGE_READWRITE |            \
                                    PAGE_WRITECOPY)

#define DETOUR_PAGE_ATTRIBUTES     (~(DETOUR_PAGE_EXECUTE_ALL | DETOUR_PAGE_NO_EXECUTE_ALL))

C_ASSERT((DETOUR_PAGE_NO_EXECUTE_ALL << 4) == DETOUR_PAGE_EXECUTE_ALL);

static DWORD DetourPageProtectAdjustExecute(_In_  DWORD dwOldProtect,
                                            _In_  DWORD dwNewProtect)
//  Copy EXECUTE from dwOldProtect to dwNewProtect.
{
    bool const fOldExecute = ((dwOldProtect & DETOUR_PAGE_EXECUTE_ALL) != 0);
    bool const fNewExecute = ((dwNewProtect & DETOUR_PAGE_EXECUTE_ALL) != 0);

    if (fOldExecute && !fNewExecute) {
        dwNewProtect = ((dwNewProtect & DETOUR_PAGE_NO_EXECUTE_ALL) << 4)
                       | (dwNewProtect & DETOUR_PAGE_ATTRIBUTES);
    } else if (!fOldExecute && fNewExecute) {
        dwNewProtect = ((dwNewProtect & DETOUR_PAGE_EXECUTE_ALL) >> 4)
                       | (dwNewProtect & DETOUR_PAGE_ATTRIBUTES);
    }
    return dwNewProtect;
}

_Success_(return != FALSE)
BOOL WINAPI DetourVirtualProtectSameExecuteEx(_In_  HANDLE hProcess,
                                              _In_  PVOID pAddress,
                                              _In_  SIZE_T nSize,
                                              _In_  DWORD dwNewProtect,
                                              _Out_ PDWORD pdwOldProtect)
// Some systems do not allow executability of a page to change. This function applies
// dwNewProtect to [pAddress, nSize), but preserving the previous executability.
// This function is meant to be a drop-in replacement for some uses of VirtualProtectEx.
// When "restoring" page protection, there is no need to use this function.
{
    MEMORY_BASIC_INFORMATION mbi;

    // Query to get existing execute access.

    ZeroMemory(&mbi, sizeof(mbi));

    if (VirtualQueryEx(hProcess, pAddress, &mbi, sizeof(mbi)) == 0) {
        return FALSE;
    }
    return VirtualProtectEx(hProcess, pAddress, nSize,
                            DetourPageProtectAdjustExecute(mbi.Protect, dwNewProtect),
                            pdwOldProtect);
}

static PVOID LoadNtHeaderFromProcess(_In_ HANDLE hProcess,
                                     _In_ HMODULE hModule,
                                     _Out_ PIMAGE_NT_HEADERS32 pNtHeader) {
    ZeroMemory(pNtHeader, sizeof(*pNtHeader));
    PBYTE pbModule = (PBYTE)hModule;

    if (pbModule == NULL) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return NULL;
    }

    MEMORY_BASIC_INFORMATION mbi;
    ZeroMemory(&mbi, sizeof(mbi));

    if (VirtualQueryEx(hProcess, hModule, &mbi, sizeof(mbi)) == 0) {
        return NULL;
    }

    IMAGE_DOS_HEADER idh;
    if (!ReadProcessMemory(hProcess, pbModule, &idh, sizeof(idh), NULL)) {
        DETOUR_TRACE(("ReadProcessMemory(idh@%p..%p) failed: %lu\n",
            pbModule, pbModule + sizeof(idh), GetLastError()));
        return NULL;
    }

    if (idh.e_magic != IMAGE_DOS_SIGNATURE ||
        (DWORD)idh.e_lfanew > mbi.RegionSize ||
        (DWORD)idh.e_lfanew < sizeof(idh)) {

        SetLastError(ERROR_BAD_EXE_FORMAT);
        return NULL;
    }

    if (!ReadProcessMemory(hProcess, pbModule + idh.e_lfanew,
                           pNtHeader, sizeof(*pNtHeader), NULL)) {
        DETOUR_TRACE(("ReadProcessMemory(inh@%p..%p:%p) failed: %lu\n",
            pbModule + idh.e_lfanew,
            pbModule + idh.e_lfanew + sizeof(*pNtHeader),
            pbModule,
            GetLastError()));
        return NULL;
    }

    if (pNtHeader->Signature != IMAGE_NT_SIGNATURE) {
        SetLastError(ERROR_BAD_EXE_FORMAT);
        return NULL;
    }

    return pbModule + idh.e_lfanew;
}

static HMODULE EnumerateModulesInProcess(_In_ HANDLE hProcess,
                                         _In_opt_ HMODULE hModuleLast,
                                         _Out_ PIMAGE_NT_HEADERS32 pNtHeader,
                                         _Out_opt_ PVOID *pRemoteNtHeader) {
    ZeroMemory(pNtHeader, sizeof(*pNtHeader));
    if (pRemoteNtHeader) {
        *pRemoteNtHeader = NULL;
    }

    PBYTE pbLast = (PBYTE)hModuleLast + MM_ALLOCATION_GRANULARITY;

    MEMORY_BASIC_INFORMATION mbi;
    ZeroMemory(&mbi, sizeof(mbi));

    // Find the next memory region that contains a mapped PE image.
    //

    for (;; pbLast = (PBYTE)mbi.BaseAddress + mbi.RegionSize) {
        if (VirtualQueryEx(hProcess, (PVOID)pbLast, &mbi, sizeof(mbi)) == 0) {
            break;
        }

        // Usermode address space has such an unaligned region size always at the
        // end and only at the end.
        //
        if ((mbi.RegionSize & 0xfff) == 0xfff) {
            break;
        }
        if (((PBYTE)mbi.BaseAddress + mbi.RegionSize) < pbLast) {
            break;
        }

        // Skip uncommitted regions and guard pages.
        //
        if ((mbi.State != MEM_COMMIT) ||
            ((mbi.Protect & 0xff) == PAGE_NOACCESS) ||
            (mbi.Protect & PAGE_GUARD)) {
            continue;
        }

        PVOID remoteHeader
            = LoadNtHeaderFromProcess(hProcess, (HMODULE)pbLast, pNtHeader);
        if (remoteHeader) {
            if (pRemoteNtHeader) {
                *pRemoteNtHeader = remoteHeader;
            }

            return (HMODULE)pbLast;
        }
    }
    return NULL;
}

static BOOL RecordExeRestore(HANDLE hProcess, HMODULE hModule, DETOUR_EXE_RESTORE *der) {
// Save the various headers for DetourRestoreAfterWith.
    ZeroMemory(der, sizeof(*der));
    der->cb = sizeof(*der);

    der->pidh = (PBYTE)hModule;
    der->cbidh = sizeof(der->idh);
    if (!ReadProcessMemory(hProcess, der->pidh, &der->idh, sizeof(der->idh), NULL)) {
        DETOUR_TRACE(("ReadProcessMemory(idh@%p..%p) failed: %lu\n",
            der->pidh, der->pidh + der->cbidh, GetLastError()));
        return FALSE;
    }
    DETOUR_TRACE(("IDH: %p..%p\n", der->pidh, der->pidh + der->cbidh));

// We read the NT header in two passes to get the full size.
// First we read just the Signature and FileHeader.
    der->pinh = der->pidh + der->idh.e_lfanew;
    der->cbinh = FIELD_OFFSET(IMAGE_NT_HEADERS, OptionalHeader);
    if (!ReadProcessMemory(hProcess, der->pinh, &der->inh, der->cbinh, NULL)) {
        DETOUR_TRACE(("ReadProcessMemory(inh@%p..%p) failed: %lu\n",
            der->pinh, der->pinh + der->cbinh, GetLastError()));
        return FALSE;
    }

// Second we read the OptionalHeader and Section headers.
    der->cbinh = (FIELD_OFFSET(IMAGE_NT_HEADERS, OptionalHeader) +
                  der->inh.FileHeader.SizeOfOptionalHeader +
                  der->inh.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER));

    if (der->cbinh > sizeof(der->raw)) {
        return FALSE;
    }

    if (!ReadProcessMemory(hProcess, der->pinh, &der->inh, der->cbinh, NULL)) {
        DETOUR_TRACE(("ReadProcessMemory(inh@%p..%p) failed: %lu\n",
            der->pinh, der->pinh + der->cbinh, GetLastError()));
        return FALSE;
    }
    DETOUR_TRACE(("INH: %p..%p\n", der->pinh, der->pinh + der->cbinh));

// Third, we read the CLR header

    if (der->inh.OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
        if (der->inh32.CLR_DIRECTORY.VirtualAddress != 0 &&
            der->inh32.CLR_DIRECTORY.Size != 0) {

            DETOUR_TRACE(("CLR32.VirtAddr=%08lx, CLR.Size=%lu\n",
                der->inh32.CLR_DIRECTORY.VirtualAddress,
                der->inh32.CLR_DIRECTORY.Size));

            der->pclr = ((PBYTE)hModule) + der->inh32.CLR_DIRECTORY.VirtualAddress;
        }
    } else if (der->inh.OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
        if (der->inh64.CLR_DIRECTORY.VirtualAddress != 0 &&
            der->inh64.CLR_DIRECTORY.Size != 0) {

            DETOUR_TRACE(("CLR64.VirtAddr=%08lx, CLR.Size=%lu\n",
                der->inh64.CLR_DIRECTORY.VirtualAddress,
                der->inh64.CLR_DIRECTORY.Size));

            der->pclr = ((PBYTE)hModule) + der->inh64.CLR_DIRECTORY.VirtualAddress;
        }
    }

    if (der->pclr != 0) {
        der->cbclr = sizeof(der->clr);
        if (!ReadProcessMemory(hProcess, der->pclr, &der->clr, der->cbclr, NULL)) {
            DETOUR_TRACE(("ReadProcessMemory(clr@%p..%p) failed: %lu\n",
                der->pclr, der->pclr + der->cbclr, GetLastError()));
            return FALSE;
        }
        DETOUR_TRACE(("CLR: %p..%p\n", der->pclr, der->pclr + der->cbclr));
    }

    return TRUE;
}

#if DETOURS_64BIT

C_ASSERT(sizeof(IMAGE_NT_HEADERS64) == sizeof(IMAGE_NT_HEADERS32) + 16);

static inline DWORD PadToDword(DWORD dw) {
    return (dw + 3) & ~3u;
}

static inline DWORD PadToDwordPtr(DWORD dw) {
    return (dw + 7) & ~7u;
}

static inline HRESULT ReplaceOptionalSizeA(_Inout_z_count_(cchDest) LPSTR pszDest,
                                           _In_ size_t cchDest,
                                           _In_z_ LPCSTR pszSize) {
    if (cchDest == 0 || pszDest == NULL || pszSize == NULL ||
        pszSize[0] == '\0' || pszSize[1] == '\0' || pszSize[2] != '\0') {

        // can not write into empty buffer or with string other than two chars.
        return ERROR_INVALID_PARAMETER;
    }

    for (; cchDest >= 2; cchDest--, pszDest++) {
        if (pszDest[0] == '?' && pszDest[1] == '?') {
            pszDest[0] = pszSize[0];
            pszDest[1] = pszSize[1];
            break;
        }
    }

    return S_OK;
}

static PBYTE FindAndAllocateNearBase(HANDLE hProcess, PBYTE pbModule, PBYTE pbBase, DWORD cbAlloc) {
    MEMORY_BASIC_INFORMATION mbi;
    ZeroMemory(&mbi, sizeof(mbi));

    PBYTE pbLast = pbBase;
    for (;; pbLast = (PBYTE)mbi.BaseAddress + mbi.RegionSize) {

        ZeroMemory(&mbi, sizeof(mbi));
        if (VirtualQueryEx(hProcess, (PVOID)pbLast, &mbi, sizeof(mbi)) == 0) {
            if (GetLastError() == ERROR_INVALID_PARAMETER) {
                break;
            }
            DETOUR_TRACE(("VirtualQueryEx(%p) failed: %lu\n",
                pbLast, GetLastError()));
            break;
        }
        // Usermode address space has such an unaligned region size always at the
        // end and only at the end.
        //
        if ((mbi.RegionSize & 0xfff) == 0xfff) {
            break;
        }

        // Skip anything other than a pure free region.
        //
        if (mbi.State != MEM_FREE) {
            continue;
        }

        // Use the max of mbi.BaseAddress and pbBase, in case mbi.BaseAddress < pbBase.
        PBYTE pbAddress = (PBYTE)mbi.BaseAddress > pbBase ? (PBYTE)mbi.BaseAddress : pbBase;

        // Round pbAddress up to the nearest MM allocation boundary.
        const DWORD_PTR mmGranularityMinusOne = (DWORD_PTR)(MM_ALLOCATION_GRANULARITY - 1);
        pbAddress = (PBYTE)(((DWORD_PTR)pbAddress + mmGranularityMinusOne) & ~mmGranularityMinusOne);

#ifdef _WIN64
        // The offset from pbModule to any replacement import must fit into 32 bits.
        // For simplicity, we check that the offset to the last byte fits into 32 bits,
        // instead of the largest offset we'll actually use. The values are very similar.
        const size_t GB4 = ((((size_t)1) << 32) - 1);
        if ((size_t)(pbAddress + cbAlloc - 1 - pbModule) > GB4) {
            DETOUR_TRACE(("FindAndAllocateNearBase(1) failing due to distance >4GB %p\n", pbAddress));
            return NULL;
        }
#else
            UNREFERENCED_PARAMETER(pbModule);
#endif

        DETOUR_TRACE(("Free region %p..%p\n",
            mbi.BaseAddress,
            (PBYTE)mbi.BaseAddress + mbi.RegionSize));

        for (; pbAddress < (PBYTE)mbi.BaseAddress + mbi.RegionSize; pbAddress += MM_ALLOCATION_GRANULARITY) {
            PBYTE pbAlloc = (PBYTE)VirtualAllocEx(hProcess, pbAddress, cbAlloc,
                                                  MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            if (pbAlloc == NULL) {
                DETOUR_TRACE(("VirtualAllocEx(%p) failed: %lu\n", pbAddress, GetLastError()));
                continue;
            }
#ifdef _WIN64
            // The offset from pbModule to any replacement import must fit into 32 bits.
            if ((size_t)(pbAddress + cbAlloc - 1 - pbModule) > GB4) {
                DETOUR_TRACE(("FindAndAllocateNearBase(2) failing due to distance >4GB %p\n", pbAddress));
                return NULL;
            }
#endif
            DETOUR_TRACE(("[%p..%p] Allocated for import table.\n",
                pbAlloc, pbAlloc + cbAlloc));
            return pbAlloc;
        }
    }
    return NULL;
}

#if DETOURS_32BIT
#define DWORD_XX                        DWORD32
#define IMAGE_NT_HEADERS_XX             IMAGE_NT_HEADERS32
#define IMAGE_NT_OPTIONAL_HDR_MAGIC_XX  IMAGE_NT_OPTIONAL_HDR32_MAGIC
#define IMAGE_ORDINAL_FLAG_XX           IMAGE_ORDINAL_FLAG32
#define IMAGE_THUNK_DATAXX              IMAGE_THUNK_DATA32
#define UPDATE_IMPORTS_XX               UpdateImports32
#define DETOURS_BITS_XX                 32
#endif // DETOURS_32BIT

#if DETOURS_64BIT
#define DWORD_XX                        DWORD64
#define IMAGE_NT_HEADERS_XX             IMAGE_NT_HEADERS64
#define IMAGE_NT_OPTIONAL_HDR_MAGIC_XX  IMAGE_NT_OPTIONAL_HDR64_MAGIC
#define IMAGE_ORDINAL_FLAG_XX           IMAGE_ORDINAL_FLAG64
#define IMAGE_THUNK_DATAXX              IMAGE_THUNK_DATA64
#define UPDATE_IMPORTS_XX               UpdateImports64
#define DETOURS_BITS_XX                 64
#endif // DETOURS_64BIT

// UpdateImports32 aka UpdateImports64
static BOOL UPDATE_IMPORTS_XX(HANDLE hProcess,
                              HMODULE hModule,
                              __in_ecount(nDlls) LPCSTR *plpDlls,
                              DWORD nDlls) {
    BOOL fSucceeded = FALSE;
    DWORD cbNew = 0;

    BYTE *pbNew = NULL;
    DWORD i;
    SIZE_T cbRead;
    DWORD n;

    PBYTE pbModule = (PBYTE)hModule;

    IMAGE_DOS_HEADER idh;
    ZeroMemory(&idh, sizeof(idh));
    if (!ReadProcessMemory(hProcess, pbModule, &idh, sizeof(idh), &cbRead)
        || cbRead < sizeof(idh)) {

        DETOUR_TRACE(("ReadProcessMemory(idh@%p..%p) failed: %lu\n",
            pbModule, pbModule + sizeof(idh), GetLastError()));

        finish:
        if (pbNew != NULL) {
            free(pbNew);
            pbNew = NULL;
        }
        return fSucceeded;
    }

    IMAGE_NT_HEADERS_XX inh;
    ZeroMemory(&inh, sizeof(inh));

    if (!ReadProcessMemory(hProcess, pbModule + idh.e_lfanew, &inh, sizeof(inh), &cbRead)
        || cbRead < sizeof(inh)) {
        DETOUR_TRACE(("ReadProcessMemory(inh@%p..%p) failed: %lu\n",
            pbModule + idh.e_lfanew,
            pbModule + idh.e_lfanew + sizeof(inh),
            GetLastError()));
        goto finish;
    }

    if (inh.OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR_MAGIC_XX) {
        DETOUR_TRACE(("Wrong size image (%04x != %04x).\n",
            inh.OptionalHeader.Magic, IMAGE_NT_OPTIONAL_HDR_MAGIC_XX));
        SetLastError(ERROR_INVALID_BLOCK);
        goto finish;
    }

    // Zero out the bound table so loader doesn't use it instead of our new table.
    inh.BOUND_DIRECTORY.VirtualAddress = 0;
    inh.BOUND_DIRECTORY.Size = 0;

    // Find the size of the mapped file.
    DWORD dwSec = idh.e_lfanew +
                  FIELD_OFFSET(IMAGE_NT_HEADERS_XX, OptionalHeader) +
                  inh.FileHeader.SizeOfOptionalHeader;

    for (i = 0; i < inh.FileHeader.NumberOfSections; i++) {
        IMAGE_SECTION_HEADER ish;
        ZeroMemory(&ish, sizeof(ish));

        if (!ReadProcessMemory(hProcess, pbModule + dwSec + sizeof(ish) * i, &ish,
                               sizeof(ish), &cbRead)
            || cbRead < sizeof(ish)) {

            DETOUR_TRACE(("ReadProcessMemory(ish@%p..%p) failed: %lu\n",
                pbModule + dwSec + sizeof(ish) * i,
                pbModule + dwSec + sizeof(ish) * (i + 1),
                GetLastError()));
            goto finish;
        }

        DETOUR_TRACE(("ish[%lu] : va=%08lx sr=%lu\n", i, ish.VirtualAddress, ish.SizeOfRawData));

        // If the linker didn't suggest an IAT in the data directories, the
        // loader will look for the section of the import directory to be used
        // for this instead. Since we put out new IMPORT_DIRECTORY outside any
        // section boundary, the loader will not find it. So we provide one
        // explicitly to avoid the search.
        //
        if (inh.IAT_DIRECTORY.VirtualAddress == 0 &&
            inh.IMPORT_DIRECTORY.VirtualAddress >= ish.VirtualAddress &&
            inh.IMPORT_DIRECTORY.VirtualAddress < ish.VirtualAddress + ish.SizeOfRawData) {

            inh.IAT_DIRECTORY.VirtualAddress = ish.VirtualAddress;
            inh.IAT_DIRECTORY.Size = ish.SizeOfRawData;
        }
    }

    if (inh.IMPORT_DIRECTORY.VirtualAddress != 0 && inh.IMPORT_DIRECTORY.Size == 0) {

        // Don't worry about changing the PE file,
        // because the load information of the original PE header has been saved and will be restored.
        // The change here is just for the following code to work normally

        PIMAGE_IMPORT_DESCRIPTOR pImageImport = (PIMAGE_IMPORT_DESCRIPTOR)(pbModule + inh.IMPORT_DIRECTORY.VirtualAddress);

        do {
            IMAGE_IMPORT_DESCRIPTOR ImageImport;
            if (!ReadProcessMemory(hProcess, pImageImport, &ImageImport, sizeof(ImageImport), NULL)) {
                DETOUR_TRACE(("ReadProcessMemory failed: %lu\n", GetLastError()));
                goto finish;
            }
            inh.IMPORT_DIRECTORY.Size += sizeof(IMAGE_IMPORT_DESCRIPTOR);
            if (!ImageImport.Name) {
                break;
            }
            ++pImageImport;
        } while (TRUE);

        DWORD dwLastError = GetLastError();
        OutputDebugString(TEXT("[This PE file has an import table, but the import table size is marked as 0. This is an error.")
                          TEXT("If it is not repaired, the launched program will not work properly, Detours has automatically repaired its import table size for you! ! !]\r\n"));
        if (GetLastError() != dwLastError) {
            SetLastError(dwLastError);
        }
    }

    DETOUR_TRACE(("     Imports: %p..%p\n",
        pbModule + inh.IMPORT_DIRECTORY.VirtualAddress,
        pbModule + inh.IMPORT_DIRECTORY.VirtualAddress +
        inh.IMPORT_DIRECTORY.Size));

    // Calculate new import directory size.  Note that since inh is from another
    // process, inh could have been corrupted. We need to protect against
    // integer overflow in allocation calculations.
    DWORD nOldDlls = inh.IMPORT_DIRECTORY.Size / sizeof(IMAGE_IMPORT_DESCRIPTOR);
    DWORD obRem;
    if (DWordMult(sizeof(IMAGE_IMPORT_DESCRIPTOR), nDlls, &obRem) != S_OK) {
        DETOUR_TRACE(("too many new DLLs.\n"));
        goto finish;
    }
    DWORD obOld;
    if (DWordAdd(obRem, sizeof(IMAGE_IMPORT_DESCRIPTOR) * nOldDlls, &obOld) != S_OK) {
        DETOUR_TRACE(("DLL entries overflow.\n"));
        goto finish;
    }
    DWORD obTab = PadToDwordPtr(obOld);
    // Check for integer overflow.
    if (obTab < obOld) {
        DETOUR_TRACE(("DLL entries padding overflow.\n"));
        goto finish;
    }
    DWORD stSize;
    if (DWordMult(sizeof(DWORD_XX) * 4, nDlls, &stSize) != S_OK) {
        DETOUR_TRACE(("String table overflow.\n"));
        goto finish;
    }
    DWORD obDll;
    if (DWordAdd(obTab, stSize, &obDll) != S_OK) {
        DETOUR_TRACE(("Import table size overflow\n"));
        goto finish;
    }
    DWORD obStr = obDll;
    cbNew = obStr;
    for (n = 0; n < nDlls; n++) {
        if (DWordAdd(cbNew, PadToDword((DWORD)strlen(plpDlls[n]) + 1), &cbNew) != S_OK) {
            DETOUR_TRACE(("Overflow adding string table entry\n"));
            goto finish;
        }
    }
    pbNew = (BYTE *)malloc(cbNew);
    if (pbNew == NULL) {
        DETOUR_TRACE(("new BYTE [cbNew] failed.\n"));
        goto finish;
    }
    ZeroMemory(pbNew, cbNew);

    PBYTE pbBase = pbModule;
    PBYTE pbNext = pbBase
                   + inh.OptionalHeader.BaseOfCode
                   + inh.OptionalHeader.SizeOfCode
                   + inh.OptionalHeader.SizeOfInitializedData
                   + inh.OptionalHeader.SizeOfUninitializedData;
    if (pbBase < pbNext) {
        pbBase = pbNext;
    }
    DETOUR_TRACE(("pbBase = %p\n", pbBase));

    PBYTE pbNewIid = FindAndAllocateNearBase(hProcess, pbModule, pbBase, cbNew);
    if (pbNewIid == NULL) {
        DETOUR_TRACE(("FindAndAllocateNearBase failed.\n"));
        goto finish;
    }

    PIMAGE_IMPORT_DESCRIPTOR piid = (PIMAGE_IMPORT_DESCRIPTOR)pbNew;
    IMAGE_THUNK_DATAXX *pt = NULL;

    DWORD obBase = (DWORD)(pbNewIid - pbModule);
    DWORD dwProtect = 0;

    if (inh.IMPORT_DIRECTORY.VirtualAddress != 0) {
        // Read the old import directory if it exists.
        DETOUR_TRACE(("IMPORT_DIRECTORY perms=%lx\n", dwProtect));

        if (!ReadProcessMemory(hProcess,
                               pbModule + inh.IMPORT_DIRECTORY.VirtualAddress,
                               &piid[nDlls],
                               nOldDlls * sizeof(IMAGE_IMPORT_DESCRIPTOR), &cbRead)
            || cbRead < nOldDlls * sizeof(IMAGE_IMPORT_DESCRIPTOR)) {

            DETOUR_TRACE(("ReadProcessMemory(imports) failed: %lu\n", GetLastError()));
            goto finish;
        }
    }

    for (n = 0; n < nDlls; n++) {
        HRESULT hrRet = StringCchCopyA((char *)pbNew + obStr, cbNew - obStr, plpDlls[n]);
        if (FAILED(hrRet)) {
            DETOUR_TRACE(("StringCchCopyA failed: %08lx\n", hrRet));
            goto finish;
        }

        // After copying the string, we patch up the size "??" bits if any.
        hrRet = ReplaceOptionalSizeA((char *)pbNew + obStr,
                                     cbNew - obStr,
                                     DETOURS_STRINGIFY(DETOURS_BITS_XX));
        if (FAILED(hrRet)) {
            DETOUR_TRACE(("ReplaceOptionalSizeA failed: %08lx\n", hrRet));
            goto finish;
        }

        DWORD nOffset = obTab + (sizeof(IMAGE_THUNK_DATAXX) * (4 * n));
        piid[n].OriginalFirstThunk = obBase + nOffset;

        // We need 2 thunks for the import table and 2 thunks for the IAT.
        // One for an ordinal import and one to mark the end of the list.
        pt = ((IMAGE_THUNK_DATAXX *)(pbNew + nOffset));
        pt[0].u1.Ordinal = IMAGE_ORDINAL_FLAG_XX + 1;
        pt[1].u1.Ordinal = 0;

        nOffset = obTab + (sizeof(IMAGE_THUNK_DATAXX) * ((4 * n) + 2));
        piid[n].FirstThunk = obBase + nOffset;
        pt = ((IMAGE_THUNK_DATAXX *)(pbNew + nOffset));
        pt[0].u1.Ordinal = IMAGE_ORDINAL_FLAG_XX + 1;
        pt[1].u1.Ordinal = 0;
        piid[n].TimeDateStamp = 0;
        piid[n].ForwarderChain = 0;
        piid[n].Name = obBase + obStr;

        obStr += PadToDword((DWORD)strlen(plpDlls[n]) + 1);
    }
    _Analysis_assume_(obStr <= cbNew);

#if 0
    for (i = 0; i < nDlls + nOldDlls; i++) {
        DETOUR_TRACE(("%8d. Look=%08x Time=%08x Fore=%08x Name=%08x Addr=%08x\n",
                      i,
                      piid[i].OriginalFirstThunk,
                      piid[i].TimeDateStamp,
                      piid[i].ForwarderChain,
                      piid[i].Name,
                      piid[i].FirstThunk));
        if (piid[i].OriginalFirstThunk == 0 && piid[i].FirstThunk == 0) {
            break;
        }
    }
#endif

    if (!WriteProcessMemory(hProcess, pbNewIid, pbNew, obStr, NULL)) {
        DETOUR_TRACE(("WriteProcessMemory(iid) failed: %lu\n", GetLastError()));
        goto finish;
    }

    DETOUR_TRACE(("obBaseBef = %08lx..%08lx\n",
        inh.IMPORT_DIRECTORY.VirtualAddress,
        inh.IMPORT_DIRECTORY.VirtualAddress + inh.IMPORT_DIRECTORY.Size));
    DETOUR_TRACE(("obBaseAft = %08lx..%08lx\n", obBase, obBase + obStr));

    // In this case the file didn't have an import directory in first place,
    // so we couldn't fix the missing IAT above. We still need to explicitly
    // provide an IAT to prevent to loader from looking for one.
    //
    if (inh.IAT_DIRECTORY.VirtualAddress == 0) {
        inh.IAT_DIRECTORY.VirtualAddress = obBase;
        inh.IAT_DIRECTORY.Size = cbNew;
    }

    inh.IMPORT_DIRECTORY.VirtualAddress = obBase;
    inh.IMPORT_DIRECTORY.Size = cbNew;

    /////////////////////// Update the NT header for the new import directory.
    //
    if (!DetourVirtualProtectSameExecuteEx(hProcess, pbModule, inh.OptionalHeader.SizeOfHeaders,
                                           PAGE_EXECUTE_READWRITE, &dwProtect)) {
        DETOUR_TRACE(("VirtualProtectEx(inh) write failed: %lu\n", GetLastError()));
        goto finish;
    }

    inh.OptionalHeader.CheckSum = 0;

    if (!WriteProcessMemory(hProcess, pbModule, &idh, sizeof(idh), NULL)) {
        DETOUR_TRACE(("WriteProcessMemory(idh) failed: %lu\n", GetLastError()));
        goto finish;
    }
    DETOUR_TRACE(("WriteProcessMemory(idh:%p..%p)\n", pbModule, pbModule + sizeof(idh)));

    if (!WriteProcessMemory(hProcess, pbModule + idh.e_lfanew, &inh, sizeof(inh), NULL)) {
        DETOUR_TRACE(("WriteProcessMemory(inh) failed: %lu\n", GetLastError()));
        goto finish;
    }
    DETOUR_TRACE(("WriteProcessMemory(inh:%p..%p)\n",
        pbModule + idh.e_lfanew,
        pbModule + idh.e_lfanew + sizeof(inh)));

    if (!VirtualProtectEx(hProcess, pbModule, inh.OptionalHeader.SizeOfHeaders,
                          dwProtect, &dwProtect)) {
        DETOUR_TRACE(("VirtualProtectEx(idh) restore failed: %lu\n", GetLastError()));
        goto finish;
    }

    fSucceeded = TRUE;
    goto finish;
}

#if DETOURS_32BIT
#undef DETOUR_EXE_RESTORE_FIELD_XX
#undef DWORD_XX
#undef IMAGE_NT_HEADERS_XX
#undef IMAGE_NT_OPTIONAL_HDR_MAGIC_XX
#undef IMAGE_ORDINAL_FLAG_XX
#undef UPDATE_IMPORTS_XX
#endif // DETOURS_32BIT

#if DETOURS_64BIT
#undef DETOUR_EXE_RESTORE_FIELD_XX
#undef DWORD_XX
#undef IMAGE_NT_HEADERS_XX
#undef IMAGE_NT_OPTIONAL_HDR_MAGIC_XX
#undef IMAGE_ORDINAL_FLAG_XX
#undef UPDATE_IMPORTS_XX
#endif // DETOURS_64BIT

static BOOL UpdateFrom32To64(HANDLE hProcess, HMODULE hModule, WORD machine,
                             DETOUR_EXE_RESTORE *der) {
    IMAGE_DOS_HEADER idh;
    IMAGE_NT_HEADERS32 inh32;
    IMAGE_NT_HEADERS64 inh64;
    IMAGE_SECTION_HEADER sects[32];
    PBYTE pbModule = (PBYTE)hModule;
    DWORD n;

    ZeroMemory(&inh32, sizeof(inh32));
    ZeroMemory(&inh64, sizeof(inh64));
    ZeroMemory(sects, sizeof(sects));

    DETOUR_TRACE(("UpdateFrom32To64(%04x)\n", machine));
//////////////////////////////////////////////////////// Read old headers.
//
    if (!ReadProcessMemory(hProcess, pbModule, &idh, sizeof(idh), NULL)) {
        DETOUR_TRACE(("ReadProcessMemory(idh@%p..%p) failed: %lu\n",
            pbModule, pbModule + sizeof(idh), GetLastError()));
        return FALSE;
    }
    DETOUR_TRACE(("ReadProcessMemory(idh@%p..%p)\n",
        pbModule, pbModule + sizeof(idh)));

    PBYTE pnh = pbModule + idh.e_lfanew;
    if (!ReadProcessMemory(hProcess, pnh, &inh32, sizeof(inh32), NULL)) {
        DETOUR_TRACE(("ReadProcessMemory(inh@%p..%p) failed: %lu\n",
            pnh, pnh + sizeof(inh32), GetLastError()));
        return FALSE;
    }
    DETOUR_TRACE(("ReadProcessMemory(inh@%p..%p)\n", pnh, pnh + sizeof(inh32)));

    if (inh32.FileHeader.NumberOfSections > (sizeof(sects) / sizeof(sects[0]))) {
        return FALSE;
    }

    PBYTE psects = pnh +
                   FIELD_OFFSET(IMAGE_NT_HEADERS, OptionalHeader) +
                   inh32.FileHeader.SizeOfOptionalHeader;
    ULONG cb = inh32.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
    if (!ReadProcessMemory(hProcess, psects, &sects, cb, NULL)) {
        DETOUR_TRACE(("ReadProcessMemory(ish@%p..%p) failed: %lu\n",
            psects, psects + cb, GetLastError()));
        return FALSE;
    }
    DETOUR_TRACE(("ReadProcessMemory(ish@%p..%p)\n", psects, psects + cb));

////////////////////////////////////////////////////////// Convert header.
//
    inh64.Signature = inh32.Signature;
    inh64.FileHeader = inh32.FileHeader;
    inh64.FileHeader.Machine = machine;
    inh64.FileHeader.SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER64);

    inh64.OptionalHeader.Magic = IMAGE_NT_OPTIONAL_HDR64_MAGIC;
    inh64.OptionalHeader.MajorLinkerVersion = inh32.OptionalHeader.MajorLinkerVersion;
    inh64.OptionalHeader.MinorLinkerVersion = inh32.OptionalHeader.MinorLinkerVersion;
    inh64.OptionalHeader.SizeOfCode = inh32.OptionalHeader.SizeOfCode;
    inh64.OptionalHeader.SizeOfInitializedData = inh32.OptionalHeader.SizeOfInitializedData;
    inh64.OptionalHeader.SizeOfUninitializedData = inh32.OptionalHeader.SizeOfUninitializedData;
    inh64.OptionalHeader.AddressOfEntryPoint = inh32.OptionalHeader.AddressOfEntryPoint;
    inh64.OptionalHeader.BaseOfCode = inh32.OptionalHeader.BaseOfCode;
    inh64.OptionalHeader.ImageBase = inh32.OptionalHeader.ImageBase;
    inh64.OptionalHeader.SectionAlignment = inh32.OptionalHeader.SectionAlignment;
    inh64.OptionalHeader.FileAlignment = inh32.OptionalHeader.FileAlignment;
    inh64.OptionalHeader.MajorOperatingSystemVersion
        = inh32.OptionalHeader.MajorOperatingSystemVersion;
    inh64.OptionalHeader.MinorOperatingSystemVersion
        = inh32.OptionalHeader.MinorOperatingSystemVersion;
    inh64.OptionalHeader.MajorImageVersion = inh32.OptionalHeader.MajorImageVersion;
    inh64.OptionalHeader.MinorImageVersion = inh32.OptionalHeader.MinorImageVersion;
    inh64.OptionalHeader.MajorSubsystemVersion = inh32.OptionalHeader.MajorSubsystemVersion;
    inh64.OptionalHeader.MinorSubsystemVersion = inh32.OptionalHeader.MinorSubsystemVersion;
    inh64.OptionalHeader.Win32VersionValue = inh32.OptionalHeader.Win32VersionValue;
    inh64.OptionalHeader.SizeOfImage = inh32.OptionalHeader.SizeOfImage;
    inh64.OptionalHeader.SizeOfHeaders = inh32.OptionalHeader.SizeOfHeaders;
    inh64.OptionalHeader.CheckSum = inh32.OptionalHeader.CheckSum;
    inh64.OptionalHeader.Subsystem = inh32.OptionalHeader.Subsystem;
    inh64.OptionalHeader.DllCharacteristics = inh32.OptionalHeader.DllCharacteristics;
    inh64.OptionalHeader.SizeOfStackReserve = inh32.OptionalHeader.SizeOfStackReserve;
    inh64.OptionalHeader.SizeOfStackCommit = inh32.OptionalHeader.SizeOfStackCommit;
    inh64.OptionalHeader.SizeOfHeapReserve = inh32.OptionalHeader.SizeOfHeapReserve;
    inh64.OptionalHeader.SizeOfHeapCommit = inh32.OptionalHeader.SizeOfHeapCommit;
    inh64.OptionalHeader.LoaderFlags = inh32.OptionalHeader.LoaderFlags;
    inh64.OptionalHeader.NumberOfRvaAndSizes = inh32.OptionalHeader.NumberOfRvaAndSizes;
    for (n = 0; n < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; n++) {
        inh64.OptionalHeader.DataDirectory[n] = inh32.OptionalHeader.DataDirectory[n];
    }

/////////////////////////////////////////////////////// Write new headers.
//
    DWORD dwProtect = 0;
    if (!DetourVirtualProtectSameExecuteEx(hProcess, pbModule, inh64.OptionalHeader.SizeOfHeaders,
                                           PAGE_EXECUTE_READWRITE, &dwProtect)) {
        return FALSE;
    }

    if (!WriteProcessMemory(hProcess, pnh, &inh64, sizeof(inh64), NULL)) {
        DETOUR_TRACE(("WriteProcessMemory(inh@%p..%p) failed: %lu\n",
            pnh, pnh + sizeof(inh64), GetLastError()));
        return FALSE;
    }
    DETOUR_TRACE(("WriteProcessMemory(inh@%p..%p)\n", pnh, pnh + sizeof(inh64)));

    psects = pnh +
             FIELD_OFFSET(IMAGE_NT_HEADERS, OptionalHeader) +
             inh64.FileHeader.SizeOfOptionalHeader;
    cb = inh64.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
    if (!WriteProcessMemory(hProcess, psects, &sects, cb, NULL)) {
        DETOUR_TRACE(("WriteProcessMemory(ish@%p..%p) failed: %lu\n",
            psects, psects + cb, GetLastError()));
        return FALSE;
    }
    DETOUR_TRACE(("WriteProcessMemory(ish@%p..%p)\n", psects, psects + cb));

// Record the updated headers.
    if (!RecordExeRestore(hProcess, hModule, der)) {
        return FALSE;
    }

// Remove the import table.
    if (der->pclr != NULL && (der->clr.Flags & COMIMAGE_FLAGS_ILONLY)) {
        inh64.IMPORT_DIRECTORY.VirtualAddress = 0;
        inh64.IMPORT_DIRECTORY.Size = 0;

        if (!WriteProcessMemory(hProcess, pnh, &inh64, sizeof(inh64), NULL)) {
            DETOUR_TRACE(("WriteProcessMemory(inh@%p..%p) failed: %lu\n",
                pnh, pnh + sizeof(inh64), GetLastError()));
            return FALSE;
        }
    }

    DWORD dwOld = 0;
    if (!VirtualProtectEx(hProcess, pbModule, inh64.OptionalHeader.SizeOfHeaders,
                          dwProtect, &dwOld)) {
        return FALSE;
    }

    return TRUE;
}
#endif // DETOURS_64BIT

_Success_(return != NULL)
PVOID WINAPI DetourCopyPayloadToProcessEx(_In_ HANDLE hProcess,
                                          _In_ REFGUID rguid,
                                          _In_reads_bytes_(cbData) LPCVOID pvData,
                                          _In_ DWORD cbData) {
    if (hProcess == NULL) {
        SetLastError(ERROR_INVALID_HANDLE);
        return NULL;
    }

    DWORD cbTotal = (sizeof(IMAGE_DOS_HEADER) +
                     sizeof(IMAGE_NT_HEADERS) +
                     sizeof(IMAGE_SECTION_HEADER) +
                     sizeof(DETOUR_SECTION_HEADER) +
                     sizeof(DETOUR_SECTION_RECORD) +
                     cbData);

    PBYTE pbBase = (PBYTE)VirtualAllocEx(hProcess, NULL, cbTotal,
                                         MEM_COMMIT, PAGE_READWRITE);
    if (pbBase == NULL) {
        DETOUR_TRACE(("VirtualAllocEx(%lu) failed: %lu\n", cbTotal, GetLastError()));
        return NULL;
    }

    // As you can see in the following code,
    // the memory layout of the payload range "[pbBase, pbBase+cbTotal]" is a PE executable file,
    // so DetourFreePayload can use "DetourGetContainingModule(Payload pointer)" to get the above "pbBase" pointer,
    // pbBase: the memory block allocated by VirtualAllocEx will be released in DetourFreePayload by VirtualFree.

    PBYTE pbTarget = pbBase;
    IMAGE_DOS_HEADER idh;
    IMAGE_NT_HEADERS inh;
    IMAGE_SECTION_HEADER ish;
    DETOUR_SECTION_HEADER dsh;
    DETOUR_SECTION_RECORD dsr;
    SIZE_T cbWrote = 0;

    ZeroMemory(&idh, sizeof(idh));
    idh.e_magic = IMAGE_DOS_SIGNATURE;
    idh.e_lfanew = sizeof(idh);
    if (!WriteProcessMemory(hProcess, pbTarget, &idh, sizeof(idh), &cbWrote) ||
        cbWrote != sizeof(idh)) {
        DETOUR_TRACE(("WriteProcessMemory(idh) failed: %lu\n", GetLastError()));
        return NULL;
    }
    pbTarget += sizeof(idh);

    ZeroMemory(&inh, sizeof(inh));
    inh.Signature = IMAGE_NT_SIGNATURE;
    inh.FileHeader.SizeOfOptionalHeader = sizeof(inh.OptionalHeader);
    inh.FileHeader.Characteristics = IMAGE_FILE_DLL;
    inh.FileHeader.NumberOfSections = 1;
    inh.OptionalHeader.Magic = IMAGE_NT_OPTIONAL_HDR_MAGIC;
    if (!WriteProcessMemory(hProcess, pbTarget, &inh, sizeof(inh), &cbWrote) ||
        cbWrote != sizeof(inh)) {
        return NULL;
    }
    pbTarget += sizeof(inh);

    ZeroMemory(&ish, sizeof(ish));
    memcpy(ish.Name, ".detour", sizeof(ish.Name));
    ish.VirtualAddress = (DWORD)((pbTarget + sizeof(ish)) - pbBase);
    ish.SizeOfRawData = (sizeof(DETOUR_SECTION_HEADER) +
                         sizeof(DETOUR_SECTION_RECORD) +
                         cbData);
    if (!WriteProcessMemory(hProcess, pbTarget, &ish, sizeof(ish), &cbWrote) ||
        cbWrote != sizeof(ish)) {
        return NULL;
    }
    pbTarget += sizeof(ish);

    ZeroMemory(&dsh, sizeof(dsh));
    dsh.cbHeaderSize = sizeof(dsh);
    dsh.nSignature = DETOUR_SECTION_HEADER_SIGNATURE;
    dsh.nDataOffset = sizeof(DETOUR_SECTION_HEADER);
    dsh.cbDataSize = (sizeof(DETOUR_SECTION_HEADER) +
                      sizeof(DETOUR_SECTION_RECORD) +
                      cbData);
    if (!WriteProcessMemory(hProcess, pbTarget, &dsh, sizeof(dsh), &cbWrote) ||
        cbWrote != sizeof(dsh)) {
        return NULL;
    }
    pbTarget += sizeof(dsh);

    ZeroMemory(&dsr, sizeof(dsr));
    dsr.cbBytes = cbData + sizeof(DETOUR_SECTION_RECORD);
    dsr.nReserved = 0;
    dsr.guid = *rguid;
    if (!WriteProcessMemory(hProcess, pbTarget, &dsr, sizeof(dsr), &cbWrote) ||
        cbWrote != sizeof(dsr)) {
        return NULL;
    }
    pbTarget += sizeof(dsr);

    if (!WriteProcessMemory(hProcess, pbTarget, pvData, cbData, &cbWrote) ||
        cbWrote != cbData) {
        return NULL;
    }

    DETOUR_TRACE(("Copied %lu byte payload into target process at %p\n",
        cbData, pbTarget));

    SetLastError(NO_ERROR);
    return pbTarget;
}

BOOL WINAPI DetourCopyPayloadToProcess(_In_ HANDLE hProcess,
                                       _In_ REFGUID rguid,
                                       _In_reads_bytes_(cbData) LPCVOID pvData,
                                       _In_ DWORD cbData) {
    return DetourCopyPayloadToProcessEx(hProcess, rguid, pvData, cbData) != NULL;
}

BOOL WINAPI DetourUpdateProcessWithDllEx(_In_ HANDLE hProcess,
                                         _In_ HMODULE hModule,
                                         _In_ BOOL bIs32BitProcess,
                                         _In_reads_(nDlls) LPCSTR *rlpDlls,
                                         _In_ DWORD nDlls) {
    // Find the next memory region that contains a mapped PE image.
    //
    BOOL bIs32BitExe = FALSE;

    DETOUR_TRACE(("DetourUpdateProcessWithDllEx(%p,%p,dlls=%lu)\n", hProcess, hModule, nDlls));

    IMAGE_NT_HEADERS32 inh;

    if (hModule == NULL || !LoadNtHeaderFromProcess(hProcess, hModule, &inh)) {
        SetLastError(ERROR_INVALID_OPERATION);
        return FALSE;
    }

    if (inh.OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC
        && inh.FileHeader.Machine != 0) {

        bIs32BitExe = TRUE;
    }

    DETOUR_TRACE(("    32BitExe=%d\n", bIs32BitExe));

    if (hModule == NULL) {
        SetLastError(ERROR_INVALID_OPERATION);
        return FALSE;
    }

    // Save the various headers for DetourRestoreAfterWith.
    //
    DETOUR_EXE_RESTORE der;

    if (!RecordExeRestore(hProcess, hModule, &der)) {
        return FALSE;
    }

#if defined(DETOURS_64BIT)
    // Try to convert a neutral 32-bit managed binary to a 64-bit managed binary.
    if (bIs32BitExe && !bIs32BitProcess) {
        if (!der.pclr                       // Native binary
            || (der.clr.Flags & COMIMAGE_FLAGS_ILONLY) == 0     // Or mixed-mode MSIL
            || (der.clr.Flags & COMIMAGE_FLAGS_32BITREQUIRED) != 0) {  // Or 32BIT Required MSIL

            SetLastError(ERROR_INVALID_HANDLE);
            return FALSE;
        }

        if (!UpdateFrom32To64(hProcess, hModule,
#if defined(DETOURS_X64)
                              IMAGE_FILE_MACHINE_AMD64,
#elif defined(DETOURS_IA64)
            IMAGE_FILE_MACHINE_IA64,
#elif defined(DETOURS_ARM64)
            IMAGE_FILE_MACHINE_ARM64,
#else
#error Must define one of DETOURS_X64 or DETOURS_IA64 or DETOURS_ARM64 on 64-bit.
#endif
                              &der)) {
            return FALSE;
        }
        bIs32BitExe = FALSE;
    }
#endif // DETOURS_64BIT

    // Now decide if we can insert the detour.

#if defined(DETOURS_32BIT)
    if (bIs32BitProcess) {
        // 32-bit native or 32-bit managed process on any platform.
        if (!UpdateImports32(hProcess, hModule, rlpDlls, nDlls)) {
            return FALSE;
        }
    }
    else {
        // 64-bit native or 64-bit managed process.
        //
        // Can't detour a 64-bit process with 32-bit code.
        // Note: This happens for 32-bit PE binaries containing only
        // manage code that have been marked as 64-bit ready.
        //
        SetLastError(ERROR_INVALID_HANDLE);
        return FALSE;
    }
#elif defined(DETOURS_64BIT)
    if (bIs32BitProcess || bIs32BitExe) {
        // Can't detour a 32-bit process with 64-bit code.
        SetLastError(ERROR_INVALID_HANDLE);
        return FALSE;
    } else {
        // 64-bit native or 64-bit managed process on any platform.
        if (!UpdateImports64(hProcess, hModule, rlpDlls, nDlls)) {
            return FALSE;
        }
    }
#else
#pragma Must define one of DETOURS_32BIT or DETOURS_64BIT.
#endif // DETOURS_64BIT

    /////////////////////////////////////////////////// Update the CLR header.
    //
    if (der.pclr != NULL) {
        DETOUR_CLR_HEADER clr;
        CopyMemory(&clr, &der.clr, sizeof(clr));
        clr.Flags &= ~COMIMAGE_FLAGS_ILONLY;    // Clear the IL_ONLY flag.

        DWORD dwProtect;
        if (!DetourVirtualProtectSameExecuteEx(hProcess, der.pclr, sizeof(clr), PAGE_READWRITE, &dwProtect)) {
            DETOUR_TRACE(("VirtualProtectEx(clr) write failed: %lu\n", GetLastError()));
            return FALSE;
        }

        if (!WriteProcessMemory(hProcess, der.pclr, &clr, sizeof(clr), NULL)) {
            DETOUR_TRACE(("WriteProcessMemory(clr) failed: %lu\n", GetLastError()));
            return FALSE;
        }

        if (!VirtualProtectEx(hProcess, der.pclr, sizeof(clr), dwProtect, &dwProtect)) {
            DETOUR_TRACE(("VirtualProtectEx(clr) restore failed: %lu\n", GetLastError()));
            return FALSE;
        }
        DETOUR_TRACE(("CLR: %p..%p\n", der.pclr, der.pclr + der.cbclr));

#if DETOURS_64BIT
        if (der.clr.Flags & COMIMAGE_FLAGS_32BITREQUIRED) { // Is the 32BIT Required Flag set?
            // X64 never gets here because the process appears as a WOW64 process.
            // However, on IA64, it doesn't appear to be a WOW process.
            DETOUR_TRACE(("CLR Requires 32-bit\n"));
            SetLastError(ERROR_INVALID_HANDLE);
            return FALSE;
        }
#endif // DETOURS_64BIT
    }

    //////////////////////////////// Save the undo data to the target process.
    //
    if (!DetourCopyPayloadToProcess(hProcess, &DETOUR_EXE_RESTORE_GUID, &der, sizeof(der))) {
        DETOUR_TRACE(("DetourCopyPayloadToProcess failed: %lu\n", GetLastError()));
        return FALSE;
    }
    return TRUE;
}

BOOL WINAPI DetourUpdateProcessWithDll(_In_ HANDLE hProcess,
                                       _In_reads_(nDlls) LPCSTR *rlpDlls,
                                       _In_ DWORD nDlls) {
    // Find the next memory region that contains a mapped PE image.
    //
    BOOL bIs32BitProcess;
    BOOL bIs64BitOS = FALSE;
    HMODULE hModule = NULL;
    HMODULE hLast = NULL;

    DETOUR_TRACE(("DetourUpdateProcessWithDll(%p,dlls=%lu)\n", hProcess, nDlls));

    for (;;) {
        IMAGE_NT_HEADERS32 inh;

        if ((hLast = EnumerateModulesInProcess(hProcess, hLast, &inh, NULL)) == NULL) {
            break;
        }

        DETOUR_TRACE(("%p  machine=%04x magic=%04x\n",
            hLast, inh.FileHeader.Machine, inh.OptionalHeader.Magic));

        if ((inh.FileHeader.Characteristics & IMAGE_FILE_DLL) == 0) {
            hModule = hLast;
            DETOUR_TRACE(("%p  Found EXE\n", hLast));
        }
    }

    if (hModule == NULL) {
        SetLastError(ERROR_INVALID_OPERATION);
        return FALSE;
    }

    // Determine if the target process is 32bit or 64bit. This is a two-stop process:
    //
    // 1. First, determine if we're running on a 64bit operating system.
    //   - If we're running 64bit code (i.e. _WIN64 is defined), this is trivially true.
    //   - If we're running 32bit code (i.e. _WIN64 is not defined), test if
    //   we're running under Wow64. If so, it implies that the operating system
    //   is 64bit.
    //
#ifdef _WIN64
    bIs64BitOS = TRUE;
#else
    if (!IsWow64ProcessHelper(GetCurrentProcess(), &bIs64BitOS)) {
        return FALSE;
    }
#endif

    // 2. With the operating system bitness known, we can now consider the target process:
    //   - If we're running on a 64bit OS, the target process is 32bit in case
    //   it is running under Wow64. Otherwise, it's 64bit, running natively
    //   (without Wow64).
    //   - If we're running on a 32bit OS, the target process must be 32bit, too.
    //
    if (bIs64BitOS) {
        if (!IsWow64ProcessHelper(hProcess, &bIs32BitProcess)) {
            return FALSE;
        }
    } else {
        bIs32BitProcess = TRUE;
    }

    DETOUR_TRACE(("    32BitProcess=%d\n", bIs32BitProcess));

    return DetourUpdateProcessWithDllEx(hProcess,
                                        hModule,
                                        bIs32BitProcess,
                                        rlpDlls,
                                        nDlls);
}

typedef BOOL (WINAPI *PDETOUR_CREATE_PROCESS_ROUTINEW)(
    _In_opt_ LPCWSTR lpApplicationName,
    _Inout_opt_ LPWSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCWSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOW lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation);

BOOL WINAPI DetourCreateProcessWithDllW(_In_opt_ LPCWSTR lpApplicationName,
                                        _Inout_opt_ LPWSTR lpCommandLine,
                                        _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                        _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                        _In_ BOOL bInheritHandles,
                                        _In_ DWORD dwCreationFlags,
                                        _In_opt_ LPVOID lpEnvironment,
                                        _In_opt_ LPCWSTR lpCurrentDirectory,
                                        _In_ LPSTARTUPINFOW lpStartupInfo,
                                        _Out_ LPPROCESS_INFORMATION lpProcessInformation,
                                        _In_ LPCSTR lpDllName,
                                        _In_opt_ PDETOUR_CREATE_PROCESS_ROUTINEW pfCreateProcessW) {
    DWORD dwMyCreationFlags = (dwCreationFlags | CREATE_SUSPENDED);
    PROCESS_INFORMATION pi;

    if (pfCreateProcessW == NULL) {
        pfCreateProcessW = CreateProcessW;
    }

    BOOL fResult = pfCreateProcessW(lpApplicationName,
                                    lpCommandLine,
                                    lpProcessAttributes,
                                    lpThreadAttributes,
                                    bInheritHandles,
                                    dwMyCreationFlags,
                                    lpEnvironment,
                                    lpCurrentDirectory,
                                    lpStartupInfo,
                                    &pi);

    if (lpProcessInformation) {
        CopyMemory(lpProcessInformation, &pi, sizeof(pi));
    }

    if (!fResult) {
        return FALSE;
    }

    LPCSTR rlpDlls[2];
    DWORD nDlls = 0;
    if (lpDllName != NULL) {
        rlpDlls[nDlls++] = lpDllName;
    }

    if (!DetourUpdateProcessWithDll(pi.hProcess, rlpDlls, nDlls)) {
        TerminateProcess(pi.hProcess, ~0u);
        return FALSE;
    }

    if (!(dwCreationFlags & CREATE_SUSPENDED)) {
        ResumeThread(pi.hThread);
    }
    return TRUE;
}
