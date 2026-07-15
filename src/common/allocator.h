#ifndef YAERMODLOADER_ALLOCATOR_H
#define YAERMODLOADER_ALLOCATOR_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <shlwapi.h>

#include <stddef.h>
void *yaer_local_alloc(UINT flags, size_t size);
void *yaer_local_realloc(void *ptr, size_t size, UINT flags);
void yaer_local_free(void *ptr);
char *yaer_strdup_a(const char *str);
wchar_t *yaer_strdup_w(const wchar_t *str);

#define LocalAlloc(flags, size) yaer_local_alloc((flags), (size))
#define LocalReAlloc(ptr, size, flags) yaer_local_realloc((ptr), (size), (flags))
#define LocalFree(ptr) yaer_local_free(ptr)
#define StrDupA(str) yaer_strdup_a(str)
#define StrDupW(str) yaer_strdup_w(str)

#endif
