#include "save_mapping.h"

#include "modloader/vfs.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include <stdint.h>
#include <wchar.h>

static SRWLOCK mapping_lock = SRWLOCK_INIT;
static wchar_t *save_root;
static wchar_t configured_name[64];

static wchar_t *join_path(const wchar_t *left, const wchar_t *right) {
    size_t left_length;
    size_t right_length;
    bool separator;
    wchar_t *result;
    if (left == NULL || right == NULL) return NULL;
    left_length = wcslen(left);
    right_length = wcslen(right);
    separator = left_length != 0 && left[left_length - 1] != L'\\' && left[left_length - 1] != L'/';
    if (left_length > SIZE_MAX - right_length - (separator ? 2 : 1)) return NULL;
    result = LocalAlloc(0, (left_length + right_length + (separator ? 2 : 1)) * sizeof(*result));
    if (result == NULL) return NULL;
    memcpy(result, left, left_length * sizeof(*result));
    if (separator) result[left_length++] = L'\\';
    memcpy(result + left_length, right, (right_length + 1) * sizeof(*result));
    return result;
}

static wchar_t *canonicalize_path(const wchar_t *path) {
    DWORD capacity;
    if (path == NULL) return NULL;
    capacity = GetFullPathNameW(path, 0, NULL, NULL);
    while (capacity != 0) {
        wchar_t *result = LocalAlloc(0, (size_t)capacity * sizeof(*result));
        DWORD length;
        if (result == NULL) return NULL;
        length = GetFullPathNameW(path, capacity, result, NULL);
        if (length == 0) {
            LocalFree(result);
            return NULL;
        }
        if (length < capacity) {
            while (length > 1 && (result[length - 1] == L'\\' || result[length - 1] == L'/')) {
                result[--length] = L'\0';
            }
            return result;
        }
        LocalFree(result);
        capacity = length + 1;
    }
    return NULL;
}

static wchar_t *environment_value(const wchar_t *name) {
    DWORD capacity = GetEnvironmentVariableW(name, NULL, 0);
    while (capacity != 0) {
        wchar_t *result = LocalAlloc(0, (size_t)capacity * sizeof(*result));
        DWORD length;
        if (result == NULL) return NULL;
        length = GetEnvironmentVariableW(name, result, capacity);
        if (length == 0) {
            LocalFree(result);
            return NULL;
        }
        if (length < capacity) return result;
        LocalFree(result);
        capacity = length + 1;
    }
    return NULL;
}

static bool path_is_under_root(const wchar_t *canonical, const wchar_t *root) {
    size_t root_length = root == NULL ? 0 : wcslen(root);
    return root_length != 0 && wcslen(canonical) > root_length &&
           _wcsnicmp(canonical, root, root_length) == 0 &&
           (canonical[root_length] == L'\\' || canonical[root_length] == L'/');
}

static bool path_contains_reparse_point(const wchar_t *canonical, const wchar_t *root) {
    size_t root_length = wcslen(root);
    wchar_t *prefix = StrDupW(canonical);
    wchar_t *cursor;
    DWORD attributes;
    if (prefix == NULL) return true;
    cursor = prefix + root_length;
    for (;;) {
        wchar_t saved;
        while (*cursor == L'\\' || *cursor == L'/') cursor++;
        while (*cursor != L'\0' && *cursor != L'\\' && *cursor != L'/') cursor++;
        saved = *cursor;
        *cursor = L'\0';
        attributes = GetFileAttributesW(prefix);
        *cursor = saved;
        if (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0) {
            LocalFree(prefix);
            return true;
        }
        if (saved == L'\0') break;
    }
    LocalFree(prefix);
    return false;
}

static wchar_t *build_override_name(const wchar_t *source_name, const wchar_t *override_name) {
    const wchar_t *extension;
    size_t stem_length;
    size_t suffix_length;
    wchar_t *result;
    if (override_name[0] != L'.') return StrDupW(override_name);
    extension = PathFindExtensionW(source_name);
    stem_length = (size_t)(extension - source_name);
    suffix_length = wcslen(override_name);
    if (stem_length > SIZE_MAX - suffix_length - 1) return NULL;
    result = LocalAlloc(0, (stem_length + suffix_length + 1) * sizeof(*result));
    if (result == NULL) return NULL;
    memcpy(result, source_name, stem_length * sizeof(*result));
    memcpy(result + stem_length, override_name, (suffix_length + 1) * sizeof(*result));
    return result;
}

static bool valid_override_name(const wchar_t *name) {
    static const wchar_t *reserved[] = { L"con", L"prn", L"aux", L"nul" };
    const wchar_t *extension;
    size_t stem_length;
    size_t length = wcslen(name);
    if (length == 0 || length >= 64 || name[length - 1] == L' ' || name[length - 1] == L'.') return false;
    for (const wchar_t *p = name; *p != L'\0'; p++) {
        if (*p < 32 || wcschr(L"<>:\"/\\|?*", *p) != NULL) return false;
    }
    if (name[0] == L'.') return length > 1;
    extension = wcschr(name, L'.');
    stem_length = extension == NULL ? length : (size_t)(extension - name);
    for (size_t i = 0; i < sizeof(reserved) / sizeof(reserved[0]); i++) {
        if (wcslen(reserved[i]) == stem_length && _wcsnicmp(name, reserved[i], stem_length) == 0) return false;
    }
    if (stem_length == 4 && (_wcsnicmp(name, L"com", 3) == 0 || _wcsnicmp(name, L"lpt", 3) == 0) &&
        name[3] >= L'1' && name[3] <= L'9') return false;
    return true;
}

bool ml_save_mapping_init(const ml_game_descriptor_t *game, const wchar_t *override_name) {
    wchar_t *appdata;
    wchar_t *joined;
    wchar_t *canonical;
    if (game == NULL || game->save_root_name == NULL || override_name == NULL || override_name[0] == L'\0') {
        return false;
    }
    if (!valid_override_name(override_name)) return false;
    appdata = environment_value(L"APPDATA");
    joined = appdata == NULL ? NULL : join_path(appdata, game->save_root_name);
    canonical = joined == NULL ? NULL : canonicalize_path(joined);
    LocalFree(joined);
    LocalFree(appdata);
    if (canonical == NULL) return false;

    AcquireSRWLockExclusive(&mapping_lock);
    LocalFree(save_root);
    save_root = canonical;
    lstrcpynW(configured_name, override_name, 64);
    configured_name[63] = L'\0';
    ReleaseSRWLockExclusive(&mapping_lock);
    return true;
}

bool ml_save_mapping_route(const wchar_t *path, const wchar_t **mapped_path) {
    wchar_t *source;
    wchar_t *logical_source;
    wchar_t *target = NULL;
    wchar_t *target_name = NULL;
    wchar_t *root_snapshot;
    wchar_t name_snapshot[64];
    const wchar_t *source_name;
    bool backup;
    const wchar_t *registered;

    if (mapped_path != NULL) *mapped_path = NULL;
    if (path == NULL || mapped_path == NULL) return false;
    AcquireSRWLockShared(&mapping_lock);
    root_snapshot = save_root == NULL ? NULL : StrDupW(save_root);
    lstrcpynW(name_snapshot, configured_name, 64);
    ReleaseSRWLockShared(&mapping_lock);
    if (root_snapshot == NULL || name_snapshot[0] == L'\0') {
        LocalFree(root_snapshot);
        return false;
    }
    source = canonicalize_path(path);
    if (source == NULL || !path_is_under_root(source, root_snapshot) ||
        path_contains_reparse_point(source, root_snapshot)) {
        LocalFree(root_snapshot);
        LocalFree(source);
        return false;
    }
    LocalFree(root_snapshot);
    registered = vfs_route_writable_path(path);
    if (registered != NULL) {
        *mapped_path = registered;
        LocalFree(source);
        return true;
    }

    backup = lstrcmpiW(PathFindExtensionW(source), L".bak") == 0;
    logical_source = StrDupW(source);
    if (logical_source == NULL) {
        LocalFree(source);
        return true;
    }
    if (backup) PathRemoveExtensionW(logical_source);
    if (lstrcmpiW(PathFindExtensionW(logical_source), L".sl2") != 0) {
        LocalFree(logical_source);
        LocalFree(source);
        return false;
    }
    source_name = PathFindFileNameW(logical_source);
    target_name = build_override_name(source_name, name_snapshot);
    if (target_name != NULL) {
        size_t directory_length = (size_t)(source_name - logical_source);
        wchar_t *directory = LocalAlloc(0, (directory_length + 1) * sizeof(*directory));
        if (directory != NULL) {
            memcpy(directory, logical_source, directory_length * sizeof(*directory));
            directory[directory_length] = L'\0';
            target = join_path(directory, target_name);
            LocalFree(directory);
        }
    }
    LocalFree(target_name);
    if (target == NULL) {
        LocalFree(logical_source);
        LocalFree(source);
        return true;
    }
    if (backup) {
        size_t length = wcslen(target);
        wchar_t *with_backup = LocalAlloc(0, (length + 5) * sizeof(*with_backup));
        if (with_backup == NULL) {
            LocalFree(target);
            LocalFree(logical_source);
            LocalFree(source);
            return true;
        }
        memcpy(with_backup, target, length * sizeof(*with_backup));
        memcpy(with_backup + length, L".bak", 5 * sizeof(*with_backup));
        LocalFree(target);
        target = with_backup;
    }

    AcquireSRWLockExclusive(&mapping_lock);
    registered = vfs_route_writable_path(path);
    if (registered == NULL) {
        if (!PathFileExistsW(target) && PathFileExistsW(source)) {
            vfs_recursion_guard_enter();
            if (!CopyFileW(source, target, TRUE) && GetLastError() != ERROR_FILE_EXISTS) {
                vfs_recursion_guard_leave();
                ReleaseSRWLockExclusive(&mapping_lock);
                LocalFree(target);
                LocalFree(logical_source);
                LocalFree(source);
                return true;
            }
            vfs_recursion_guard_leave();
        }
        if (vfs_register_writable_path(path, target)) registered = vfs_route_writable_path(path);
    }
    *mapped_path = registered;
    ReleaseSRWLockExclusive(&mapping_lock);
    LocalFree(target);
    LocalFree(logical_source);
    LocalFree(source);
    return true;
}

void ml_save_mapping_uninit(void) {
    AcquireSRWLockExclusive(&mapping_lock);
    LocalFree(save_root);
    save_root = NULL;
    configured_name[0] = L'\0';
    ReleaseSRWLockExclusive(&mapping_lock);
}
