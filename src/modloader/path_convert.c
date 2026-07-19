#include "path_convert.h"

#include "allocator.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

wchar_t *ml_path_from_ansi(const char *path) {
    int length;
    wchar_t *wide;
    if (path == NULL) return NULL;
    length = MultiByteToWideChar(CP_ACP, 0, path, -1, NULL, 0);
    if (length <= 0) return NULL;
    wide = ml_mem_alloc(0, (size_t)length * sizeof(*wide));
    if (wide == NULL) return NULL;
    if (MultiByteToWideChar(CP_ACP, 0, path, -1, wide, length) == 0) {
        ml_mem_free(wide);
        return NULL;
    }
    return wide;
}
