#ifndef ML_ALLOCATOR_H
#define ML_ALLOCATOR_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <shlwapi.h>

#include <stddef.h>
#if defined(ML_USE_WIN32_ALLOCATOR) && !defined(ML_USE_TEST_ALLOCATOR)
#define yaer_mem_alloc LocalAlloc
#define yaer_mem_realloc LocalReAlloc
#define yaer_mem_free LocalFree
#define yaer_mem_strdup_a StrDupA
#define yaer_mem_strdup_w StrDupW
#else
void *yaer_mem_alloc(UINT flags, size_t size);
void *yaer_mem_realloc(void *ptr, size_t size, UINT flags);
void yaer_mem_free(void *ptr);
char *yaer_mem_strdup_a(const char *str);
wchar_t *yaer_mem_strdup_w(const wchar_t *str);
#endif

#endif
