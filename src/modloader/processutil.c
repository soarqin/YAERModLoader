/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "processutil.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sysinfoapi.h>
#include <stdint.h>
#include <stdio.h>

void set_process_cpu_affinity_strategy(int strategy) {
    DWORD len = 0;
    GetLogicalProcessorInformationEx(RelationProcessorCore, NULL, &len);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) return;
    char *data = malloc(len);
    if (!data) return;
    if (!GetLogicalProcessorInformationEx(RelationProcessorCore, (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)data, &len)) {
        free(data);
        return;
    }
    uint64_t masks[256] = {};
    uint64_t all_masks = 0;
    uint64_t nonzero_masks = 0;
    DWORD offset = 0;
    while (offset < len) {
        const SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *info = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)(data + offset);
        offset += info->Size;
        const uint64_t mask = info->Processor.GroupMask[0].Mask;
        BYTE eff = info->Processor.EfficiencyClass;
        masks[eff] |= mask;
        all_masks |= mask;
        if (eff > 0)
            nonzero_masks |= mask;
    }
    free(data);

    uint64_t process_mask;
    uint64_t system_mask;
    GetProcessAffinityMask(GetCurrentProcess(), &process_mask, &system_mask);
    switch (strategy) {
        case 1:
            SetProcessAffinityMask(GetCurrentProcess(), all_masks & ~1ULL & system_mask);
            break;
        case 2:
            if (!nonzero_masks) break;
            for (int i = 0; i < 256; i++) {
                if (masks[i]) {
                    SetProcessAffinityMask(GetCurrentProcess(), masks[i] & system_mask);
                    break;
                }
            }
            break;
        case 3:
            if (!nonzero_masks) break;
            for (int i = 255; i > 0; i--) {
                if (masks[i]) {
                    SetProcessAffinityMask(GetCurrentProcess(), masks[i] & system_mask);
                    break;
                }
            }
            break;
        case 4:
            if (!nonzero_masks) break;
            for (int i = 255; i > 0; i--) {
                if (masks[i]) {
                    uint64_t m = masks[i];
                    for (int j = 0; j < 64; j++) {
                        if (m & (1ULL << j)) {
                            m &= ~(1ULL << j);
                            break;
                        }
                    }
                    SetProcessAffinityMask(GetCurrentProcess(), m & system_mask);
                    break;
                }
            }
            break;
        default:
            break;
    }
}
