/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "image.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void *get_module_image_base(const wchar_t *module_name, size_t *size) {
    const HMODULE hModule = GetModuleHandleW(module_name);
    if (hModule == NULL) {
        return NULL;
    }
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)hModule;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        return NULL;
    }
    const PIMAGE_NT_HEADERS ntHeader = (const PIMAGE_NT_HEADERS64)((DWORD_PTR)dosHeader + dosHeader->e_lfanew);
    if (ntHeader->Signature != IMAGE_NT_SIGNATURE) {
        return NULL;
    }
    *size = ntHeader->OptionalHeader.SizeOfImage;
    return hModule;
}
