/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "cpu_affinity.h"

static int is_usable_cpu_set(const process_cpu_set_info_t *set) {
    return set && (!set->allocated || set->allocated_to_target_process);
}

static int find_efficiency_classes(
    const process_cpu_set_info_t *sets,
    const size_t set_count,
    uint8_t *min_class,
    int *has_higher_class) {
    int found = 0;
    *has_higher_class = 0;
    for (size_t i = 0; i < set_count; i++) {
        if (!is_usable_cpu_set(&sets[i]))
            continue;
        if (!found || sets[i].efficiency_class < *min_class) {
            *min_class = sets[i].efficiency_class;
            found = 1;
        }
    }
    if (!found)
        return 0;
    for (size_t i = 0; i < set_count; i++) {
        if (is_usable_cpu_set(&sets[i]) && sets[i].efficiency_class > *min_class) {
            *has_higher_class = 1;
            break;
        }
    }
    return 1;
}

static int is_lower_logical_cpu(const process_cpu_set_info_t *lhs, const process_cpu_set_info_t *rhs) {
    if (lhs->group != rhs->group)
        return lhs->group < rhs->group;
    if (lhs->logical_processor_index != rhs->logical_processor_index)
        return lhs->logical_processor_index < rhs->logical_processor_index;
    return lhs->id < rhs->id;
}

static int find_first_matching_cpu_set(
    const process_cpu_set_info_t *sets,
    const size_t set_count,
    const int strategy,
    const uint8_t min_class,
    process_cpu_set_info_t *first) {
    int found = 0;
    for (size_t i = 0; i < set_count; i++) {
        if (!is_usable_cpu_set(&sets[i]))
            continue;
        if (strategy == 4 && sets[i].efficiency_class <= min_class)
            continue;
        if (!found || is_lower_logical_cpu(&sets[i], first)) {
            *first = sets[i];
            found = 1;
        }
    }
    return found;
}

static int should_select_cpu_set(
    const int strategy,
    const process_cpu_set_info_t *set,
    const uint8_t min_class,
    const process_cpu_set_info_t *excluded) {
    if (!is_usable_cpu_set(set))
        return 0;
    if (excluded && set->id == excluded->id)
        return 0;
    switch (strategy) {
        case 1:
            return 1;
        case 2:
            return set->efficiency_class == min_class;
        case 3:
        case 4:
            return set->efficiency_class > min_class;
        default:
            return 0;
    }
}

size_t select_process_cpu_set_ids(
    const int strategy,
    const process_cpu_set_info_t *sets,
    const size_t set_count,
    process_cpu_set_id_t *ids,
    const size_t ids_capacity) {
    if (!sets || strategy < 1 || strategy > 4)
        return 0;

    uint8_t min_class = 0;
    int has_higher_class = 0;
    if (!find_efficiency_classes(sets, set_count, &min_class, &has_higher_class))
        return 0;

    if (strategy >= 2 && !has_higher_class)
        return 0;

    process_cpu_set_info_t excluded = {0};
    process_cpu_set_info_t *excluded_ptr = NULL;
    if ((strategy == 1 || strategy == 4) &&
        find_first_matching_cpu_set(sets, set_count, strategy, min_class, &excluded)) {
        excluded_ptr = &excluded;
    }

    size_t selected_count = 0;
    for (size_t i = 0; i < set_count; i++) {
        if (!should_select_cpu_set(strategy, &sets[i], min_class, excluded_ptr))
            continue;
        if (ids && selected_count < ids_capacity)
            ids[selected_count] = sets[i].id;
        selected_count++;
    }
    return selected_count;
}
