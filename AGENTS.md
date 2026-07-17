# AGENTS.md — YAERModLoader

## What this repo is

A Windows-only C11 mod loader for Elden Ring (`YAERModLoader`). Produces two primary artifacts:
- `YAERModLoader.exe` — standalone launcher (`modloader_launcher`, WIN32 subsystem)
- `YAERModLoader.dll` — injected DLL (`modloader_dll`, proxy for `dxgi.dll` / `dinput8.dll` / `winhttp.dll`)

When comparing or porting behavior from me3, use `docs/me3-repo.md` as the source of truth for the repository, branch, and synced commit. Do not infer the comparison baseline from whichever me3 working tree happens to be checked out. The cache dictionary system intentionally follows the performance optimization in the documented me3 fork; treat it as the project's chosen me3 implementation, not as a parity difference from the original repository.

Optional extension DLLs live under `src/extdlls/` (e.g. `autoloot`, `no_dup_loot`, `itemlot_rate`, `almighty_kale`). Each subdirectory with source files is auto-discovered and built as a separate shared library.

## Build system

CMake + MSVC (Visual Studio 2026 Community observed in build cache). No Makefile, no npm, no Python build step.

**Configure (out-of-source, debug):**
```
cmake -S . -B cmake-build-debug -G "Visual Studio 18 2026" -DBUILD_TESTING=ON
```

**Build:**
```
cmake --build cmake-build-debug --config Debug
```

**Build release (with LTO + static CRT + stripped binary):**
```
cmake -S . -B cmake-build-release -G "Visual Studio 18 2026" -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release --config Release
```

**Distribution package** (zip + 7z in `<build>/dist/`):
```
cmake --build cmake-build-release --target dist
```

**Run tests (CTest):**
```
ctest --test-dir cmake-build-debug -C Debug --output-on-failure
```

Or build the `RUN_TESTS` target in Visual Studio.

## Build prerequisites

- MSVC (Visual Studio with C/C++ workload)
- NASM — required for `src/extdlls/autoloot/` (`.asm` file). CMake finds it via `CMAKE_ASM_NASM_COMPILER`. Install via scoop: `scoop install nasm`.
- Python + lxml — only needed to regenerate `src/extdlls/er_param/include/er_param/param_defs.h` from XML definitions (see codegen below).

## Source layout

```
src/
  common/         khash_wstr.h — wide-string hash table adapter (shared header, no .c)
  modloader/      Core DLL: config, mod loading, file cache, game hooks, proxy stubs
    patches/      Game-specific patches (common + eldenring)
    proxy/        Proxy DLL stubs for dxgi/dinput8/winhttp
  launcher/       Standalone EXE: injects the DLL into the game process
  steam/          Steam API helpers (locate game folder via VDF; ISteamApps::GetCurrentGameLanguage)
  process/        PE image utilities, signature scanner
  extdlls/        Optional extension DLLs (auto-discovered by CMake glob)
    er_param/     Param provider DLL (param table access, pointers, wstring, cursor_speed; also exposes `from/` C struct headers + runtime pointer accessors via API v2)
    almighty_kale/ 1:1 C port of Glorious Merchant (free shops, gesture unlocks, Kalé-alive patch)
deps/
  klib/           khash.h (header-only, INTERFACE target `klib` / alias `klib::headers`)
  minhook/        Function hooking
  inih/           INI parser
  toml-c/         TOML parser (ModEngine2 config compatibility; can be stripped via -DSTRIP_MODENGINE_CONFIG_SUPPORT=ON)
  getopt/         wingetopt — command-line argument parsing
  lzma/           LZMA SDK (currently commented out in launcher link)
tests/
  smoke_filecache.c   Tests khash wstr table used by filecache
  smoke_no_dup_loot.c Tests khash int map used by no_dup_loot
  smoke_param.c       Tests khash wstr table used by param lookup
  test_common.h       Minimal assert macros (EXPECT_TRUE, EXPECT_EQ, EXPECT_STREQ_W, etc.)
```

## Key conventions

**Language:** C11 only. No C++. Headers use `#ifdef __cplusplus extern "C"` guards for potential C++ consumers.

**Memory:** The main loader DLL uses mimalloc. The launcher and extension DLLs use the C runtime allocator. Shared source keeps the existing `LocalAlloc`/`LocalFree` call sites; `src/common/allocator.h`, force-included by each target, maps them to the target allocator. Tests use standard `calloc`/`malloc` via the `kcalloc`/`kmalloc` macros redefined at the top of each test file.

**Hash tables:** `khash.h` (klib) is the only hash table. Two instantiation patterns in use:
- `KHASH_INIT(wstr, ...)` with `kh_wstr_hash_func`/`kh_wstr_hash_equal` — wide-string keys, defined in `src/common/khash_wstr.h`
- `KHASH_MAP_INIT_INT(name, value_type)` — integer keys

Always `#define kcalloc/kmalloc/krealloc/kfree` before `#include "khash.h"` in production files.

**Extension DLLs:** Project-owned ER extensions initialize from `DllMain` and share direct process/scanner/MinHook helpers from `src/common/ext_shared.*`; they do not depend on a modloader-specific extension ABI. Param-consuming extdlls obtain the provider through `er_param_api_get()` and must list `er_param` before themselves in the `[dlls]` ini section (load order dependency; no build-time runtime dependency system). External ModEngine extensions continue to use `modengine_ext_init`.

**er_param API v2:** `er_param_api_t` (in `src/extdlls/er_param/include/er_param/er_param_api.h`) is at `api_version = 2`. New function pointers are appended after `off_param_loaded` so existing field offsets are preserved for already-compiled consumers. The v2 additions expose scanned runtime addresses/pointers (`get_msg_repository`, `get_game_data_man`, `get_lookup_shop_menu`, `get_lookup_shop_lineup`, `get_msg_repository_lookup_entry`, `get_ezstate_enter_state`, `get_get_event_flag`, `get_get_sell_value`, `get_get_max_repository_num`, `get_open_regular_shop`) plus the `from/` C struct headers (`include/er_param/from/ezstate.h`, `talk_commands.h`, `messages.h`, `game_data.h`) matching the in-game layouts. `almighty_kale` is the primary consumer.

**Signature scanning:** Game function addresses are found at runtime via byte-pattern scanning (`sig_scan` or `ml_ext_sig_scan`). Patterns use `??` for wildcard bytes. Offsets in comments (e.g. `/* 0x5B8 for version < 1.12 */`) track version-specific differences.

**Param definitions codegen:** `src/extdlls/er_param/include/er_param/param_defs.h` and `src/extdlls/er_param/include/er_param/defs/*.h` are generated by `src/extdlls/er_param/param_to_c.py` from Elden Ring XML definition files (not in repo). Run the script manually when param structs need updating; it reads from `ER/Defs/` and `ER/Meta/` relative to the script's working directory (`src/extdlls/er_param/`).

**Version string:** Defined once in `src/CMakeLists.txt` as `YAERMODLOADER_VERSION`. Update there only.

**Unicode:** All file paths use `wchar_t`. MSVC `/utf-8` flag is set globally. Non-MSVC targets require `-municode` linker flag (already set in CMakeLists).

## Tests

Tests are smoke tests only — they test the hash table logic in isolation, not the full DLL. They compile against `klib` headers and `src/common/`. No mocking framework; failures print to stderr and return non-zero.

Tests are only built when `BUILD_TESTING=ON` is passed to CMake. Each test file is conditionally compiled only if the `.c` file exists (CMake checks `if(EXISTS ...)`), so adding a new test file is enough — no CMakeLists edit needed.

## Release process

Releases are automated via `.github/workflows/release.yml`. Before tagging a release:

1. **Update `CHANGELOG.md`** — add a new `#### X.Y.Z` section at the top listing all changes since the previous release.
2. **Update `src/CMakeLists.txt`** — change the `YAERMODLOADER_VERSION` value to match.
3. **Verify consistency** — the tag, `src/CMakeLists.txt`, and `CHANGELOG.md` must all carry the same version string.
4. **Tag and push** — use the format `vX.Y.Z` (e.g. `v0.5.0`). Pushing the tag triggers the workflow.

```
git add CHANGELOG.md src/CMakeLists.txt
git commit -m "chore: release vX.Y.Z"
git tag vX.Y.Z
git push origin main --tags
```

The workflow will fail fast if the version in `src/CMakeLists.txt` or `CHANGELOG.md` does not match the pushed tag.

## What to avoid

- Do not add C++ source files; the project is intentionally C11-only.
- Do not introduce direct `LocalAlloc`/`LocalFree` calls in new production code. Use `mi_*` in the main loader DLL and `malloc`/`free` in the launcher or extension DLLs; shared code continues to use the target-specific mappings in `src/common/allocator.h`.
- Do not edit `src/extdlls/er_param/include/er_param/defs/*.h` or `src/extdlls/er_param/include/er_param/param_defs.h` by hand; they are generated.
- Do not add new dependencies without a corresponding `deps/` subdirectory and CMakeLists entry.
- The `tools/` subdirectory is commented out in the root CMakeLists (`# add_subdirectory(tools)`); do not uncomment without understanding why.
- The LZMA embed step in `src/CMakeLists.txt` is also commented out; leave it unless intentionally re-enabling DLL embedding.
