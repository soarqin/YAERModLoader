/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * C11 port of the Elden Ring EzState (ESD) structure layouts, matching the
 * in-memory layout used by the game byte-for-byte (verified against the
 * Glorious Merchant reverse engineering). std::span<T> is replaced by
 * {T *data; size_t count;} pairs.
 */

#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct er_ezstate_state_s er_ezstate_state_t;
typedef struct er_ezstate_state_group_s er_ezstate_state_group_t;
typedef struct er_ezstate_event_s er_ezstate_event_t;
typedef struct er_ezstate_transition_s er_ezstate_transition_t;

typedef struct er_ezstate_command_s {
    int bank;
    int id;
} er_ezstate_command_t;

typedef struct er_ezstate_arg_s {
    unsigned char *data;
    size_t count;
} er_ezstate_arg_t;

struct er_ezstate_event_s {
    er_ezstate_command_t command;
    er_ezstate_arg_t *args;
    size_t args_count;
};

struct er_ezstate_transition_s {
    er_ezstate_state_t *target_state;
    er_ezstate_event_t *pass_events;
    size_t pass_events_count;
    er_ezstate_transition_t **sub_transitions;
    size_t sub_count;
    unsigned char *evaluator;
    size_t evaluator_count;
};

struct er_ezstate_state_s {
    int id;
    int _pad0;
    er_ezstate_transition_t **transitions;
    size_t transitions_count;
    er_ezstate_event_t *entry_events;
    size_t entry_events_count;
    er_ezstate_event_t *exit_events;
    size_t exit_events_count;
    er_ezstate_event_t *while_events;
    size_t while_events_count;
};

struct er_ezstate_state_group_s {
    int id;
    int _pad0;
    er_ezstate_state_t *states;
    size_t states_count;
    er_ezstate_state_t *initial_state;
};

typedef struct er_ezstate_machine_impl_s {
    void *vtable;
    unsigned char unk1[0x20];
    er_ezstate_state_group_t *state_group;
    unsigned char unk2[0x110];
} er_ezstate_machine_impl_t;

#ifdef __cplusplus
}
#endif