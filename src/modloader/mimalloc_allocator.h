/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include "dl_allocator.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MIMALLOC_DL_ALLOCATOR_DEFAULT_HEAP_SIZE_MB 12288u

bool mimalloc_dl_allocator_prepare(size_t heap_size_mb);
dl_allocator_t *mimalloc_dl_allocator(void);

#ifdef __cplusplus
}
#endif
