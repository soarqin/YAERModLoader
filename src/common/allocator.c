#include "allocator.h"

#ifdef YAERMODLOADER_USE_MIMALLOC
#include <mimalloc.h>

void *yaer_local_alloc(UINT flags, size_t size) {
    return (flags & LMEM_ZEROINIT) ? mi_zalloc(size) : mi_malloc(size);
}

void *yaer_local_realloc(void *ptr, size_t size, UINT flags) {
    return (flags & LMEM_ZEROINIT) ? mi_rezalloc(ptr, size) : mi_realloc(ptr, size);
}

void yaer_local_free(void *ptr) {
    mi_free(ptr);
}

char *yaer_strdup_a(const char *str) {
    return mi_strdup(str);
}

wchar_t *yaer_strdup_w(const wchar_t *str) {
    return mi_wcsdup(str);
}
#else
#include <stdlib.h>

void *yaer_local_alloc(UINT flags, size_t size) {
    return (flags & LMEM_ZEROINIT) ? calloc(1, size) : malloc(size);
}

void *yaer_local_realloc(void *ptr, size_t size, UINT flags) {
    return (flags & LMEM_ZEROINIT) ? _recalloc(ptr, 1, size) : realloc(ptr, size);
}

void yaer_local_free(void *ptr) {
    free(ptr);
}

char *yaer_strdup_a(const char *str) {
    return _strdup(str);
}

wchar_t *yaer_strdup_w(const wchar_t *str) {
    return _wcsdup(str);
}
#endif
