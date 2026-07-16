#include "win32_hooks.h"

#include <MinHook.h>

#include "save_mapping.h"

#include "modloader/hook.h"
#include "modloader/hook_batch.h"
#include "modloader/mod.h"
#include "modloader/path_convert.h"
#include "modloader/vfs.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>

typedef HANDLE (WINAPI *create_file_w_t)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef HANDLE (WINAPI *create_file_a_t)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef HANDLE (WINAPI *create_file_2_t)(LPCWSTR, DWORD, DWORD, DWORD, LPCREATEFILE2_EXTENDED_PARAMETERS);
typedef BOOL (WINAPI *delete_file_w_t)(LPCWSTR);
typedef BOOL (WINAPI *delete_file_a_t)(LPCSTR);
typedef BOOL (WINAPI *create_directory_w_t)(LPCWSTR, LPSECURITY_ATTRIBUTES);
typedef BOOL (WINAPI *create_directory_a_t)(LPCSTR, LPSECURITY_ATTRIBUTES);
typedef BOOL (WINAPI *create_directory_ex_w_t)(LPCWSTR, LPCWSTR, LPSECURITY_ATTRIBUTES);
typedef BOOL (WINAPI *copy_file_w_t)(LPCWSTR, LPCWSTR, BOOL);
typedef BOOL (WINAPI *copy_file_ex_w_t)(LPCWSTR, LPCWSTR, LPPROGRESS_ROUTINE, LPVOID, LPBOOL, DWORD);
typedef HRESULT (WINAPI *copy_file_2_t)(PCWSTR, PCWSTR, COPYFILE2_EXTENDED_PARAMETERS *);
typedef BOOL (WINAPI *copy_file_a_t)(LPCSTR, LPCSTR, BOOL);
typedef BOOL (WINAPI *copy_file_ex_a_t)(LPCSTR, LPCSTR, LPPROGRESS_ROUTINE, LPVOID, LPBOOL, DWORD);
typedef BOOL (WINAPI *move_file_ex_w_t)(LPCWSTR, LPCWSTR, DWORD);
typedef BOOL (WINAPI *replace_file_w_t)(LPCWSTR, LPCWSTR, LPCWSTR, DWORD, LPVOID, LPVOID);

static create_file_w_t old_create_file_w;
static create_file_a_t old_create_file_a;
static create_file_2_t old_create_file_2;
static delete_file_w_t old_delete_file_w;
static delete_file_a_t old_delete_file_a;
static create_directory_w_t old_create_directory_w;
static create_directory_a_t old_create_directory_a;
static create_directory_ex_w_t old_create_directory_ex_w;
static copy_file_w_t old_copy_file_w;
static copy_file_ex_w_t old_copy_file_ex_w;
static copy_file_2_t old_copy_file_2;
static copy_file_a_t old_copy_file_a;
static copy_file_ex_a_t old_copy_file_ex_a;
static move_file_ex_w_t old_move_file_ex_w;
static replace_file_w_t old_replace_file_w;
static bool hooks_installed;

static HANDLE WINAPI create_file_w_hooked(LPCWSTR path, DWORD access, DWORD share,
                                           LPSECURITY_ATTRIBUTES security, DWORD disposition,
                                           DWORD flags, HANDLE template_file);
static HANDLE WINAPI create_file_a_hooked(LPCSTR path, DWORD access, DWORD share,
                                           LPSECURITY_ATTRIBUTES security, DWORD disposition,
                                           DWORD flags, HANDLE template_file);
static HANDLE WINAPI create_file_2_hooked(LPCWSTR path, DWORD access, DWORD share, DWORD disposition,
                                           LPCREATEFILE2_EXTENDED_PARAMETERS parameters);
static BOOL WINAPI delete_file_w_hooked(LPCWSTR path);
static BOOL WINAPI delete_file_a_hooked(LPCSTR path);
static BOOL WINAPI create_directory_w_hooked(LPCWSTR path, LPSECURITY_ATTRIBUTES security);
static BOOL WINAPI create_directory_a_hooked(LPCSTR path, LPSECURITY_ATTRIBUTES security);
static BOOL WINAPI create_directory_ex_w_hooked(LPCWSTR template_path, LPCWSTR path,
                                                  LPSECURITY_ATTRIBUTES security);
static BOOL WINAPI copy_file_w_hooked(LPCWSTR existing_path, LPCWSTR new_path, BOOL fail_if_exists);
static BOOL WINAPI copy_file_ex_w_hooked(LPCWSTR existing_path, LPCWSTR new_path,
                                         LPPROGRESS_ROUTINE progress, LPVOID data,
                                         LPBOOL cancel, DWORD flags);
static HRESULT WINAPI copy_file_2_hooked(PCWSTR existing_path, PCWSTR new_path,
                                         COPYFILE2_EXTENDED_PARAMETERS *parameters);
static BOOL WINAPI copy_file_a_hooked(LPCSTR existing_path, LPCSTR new_path, BOOL fail_if_exists);
static BOOL WINAPI copy_file_ex_a_hooked(LPCSTR existing_path, LPCSTR new_path,
                                         LPPROGRESS_ROUTINE progress, LPVOID data,
                                         LPBOOL cancel, DWORD flags);
static BOOL WINAPI move_file_ex_w_hooked(LPCWSTR existing_path, LPCWSTR new_path, DWORD flags);
static BOOL WINAPI replace_file_w_hooked(LPCWSTR replaced_path, LPCWSTR replacement_path,
                                         LPCWSTR backup_path, DWORD flags,
                                         LPVOID exclude, LPVOID reserved);

static bool remove_hook(void *target) {
    MH_STATUS status = MH_RemoveHook(target);
    if (status == MH_OK || status == MH_ERROR_NOT_CREATED) return true;
    fwprintf(stderr, L"WARNING: [win32-vfs] failed to remove hook at %p: %d\n", target, status);
    return false;
}

static ml_hook_result_t install_hook(void *target, void *detour, void **original) {
    ml_hook_result_t result = ml_hook_install(target, detour, original);
    if (result != ML_HOOK_APPLIED) {
        fwprintf(stderr, L"WARNING: [win32-vfs] failed to install hook at %p: %hs\n",
                 target, ml_hook_result_name(result));
    }
    return result;
}

static void build_hook_specs(ml_hook_spec_t specs[15]) {
    specs[0] = (ml_hook_spec_t){ CreateFileW, create_file_w_hooked, (void **)&old_create_file_w };
    specs[1] = (ml_hook_spec_t){ CreateFileA, create_file_a_hooked, (void **)&old_create_file_a };
    specs[2] = (ml_hook_spec_t){ CreateFile2, create_file_2_hooked, (void **)&old_create_file_2 };
    specs[3] = (ml_hook_spec_t){ DeleteFileW, delete_file_w_hooked, (void **)&old_delete_file_w };
    specs[4] = (ml_hook_spec_t){ DeleteFileA, delete_file_a_hooked, (void **)&old_delete_file_a };
    specs[5] = (ml_hook_spec_t){ CreateDirectoryW, create_directory_w_hooked, (void **)&old_create_directory_w };
    specs[6] = (ml_hook_spec_t){ CreateDirectoryA, create_directory_a_hooked, (void **)&old_create_directory_a };
    specs[7] = (ml_hook_spec_t){ CreateDirectoryExW, create_directory_ex_w_hooked, (void **)&old_create_directory_ex_w };
    specs[8] = (ml_hook_spec_t){ CopyFileW, copy_file_w_hooked, (void **)&old_copy_file_w };
    specs[9] = (ml_hook_spec_t){ CopyFileExW, copy_file_ex_w_hooked, (void **)&old_copy_file_ex_w };
    specs[10] = (ml_hook_spec_t){ CopyFile2, copy_file_2_hooked, (void **)&old_copy_file_2 };
    specs[11] = (ml_hook_spec_t){ CopyFileA, copy_file_a_hooked, (void **)&old_copy_file_a };
    specs[12] = (ml_hook_spec_t){ CopyFileExA, copy_file_ex_a_hooked, (void **)&old_copy_file_ex_a };
    specs[13] = (ml_hook_spec_t){ MoveFileExW, move_file_ex_w_hooked, (void **)&old_move_file_ex_w };
    specs[14] = (ml_hook_spec_t){ ReplaceFileW, replace_file_w_hooked, (void **)&old_replace_file_w };
}

static bool route_copy_paths(LPCWSTR existing_path, LPCWSTR new_path,
                             const wchar_t **mapped_existing, const wchar_t **mapped_new) {
    bool existing_is_save;
    bool new_is_save;
    *mapped_existing = NULL;
    *mapped_new = NULL;
    existing_is_save = ml_save_mapping_route(existing_path, mapped_existing);
    new_is_save = ml_save_mapping_route(new_path, mapped_new);
    return (!existing_is_save || *mapped_existing != NULL) && (!new_is_save || *mapped_new != NULL);
}

static const wchar_t *route_wide(const wchar_t *path, DWORD access, DWORD disposition, bool *failed) {
    const wchar_t *mapped = NULL;
    *failed = false;
    if (vfs_recursion_guard_active()) return NULL;
    if (ml_save_mapping_route(path, &mapped)) {
        *failed = mapped == NULL;
        return mapped;
    }
    mapped = vfs_route_writable_path(path);
    return mapped != NULL ? mapped : mods_file_route_read(path, access, disposition);
}

static HANDLE WINAPI create_file_w_hooked(LPCWSTR path, DWORD access, DWORD share,
                                           LPSECURITY_ATTRIBUTES security, DWORD disposition,
                                           DWORD flags, HANDLE template_file) {
    bool failed;
    const wchar_t *mapped = route_wide(path, access, disposition, &failed);
    if (failed) {
        SetLastError(ERROR_CANNOT_MAKE);
        return INVALID_HANDLE_VALUE;
    }
    return old_create_file_w(mapped != NULL ? mapped : path, access, share, security, disposition, flags, template_file);
}

static HANDLE WINAPI create_file_a_hooked(LPCSTR path, DWORD access, DWORD share,
                                           LPSECURITY_ATTRIBUTES security, DWORD disposition,
                                           DWORD flags, HANDLE template_file) {
    wchar_t *wide = ml_path_from_ansi(path);
    bool failed;
    const wchar_t *mapped;
    if (wide != NULL) {
        mapped = route_wide(wide, access, disposition, &failed);
        if (failed) {
            LocalFree(wide);
            SetLastError(ERROR_CANNOT_MAKE);
            return INVALID_HANDLE_VALUE;
        }
        if (mapped != NULL) {
            HANDLE result = old_create_file_w(mapped, access, share, security, disposition, flags, template_file);
            LocalFree(wide);
            return result;
        }
    }
    LocalFree(wide);
    return old_create_file_a(path, access, share, security, disposition, flags, template_file);
}

static HANDLE WINAPI create_file_2_hooked(LPCWSTR path, DWORD access, DWORD share, DWORD disposition,
                                           LPCREATEFILE2_EXTENDED_PARAMETERS parameters) {
    bool failed;
    const wchar_t *mapped = route_wide(path, access, disposition, &failed);
    if (failed) {
        SetLastError(ERROR_CANNOT_MAKE);
        return INVALID_HANDLE_VALUE;
    }
    return old_create_file_2(mapped != NULL ? mapped : path, access, share, disposition, parameters);
}

static BOOL WINAPI delete_file_w_hooked(LPCWSTR path) {
    const wchar_t *mapped = NULL;
    if (vfs_recursion_guard_active()) return old_delete_file_w(path);
    if (ml_save_mapping_route(path, &mapped) && mapped == NULL) {
        SetLastError(ERROR_CANNOT_MAKE);
        return FALSE;
    }
    if (mapped == NULL) mapped = vfs_route_writable_path(path);
    return old_delete_file_w(mapped != NULL ? mapped : path);
}

static BOOL WINAPI delete_file_a_hooked(LPCSTR path) {
    wchar_t *wide;
    const wchar_t *mapped = NULL;
    if (vfs_recursion_guard_active()) return old_delete_file_a(path);
    wide = ml_path_from_ansi(path);
    if (wide == NULL) return old_delete_file_a(path);
    if (ml_save_mapping_route(wide, &mapped) && mapped == NULL) {
        LocalFree(wide);
        SetLastError(ERROR_CANNOT_MAKE);
        return FALSE;
    }
    if (mapped == NULL) mapped = vfs_route_writable_path(wide);
    BOOL result = mapped != NULL ? old_delete_file_w(mapped) : old_delete_file_a(path);
    LocalFree(wide);
    return result;
}

static BOOL WINAPI create_directory_w_hooked(LPCWSTR path, LPSECURITY_ATTRIBUTES security) {
    const wchar_t *mapped = vfs_route_writable_path(path);
    return old_create_directory_w(mapped != NULL ? mapped : path, security);
}

static BOOL WINAPI create_directory_a_hooked(LPCSTR path, LPSECURITY_ATTRIBUTES security) {
    wchar_t *wide = ml_path_from_ansi(path);
    const wchar_t *mapped = NULL;
    if (wide != NULL) mapped = vfs_route_writable_path(wide);
    BOOL result = mapped != NULL ? old_create_directory_w(mapped, security) : old_create_directory_a(path, security);
    LocalFree(wide);
    return result;
}

static BOOL WINAPI create_directory_ex_w_hooked(LPCWSTR template_path, LPCWSTR path,
                                                  LPSECURITY_ATTRIBUTES security) {
    const wchar_t *mapped = vfs_route_writable_path(path);
    return old_create_directory_ex_w(template_path, mapped != NULL ? mapped : path, security);
}

static BOOL WINAPI copy_file_w_hooked(LPCWSTR existing_path, LPCWSTR new_path, BOOL fail_if_exists) {
    const wchar_t *mapped_existing = NULL;
    const wchar_t *mapped_new = NULL;
    if (vfs_recursion_guard_active()) return old_copy_file_w(existing_path, new_path, fail_if_exists);
    if (!route_copy_paths(existing_path, new_path, &mapped_existing, &mapped_new)) {
        SetLastError(ERROR_CANNOT_MAKE);
        return FALSE;
    }
    return old_copy_file_w(mapped_existing != NULL ? mapped_existing : existing_path,
                           mapped_new != NULL ? mapped_new : new_path, fail_if_exists);
}

static BOOL WINAPI copy_file_ex_w_hooked(LPCWSTR existing_path, LPCWSTR new_path,
                                         LPPROGRESS_ROUTINE progress, LPVOID data,
                                         LPBOOL cancel, DWORD flags) {
    const wchar_t *mapped_existing = NULL;
    const wchar_t *mapped_new = NULL;
    if (vfs_recursion_guard_active()) {
        return old_copy_file_ex_w(existing_path, new_path, progress, data, cancel, flags);
    }
    if (!route_copy_paths(existing_path, new_path, &mapped_existing, &mapped_new)) {
        SetLastError(ERROR_CANNOT_MAKE);
        return FALSE;
    }
    return old_copy_file_ex_w(mapped_existing != NULL ? mapped_existing : existing_path,
                              mapped_new != NULL ? mapped_new : new_path,
                              progress, data, cancel, flags);
}

static HRESULT WINAPI copy_file_2_hooked(PCWSTR existing_path, PCWSTR new_path,
                                         COPYFILE2_EXTENDED_PARAMETERS *parameters) {
    const wchar_t *mapped_existing = NULL;
    const wchar_t *mapped_new = NULL;
    if (vfs_recursion_guard_active()) return old_copy_file_2(existing_path, new_path, parameters);
    if (!route_copy_paths(existing_path, new_path, &mapped_existing, &mapped_new)) {
        return HRESULT_FROM_WIN32(ERROR_CANNOT_MAKE);
    }
    return old_copy_file_2(mapped_existing != NULL ? mapped_existing : existing_path,
                           mapped_new != NULL ? mapped_new : new_path, parameters);
}

static BOOL WINAPI copy_file_a_hooked(LPCSTR existing_path, LPCSTR new_path, BOOL fail_if_exists) {
    wchar_t *wide_existing;
    wchar_t *wide_new;
    const wchar_t *mapped_existing = NULL;
    const wchar_t *mapped_new = NULL;
    BOOL result;
    if (vfs_recursion_guard_active()) return old_copy_file_a(existing_path, new_path, fail_if_exists);
    wide_existing = ml_path_from_ansi(existing_path);
    wide_new = ml_path_from_ansi(new_path);
    if (wide_existing == NULL || wide_new == NULL) {
        LocalFree(wide_existing);
        LocalFree(wide_new);
        return old_copy_file_a(existing_path, new_path, fail_if_exists);
    }
    if (!route_copy_paths(wide_existing, wide_new, &mapped_existing, &mapped_new)) {
        LocalFree(wide_existing);
        LocalFree(wide_new);
        SetLastError(ERROR_CANNOT_MAKE);
        return FALSE;
    }
    result = mapped_existing != NULL || mapped_new != NULL
        ? old_copy_file_w(mapped_existing != NULL ? mapped_existing : wide_existing,
                          mapped_new != NULL ? mapped_new : wide_new, fail_if_exists)
        : old_copy_file_a(existing_path, new_path, fail_if_exists);
    LocalFree(wide_existing);
    LocalFree(wide_new);
    return result;
}

static BOOL WINAPI copy_file_ex_a_hooked(LPCSTR existing_path, LPCSTR new_path,
                                         LPPROGRESS_ROUTINE progress, LPVOID data,
                                         LPBOOL cancel, DWORD flags) {
    wchar_t *wide_existing;
    wchar_t *wide_new;
    const wchar_t *mapped_existing = NULL;
    const wchar_t *mapped_new = NULL;
    BOOL result;
    if (vfs_recursion_guard_active()) {
        return old_copy_file_ex_a(existing_path, new_path, progress, data, cancel, flags);
    }
    wide_existing = ml_path_from_ansi(existing_path);
    wide_new = ml_path_from_ansi(new_path);
    if (wide_existing == NULL || wide_new == NULL) {
        LocalFree(wide_existing);
        LocalFree(wide_new);
        return old_copy_file_ex_a(existing_path, new_path, progress, data, cancel, flags);
    }
    if (!route_copy_paths(wide_existing, wide_new, &mapped_existing, &mapped_new)) {
        LocalFree(wide_existing);
        LocalFree(wide_new);
        SetLastError(ERROR_CANNOT_MAKE);
        return FALSE;
    }
    result = mapped_existing != NULL || mapped_new != NULL
        ? old_copy_file_ex_w(mapped_existing != NULL ? mapped_existing : wide_existing,
                             mapped_new != NULL ? mapped_new : wide_new, progress, data, cancel, flags)
        : old_copy_file_ex_a(existing_path, new_path, progress, data, cancel, flags);
    LocalFree(wide_existing);
    LocalFree(wide_new);
    return result;
}

static bool route_optional_save_path(LPCWSTR path, const wchar_t **mapped) {
    bool is_save;
    *mapped = NULL;
    if (path == NULL) return true;
    is_save = ml_save_mapping_route(path, mapped);
    return !is_save || *mapped != NULL;
}

static BOOL WINAPI move_file_ex_w_hooked(LPCWSTR existing_path, LPCWSTR new_path, DWORD flags) {
    const wchar_t *mapped_existing = NULL;
    const wchar_t *mapped_new = NULL;
    if (vfs_recursion_guard_active()) return old_move_file_ex_w(existing_path, new_path, flags);
    if (!route_optional_save_path(existing_path, &mapped_existing) ||
        !route_optional_save_path(new_path, &mapped_new)) {
        SetLastError(ERROR_CANNOT_MAKE);
        return FALSE;
    }
    return old_move_file_ex_w(mapped_existing != NULL ? mapped_existing : existing_path,
                              mapped_new != NULL ? mapped_new : new_path, flags);
}

static BOOL WINAPI replace_file_w_hooked(LPCWSTR replaced_path, LPCWSTR replacement_path,
                                         LPCWSTR backup_path, DWORD flags,
                                         LPVOID exclude, LPVOID reserved) {
    const wchar_t *mapped_replaced = NULL;
    const wchar_t *mapped_replacement = NULL;
    const wchar_t *mapped_backup = NULL;
    if (vfs_recursion_guard_active()) {
        return old_replace_file_w(replaced_path, replacement_path, backup_path, flags, exclude, reserved);
    }
    if (!route_optional_save_path(replaced_path, &mapped_replaced) ||
        !route_optional_save_path(replacement_path, &mapped_replacement) ||
        !route_optional_save_path(backup_path, &mapped_backup)) {
        SetLastError(ERROR_CANNOT_MAKE);
        return FALSE;
    }
    return old_replace_file_w(mapped_replaced != NULL ? mapped_replaced : replaced_path,
                              mapped_replacement != NULL ? mapped_replacement : replacement_path,
                              mapped_backup != NULL ? mapped_backup : backup_path,
                              flags, exclude, reserved);
}

bool ml_win32_file_hooks_install(void) {
    ml_hook_spec_t specs[15];
    bool rollback_complete;
    if (hooks_installed) return true;
    build_hook_specs(specs);
    bool result = ml_hook_batch_install(specs, 15, install_hook, remove_hook, &rollback_complete);
    hooks_installed = result || !rollback_complete;
    fwprintf(result ? stdout : stderr, result
        ? L"NOTE: [win32-vfs] file hooks APPLIED\n"
        : L"WARNING: [win32-vfs] file hooks HOOK_FAILED\n");
    if (!rollback_complete) {
        fwprintf(stderr, L"WARNING: [win32-vfs] hook rollback incomplete; uninstall will retry cleanup\n");
    }
    return result;
}

void ml_win32_file_hooks_uninstall(void) {
    ml_hook_spec_t specs[15];
    if (!hooks_installed) return;
    build_hook_specs(specs);
    if (ml_hook_batch_remove(specs, 15, remove_hook)) {
        hooks_installed = false;
    } else {
        fwprintf(stderr, L"WARNING: [win32-vfs] one or more file hooks could not be removed\n");
    }
}

#ifdef ML_WIN32_HOOKS_TEST
void ml_win32_file_hooks_test_init(void) {
    old_create_file_w = CreateFileW;
    old_create_file_a = CreateFileA;
    old_create_file_2 = CreateFile2;
    old_delete_file_w = DeleteFileW;
    old_delete_file_a = DeleteFileA;
    old_create_directory_w = CreateDirectoryW;
    old_create_directory_a = CreateDirectoryA;
    old_create_directory_ex_w = CreateDirectoryExW;
    old_copy_file_w = CopyFileW;
    old_copy_file_ex_w = CopyFileExW;
    old_copy_file_2 = CopyFile2;
    old_copy_file_a = CopyFileA;
    old_copy_file_ex_a = CopyFileExA;
    old_move_file_ex_w = MoveFileExW;
    old_replace_file_w = ReplaceFileW;
}

HANDLE ml_win32_file_hooks_test_create_file_w(LPCWSTR path, DWORD access, DWORD share,
                                               DWORD disposition, DWORD flags) {
    return create_file_w_hooked(path, access, share, NULL, disposition, flags, NULL);
}

HANDLE ml_win32_file_hooks_test_create_file_2(LPCWSTR path, DWORD access, DWORD share,
                                               DWORD disposition) {
    return create_file_2_hooked(path, access, share, disposition, NULL);
}

BOOL ml_win32_file_hooks_test_copy_file_w(LPCWSTR source, LPCWSTR target) {
    return copy_file_w_hooked(source, target, FALSE);
}

BOOL ml_win32_file_hooks_test_move_file_ex_w(LPCWSTR source, LPCWSTR target) {
    return move_file_ex_w_hooked(source, target, 0);
}

BOOL ml_win32_file_hooks_test_create_directory_w(LPCWSTR path) {
    return create_directory_w_hooked(path, NULL);
}

BOOL ml_win32_file_hooks_test_delete_file_w(LPCWSTR path) {
    return delete_file_w_hooked(path);
}
#endif
