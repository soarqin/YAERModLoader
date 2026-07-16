#pragma once

#include <stdbool.h>

bool ml_win32_file_hooks_install(void);
void ml_win32_file_hooks_uninstall(void);

#ifdef ML_WIN32_HOOKS_TEST
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
void ml_win32_file_hooks_test_init(void);
HANDLE ml_win32_file_hooks_test_create_file_w(LPCWSTR path, DWORD access, DWORD share,
                                               DWORD disposition, DWORD flags);
HANDLE ml_win32_file_hooks_test_create_file_2(LPCWSTR path, DWORD access, DWORD share,
                                               DWORD disposition);
BOOL ml_win32_file_hooks_test_copy_file_w(LPCWSTR source, LPCWSTR target);
BOOL ml_win32_file_hooks_test_move_file_ex_w(LPCWSTR source, LPCWSTR target);
BOOL ml_win32_file_hooks_test_create_directory_w(LPCWSTR path);
BOOL ml_win32_file_hooks_test_delete_file_w(LPCWSTR path);
#endif
