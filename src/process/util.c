/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "util.h"
#include "cpu_affinity.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

void set_process_cpu_affinity_strategy(const int strategy) {
    if (strategy < 1 || strategy > 4)
        return;

    DWORD len = 0;
    if (GetSystemCpuSetInformation(NULL, 0, &len, GetCurrentProcess(), 0) ||
        GetLastError() != ERROR_INSUFFICIENT_BUFFER || len == 0)
        return;

    char *data = (char *)LocalAlloc(0, len);
    if (!data)
        return;

    if (!GetSystemCpuSetInformation((PSYSTEM_CPU_SET_INFORMATION)data, len, &len, GetCurrentProcess(), 0)) {
        LocalFree(data);
        return;
    }

    size_t set_count = 0;
    DWORD offset = 0;
    while (offset < len) {
        const SYSTEM_CPU_SET_INFORMATION *info = (SYSTEM_CPU_SET_INFORMATION*)(data + offset);
        if (info->Size == 0)
            break;
        if (info->Type == CpuSetInformation)
            set_count++;
        offset += info->Size;
    }

    if (set_count == 0) {
        LocalFree(data);
        return;
    }

    process_cpu_set_info_t *sets = (process_cpu_set_info_t *)LocalAlloc(0, sizeof(process_cpu_set_info_t) * set_count);
    if (!sets) {
        LocalFree(data);
        return;
    }

    size_t set_index = 0;
    offset = 0;
    while (offset < len && set_index < set_count) {
        const SYSTEM_CPU_SET_INFORMATION *info = (SYSTEM_CPU_SET_INFORMATION*)(data + offset);
        if (info->Size == 0)
            break;
        if (info->Type == CpuSetInformation) {
            sets[set_index].id = info->CpuSet.Id;
            sets[set_index].group = info->CpuSet.Group;
            sets[set_index].logical_processor_index = info->CpuSet.LogicalProcessorIndex;
            sets[set_index].efficiency_class = info->CpuSet.EfficiencyClass;
            sets[set_index].allocated = info->CpuSet.Allocated;
            sets[set_index].allocated_to_target_process = info->CpuSet.AllocatedToTargetProcess;
            set_index++;
        }
        offset += info->Size;
    }
    LocalFree(data);

    process_cpu_set_id_t *ids = (process_cpu_set_id_t *)LocalAlloc(0, sizeof(process_cpu_set_id_t) * set_index);
    if (!ids) {
        LocalFree(sets);
        return;
    }

    const size_t selected_count = select_process_cpu_set_ids(strategy, sets, set_index, ids, set_index);
    if (selected_count > 0 && selected_count <= (size_t)ULONG_MAX) {
        SetProcessDefaultCpuSets(GetCurrentProcess(), (const ULONG *)ids, (ULONG)selected_count);
    }
    LocalFree(ids);
    LocalFree(sets);
}
