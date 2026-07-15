/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "lifecycle.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef struct ml_phase_observer_s {
    ml_lifecycle_phase_t phase;
    ml_lifecycle_callback_t callback;
    void *userp;
    bool invoked;
} ml_phase_observer_t;

static SRWLOCK observers_lock = SRWLOCK_INIT;
static ml_phase_observer_t *observers;
static size_t observer_count;
static size_t observer_capacity;
static volatile LONG current_phase;

void ml_lifecycle_init(void) {
    AcquireSRWLockExclusive(&observers_lock);
    LocalFree(observers);
    observers = NULL;
    observer_count = 0;
    observer_capacity = 0;
    InterlockedExchange(&current_phase, ML_LIFECYCLE_PHASE_UNKNOWN);
    ReleaseSRWLockExclusive(&observers_lock);
}

void ml_lifecycle_uninit(void) {
    ml_lifecycle_init();
}

ml_lifecycle_phase_t ml_lifecycle_current(void) {
    return (ml_lifecycle_phase_t)InterlockedCompareExchange(&current_phase, 0, 0);
}

bool ml_lifecycle_on_phase(ml_lifecycle_phase_t phase, ml_lifecycle_callback_t callback, void *userp) {
    if (phase <= ML_LIFECYCLE_PHASE_UNKNOWN || phase > ML_LIFECYCLE_PHASE_AFTER_PROPERTIES_READY || callback == NULL) {
        return false;
    }

    AcquireSRWLockExclusive(&observers_lock);
    if (phase <= ml_lifecycle_current()) {
        ReleaseSRWLockExclusive(&observers_lock);
        callback(phase, userp);
        return true;
    }
    if (observer_count == observer_capacity) {
        size_t capacity = observer_capacity == 0 ? 8 : observer_capacity * 2;
        ml_phase_observer_t *new_observers = observers == NULL
            ? LocalAlloc(LMEM_ZEROINIT, capacity * sizeof(*observers))
            : LocalReAlloc(observers, capacity * sizeof(*observers), LMEM_MOVEABLE | LMEM_ZEROINIT);
        if (new_observers == NULL) {
            ReleaseSRWLockExclusive(&observers_lock);
            return false;
        }
        observers = new_observers;
        observer_capacity = capacity;
    }
    observers[observer_count++] = (ml_phase_observer_t){ phase, callback, userp, false };
    ReleaseSRWLockExclusive(&observers_lock);
    return true;
}

bool ml_lifecycle_advance(ml_lifecycle_phase_t phase) {
    ml_lifecycle_phase_t previous;
    if (phase <= ML_LIFECYCLE_PHASE_UNKNOWN || phase > ML_LIFECYCLE_PHASE_AFTER_PROPERTIES_READY) return false;

    previous = ml_lifecycle_current();
    if (phase < previous) return false;
    if (phase == previous) return true;
    InterlockedExchange(&current_phase, phase);

    for (;;) {
        ml_lifecycle_callback_t callback = NULL;
        ml_lifecycle_phase_t callback_phase = ML_LIFECYCLE_PHASE_UNKNOWN;
        void *userp = NULL;

        AcquireSRWLockExclusive(&observers_lock);
        for (size_t i = 0; i < observer_count; i++) {
            if (!observers[i].invoked && observers[i].phase <= phase) {
                observers[i].invoked = true;
                callback = observers[i].callback;
                callback_phase = observers[i].phase;
                userp = observers[i].userp;
                break;
            }
        }
        ReleaseSRWLockExclusive(&observers_lock);
        if (callback == NULL) break;
        callback(callback_phase, userp);
    }
    return true;
}
