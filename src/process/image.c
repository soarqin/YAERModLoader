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
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE || dosHeader->e_lfanew <= 0) {
        return NULL;
    }
    const PIMAGE_NT_HEADERS ntHeader = (const PIMAGE_NT_HEADERS64)((DWORD_PTR)dosHeader + dosHeader->e_lfanew);
    if (ntHeader->Signature != IMAGE_NT_SIGNATURE ||
        ntHeader->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
        return NULL;
    }
    *size = ntHeader->OptionalHeader.SizeOfImage;
    return hModule;
}

void *get_module_entrypoint(const wchar_t *module_name) {
    size_t image_size;
    BYTE *image_base = get_module_image_base(module_name, &image_size);
    if (image_base == NULL) {
        return NULL;
    }
    const PIMAGE_DOS_HEADER dos_header = (const PIMAGE_DOS_HEADER)image_base;
    const PIMAGE_NT_HEADERS nt_header =
        (const PIMAGE_NT_HEADERS)(image_base + dos_header->e_lfanew);
    const DWORD entrypoint = nt_header->OptionalHeader.AddressOfEntryPoint;
    if (nt_header->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC ||
        entrypoint == 0 || entrypoint >= image_size) {
        return NULL;
    }
    return image_base + entrypoint;
}
