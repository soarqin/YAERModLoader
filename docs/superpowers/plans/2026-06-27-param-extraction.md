# Param 接口移出主 Loader 实现计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 把 Elden Ring param 接口从主 mod loader 移出为独立 `er_param` provider DLL，主 loader 不再耦合 param/wstring/pointers；依赖 param 的 extdll 改经 `er_param_api_get()` 消费。

**Architecture:** 新建 `src/extdlls/er_param/` 顶层 extdll（含迁入的 param/pointers/wstring 实现与头），导出 `er_param_api_t`（观察者机制 + find_table）。主 loader `modloader_ext_api_t`/`modloader_ext_def_t` 重新锚定为 V1，移除 param 字段与 `on_param_initialized` 回调路径。extdlls glob 顶层 CMakeLists 扩展子目录分支，消费者 link `er_param::headers` INTERFACE 目标。

**Tech Stack:** C11, MSVC, CMake, MinHook, klib(khash), inih。验证靠 `cmake --build` + `ctest`（无游戏运行时单测；逻辑靠构建通过 + 代码审查）。

**参考设计:** `docs/superpowers/specs/2026-06-27-param-extraction-design.md`

**全局约定:**
- 生产代码用 `LocalAlloc`/`LocalFree`，测试用 `calloc`/`malloc`（AGENTS.md 约定）。
- 不加注释（除非要求）。
- 验证构建命令（所有构建类任务复用）:
  - 配置: `cmake -S . -B cmake-build-debug -G "Visual Studio 18 2026" -DBUILD_TESTING=ON`
  - 构建: `cmake --build cmake-build-debug --config Debug`
  - 测试: `ctest --test-dir cmake-build-debug -C Debug --output-on-failure`
- 每个 git commit 前先 `git status` 确认只含预期文件。

---

## 文件结构

**新建 `src/extdlls/er_param/`:**
- `CMakeLists.txt` — 自包含构建: SHARED `extdll_er_param` + INTERFACE `er_param::headers`
- `include/er_param/er_param_api.h` — `er_param_api_t` + `er_param_api_get_t`
- `include/er_param/param.h` — 迁自 `eldenring/param.h`（结构体 + 宏，内容不变）
- `include/er_param/wstring.h` — 迁自 `eldenring/wstring.h`（`er_wstring_impl_t` + 声明）
- `include/er_param/param_defs.h` — 迁自 `eldenring/param_defs.h`
- `include/er_param/defs/*.h` — 迁自 `eldenring/defs/*.h`（194 文件）
- `src/param.c` — 迁自 `eldenring/param.c`
- `src/param_internal.h` — 迁自 `eldenring/param_internal.h`
- `src/pointers.c` / `src/pointers.h` — 迁自 `eldenring/`
- `src/wstring.c` — 迁自 `eldenring/wstring.c`
- `src/provider.c` — 新增: `modloader_ext_init` + `er_param_api_get` + 观察者线程 + cursor_speed
- `param_to_c.py` — 迁自 `eldenring/param_to_c.py`
- `er_param.ini` — 新增

**修改:**
- `src/modloader/extdll_api.h` — 两个结构体改 V1
- `src/modloader/extdll.h` — 移除 `extdlls_on_param_initialized` 声明
- `src/modloader/extdll.c` — ext_api / extdll_t / load_all / unload_all
- `src/modloader/config.h` / `config.c` — 移除 `world_map_cursor_speed`
- `src/modloader/patches/eldenring.c` — async_operation_thread / uninstall / 内联 wstring / include
- `src/modloader/CMakeLists.txt` — 去 `eldenring`
- `src/CMakeLists.txt` — 去 `add_subdirectory(eldenring)`, dist 追加 er_param
- `src/extdlls/CMakeLists.txt` — glob 分支 + er_param::headers
- `src/extdlls/itemlot_rate/main.c` — 改 er_param api
- `src/extdlls/autoloot/main.c` — 改 er_param api
- `src/YAERModLoader.ini` — 移 world_map_cursor_speed, 加 er_param 示例
- `AGENTS.md` — 更新

**删除:** `src/eldenring/`（迁移后整体移除）

---

## Task 1: 建立基础构建配置 (er_param CMakeLists + 空目录骨架)

**Files:**
- Create: `src/extdlls/er_param/CMakeLists.txt`
- Create: `src/extdlls/er_param/include/er_param/er_param_api.h`

**说明:** 先建 CMake 骨架与接口头占位，使后续迁移文件有落点。此任务只创建结构与空接口头，不迁实现；构建可配置通过（无源文件则 extdll_er_param 暂为空库）。

- [ ] **Step 1: 创建接口头 `include/er_param/er_param_api.h`**

完整内容:

```c
/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <er_param/param.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct er_param_api_s {
    uint32_t api_version;
    const er_param_table_t *(*find_table)(const wchar_t *name);
    const wchar_t *(*wstring_str)(const er_wstring_impl_t *str);

    bool (*is_loaded)(void);
    bool (*on_param_loaded)(void (*cb)(void *userp), void *userp);
    void (*off_param_loaded)(void (*cb)(void *userp), void *userp);
} er_param_api_t;

typedef const er_param_api_t *(*er_param_api_get_t)(void);

#ifdef __cplusplus
}
#endif
```

- [ ] **Step 2: 创建 `src/extdlls/er_param/CMakeLists.txt`**

完整内容:

```cmake
# er_param provider DLL - 自包含构建, 导出 INTERFACE headers 供其他 extdll 消费
file(GLOB PARAM_DEF_SRC include/er_param/defs/*.h)

add_project(extdll_er_param SHARED
    src/provider.c
    src/param.c src/param_internal.h
    src/pointers.c src/pointers.h
    src/wstring.c
    include/er_param/er_param_api.h include/er_param/param.h include/er_param/wstring.h
    include/er_param/param_defs.h ${PARAM_DEF_SRC}
    LANGUAGES C FOLDER extdlls OUTPUT_SUBDIR dll NO_PREFIX OUTPUT_NAME er_param)

target_include_directories(${PROJECT_NAME} PRIVATE src include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/common)
target_link_libraries(${PROJECT_NAME} PRIVATE klib inih shlwapi)

add_library(er_param::headers INTERFACE)
target_include_directories(er_param::headers INTERFACE include)
```

**注意:** 此时 `src/provider.c` 等文件尚不存在, 配置阶段会因 `add_project` 列出的源文件缺失而失败。本任务先不配置构建, 仅建立文件骨架; Task 2 迁入实现后才能配置通过。因此本任务结束后**不验证构建**, 留到 Task 2 末尾。

- [ ] **Step 3: Commit**

```bash
git add src/extdlls/er_param/CMakeLists.txt src/extdlls/er_param/include/er_param/er_param_api.h
git commit -m "feat(er_param): add CMake skeleton and api header"
```

---

## Task 2: 迁移 eldenring 文件到 er_param (实现 + 头 + codegen)

**Files:**
- Move: `src/eldenring/param.c` → `src/extdlls/er_param/src/param.c`
- Move: `src/eldenring/param.h` → `src/extdlls/er_param/include/er_param/param.h`
- Move: `src/eldenring/param_internal.h` → `src/extdlls/er_param/src/param_internal.h`
- Move: `src/eldenring/param_defs.h` → `src/extdlls/er_param/include/er_param/param_defs.h`
- Move: `src/eldenring/defs/` → `src/extdlls/er_param/include/er_param/defs/`
- Move: `src/eldenring/pointers.c` → `src/extdlls/er_param/src/pointers.c`
- Move: `src/eldenring/pointers.h` → `src/extdlls/er_param/src/pointers.h`
- Move: `src/eldenring/wstring.c` → `src/extdlls/er_param/src/wstring.c`
- Move: `src/eldenring/wstring.h` → `src/extdlls/er_param/include/er_param/wstring.h`
- Move: `src/eldenring/param_to_c.py` → `src/extdlls/er_param/param_to_c.py`

**说明:** 用 `git mv` 保留历史。迁移后调整内部 include 路径。不删除原 `src/eldenring/CMakeLists.txt`(留到 Task 9 与目录一并删)。此任务后 eldenring 目录仍存在但被 er_param 引用, 主构建仍配置通过(因主 loader 还链接 eldenring, 见 Task 4 才解除)。

- [ ] **Step 1: 用 git mv 迁移文件**

```bash
cd src/extdlls/er_param
git mv ../../../src/eldenring/param.c src/param.c
git mv ../../../src/eldenring/param_internal.h src/param_internal.h
git mv ../../../src/eldenring/param.h include/er_param/param.h
git mv ../../../src/eldenring/param_defs.h include/er_param/param_defs.h
git mv ../../../src/eldenring/defs include/er_param/defs
git mv ../../../src/eldenring/pointers.c src/pointers.c
git mv ../../../src/eldenring/pointers.h src/pointers.h
git mv ../../../src/eldenring/wstring.c src/wstring.c
git mv ../../../src/eldenring/wstring.h include/er_param/wstring.h
git mv ../../../src/eldenring/param_to_c.py param_to_c.py
cd -
```

(在 Windows pwsh 下改用绝对路径 git mv, 逐条执行; 路径以仓库根为准:)

```bash
git mv src/eldenring/param.c src/extdlls/er_param/src/param.c
git mv src/eldenring/param_internal.h src/extdlls/er_param/src/param_internal.h
git mv src/eldenring/param.h src/extdlls/er_param/include/er_param/param.h
git mv src/eldenring/param_defs.h src/extdlls/er_param/include/er_param/param_defs.h
git mv src/eldenring/defs src/extdlls/er_param/include/er_param/defs
git mv src/eldenring/pointers.c src/extdlls/er_param/src/pointers.c
git mv src/eldenring/pointers.h src/extdlls/er_param/src/pointers.h
git mv src/eldenring/wstring.c src/extdlls/er_param/src/wstring.c
git mv src/eldenring/wstring.h src/extdlls/er_param/include/er_param/wstring.h
git mv src/eldenring/param_to_c.py src/extdlls/er_param/param_to_c.py
```

- [ ] **Step 2: 修正 `src/param_internal.h` 的 include**

当前 `src/eldenring/param_internal.h` 第 11 行 `#include "param.h"`。迁移后 `src/param_internal.h` 改为 include 公共头:

旧:
```c
#include "param.h"
```
新:
```c
#include <er_param/param.h>
```

- [ ] **Step 3: 修正 `src/param.c` 的 include**

当前 `src/eldenring/param.c` 第 9-12 行:
```c
#include "param_internal.h"

#include "pointers.h"
#include "wstring.h"
```
迁移后:
- `param_internal.h` 与 `pointers.h` 同在 `src/` 目录, 引号 include 仍有效(CMake 的 `src` include 目录覆盖)。
- `wstring.h` 移到了 `include/er_param/wstring.h`(不在 `src/`)。`param.c` 第 75 行用 `er_wstring_impl_str`、第 27 行用 `er_wstring_impl_t`, 需 include 公共头。

改 `src/param.c` 第 12 行:
旧:
```c
#include "wstring.h"
```
新:
```c
#include <er_param/wstring.h>
```
(`param_internal.h` 第 11 行、`pointers.h` 第 9 行的 include 保持不变, 见下方确认。)

确认 `pointers.h` 是否 include 了其它路径。读 `src/pointers.h`:
- 它 `#include "process/image.h"` / `#include "process/scanner.h"`(通过 include `src/` 根覆盖)。er_param 在 `src/extdlls/er_param/`, `src/` 根是其上两级 `../..`。

er_param 的 CMakeLists(Task 1 Step 2 写的)中 `target_include_directories(${PROJECT_NAME} PRIVATE src include)` **缺少** 指向仓库 `src/` 根的 include。需补。修正 `src/extdlls/er_param/CMakeLists.txt` 的该行:

旧(Task 1 Step 2 写的):
```cmake
target_include_directories(${PROJECT_NAME} PRIVATE src include)
```
新:
```cmake
target_include_directories(${PROJECT_NAME} PRIVATE src include ${CMAKE_SOURCE_DIR}/src)
```

- [ ] **Step 4: 修正 `src/pointers.c` 的 include**

当前 `src/eldenring/pointers.c` 第 9-11 行:
```c
#include "pointers.h"

#include "process/image.h"
#include "process/scanner.h"
```
`pointers.h` 同目录(已由 Step 3 的 `src` include 覆盖)。`process/image.h` / `process/scanner.h` 由 Step 3 新增的 `${CMAKE_SOURCE_DIR}/src` include 覆盖。**无需改动 pointers.c**。

但 pointers.c 调用 `get_module_image_base` / `sig_scan`, 这些在 `process` 静态库。er_param CMakeLists 需 link `process`。修正 `src/extdlls/er_param/CMakeLists.txt` 的 `target_link_libraries`:

旧(Task 1 Step 2 写的):
```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE klib inih shlwapi)
```
新:
```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE process klib inih shlwapi)
```

- [ ] **Step 5: 修正 `src/wstring.c` 的 include**

`src/eldenring/wstring.c` 第 9 行 `#include "wstring.h"`。迁移后 `wstring.h` 在 `include/er_param/wstring.h`, 而 `include/er_param` 已是 include 目录(CMakeLists 的 `include` 即 `src/extdlls/er_param/include`, 头位于 `include/er_param/wstring.h`, 引用时 `#include <er_param/wstring.h>`)。但 wstring.c 用引号 `"wstring.h"` 找同目录(`src/`)无此文件。

改 `src/wstring.c` 第 9 行:
旧:
```c
#include "wstring.h"
```
新:
```c
#include <er_param/wstring.h>
```

- [ ] **Step 6: 修正 `include/er_param/wstring.h` 的声明**

当前 `src/eldenring/wstring.h` 第 25-26 行声明 `er_wstring_impl_str` / `er_wstring_impl_str_mutable`。迁移后 `include/er_param/wstring.h` 保留两者声明(er_param 内部用 mutable, 消费者经 api 用 str)。**无需改动内容**(声明照旧)。确认 header guard 与结构体定义完整即可。

- [ ] **Step 7: 修正 codegen 脚本输出路径**

`param_to_c.py` 第 44 行 `all_headers = codecs.open('param_defs.h', 'w', 'utf-8')` 与第 115 行 `with codecs.open('defs/' + type_name + '.h', ...)`。脚本从其工作目录输出, AGENTS.md 说"reads from ER/Defs/ ... relative to the script's working directory"。迁移后脚本工作目录为 `src/extdlls/er_param/`, 输出应到 `include/er_param/`。

改 `param_to_c.py` 第 44 行:
旧:
```python
all_headers = codecs.open('param_defs.h', 'w', 'utf-8')
```
新:
```python
all_headers = codecs.open('include/er_param/param_defs.h', 'w', 'utf-8')
```

改第 115 行:
旧:
```python
    with codecs.open('defs/' + type_name + '.h', 'w', 'utf-8') as f:
```
新:
```python
    with codecs.open('include/er_param/defs/' + type_name + '.h', 'w', 'utf-8') as f:
```

改第 117 行(all_headers.write 引 defs 路径):
旧:
```python
    all_headers.write('#include "defs/' + type_name + '.h"\n')
```
新:
```python
    all_headers.write('#include "defs/' + type_name + '.h"\n')
```
(param_defs.h 内 include 仍写 `defs/...`, 因 param_defs.h 与 defs/ 同在 `include/er_param/`, 相对引用正确, **不改**。)

注: codegen 仅人工触发(需 ER/ XML), 此步仅改脚本路径常量, 不运行脚本(无 XML 输入)。

- [ ] **Step 8: 验证配置(暂不期望构建通过, 因 provider.c 未建)**

```bash
cmake -S . -B cmake-build-debug -G "Visual Studio 18 2026" -DBUILD_TESTING=ON
```
预期: 配置成功。`extdll_er_param` 目标创建(源文件 provider.c 尚不存在, 但 CMake 配置阶段不检查源文件存在性, 仅生成时检查)。

注: 此时 `src/eldenring/CMakeLists.txt` 仍存在并仍被 `src/CMakeLists.txt` 的 `add_subdirectory(eldenring)` 引用, 但其列出的源文件(param.c 等)已 git mv 走, **配置会失败**(找不到 param.c)。因此本任务必须先在 Task 3 解除主 loader 对 eldenring 的引用, 才能验证。故本任务不在此验证, 留到 Task 4 末尾统一验证。

- [ ] **Step 9: Commit**

```bash
git add -A
git commit -m "feat(er_param): migrate param/pointers/wstring files from eldenring"
```

---

## Task 3: 解除主 loader 对 eldenring 的构建引用

**Files:**
- Modify: `src/CMakeLists.txt:7` (移除 `add_subdirectory(eldenring)`)
- Modify: `src/modloader/CMakeLists.txt:43` (去 `eldenring` 链接)
- Delete: `src/eldenring/CMakeLists.txt`

**说明:** 先断开主构建对 `src/eldenring/` 的引用, 使配置不再因 eldenring 缺源文件而失败。此时主 loader 代码仍 `#include "eldenring/..."`(Task 5 才改), 但因不再链接 eldenring, 编译会在 Task 5 才真正修复。本任务仅处理 CMake 层。

- [ ] **Step 1: 移除 `src/CMakeLists.txt` 的 eldenring 子目录**

旧(`src/CMakeLists.txt:7`):
```cmake
add_subdirectory(process)
add_subdirectory(steam)
add_subdirectory(eldenring)
add_subdirectory(modloader)
add_subdirectory(launcher)
add_subdirectory(extdlls)
```
新:
```cmake
add_subdirectory(process)
add_subdirectory(steam)
add_subdirectory(modloader)
add_subdirectory(launcher)
add_subdirectory(extdlls)
```

- [ ] **Step 2: 移除 modloader 对 eldenring 的链接**

旧(`src/modloader/CMakeLists.txt:43`):
```cmake
target_link_libraries(modloader_dll process steam eldenring minhook inih klib shlwapi version)
```
新:
```cmake
target_link_libraries(modloader_dll process steam minhook inih klib shlwapi version)
```

- [ ] **Step 3: 删除 `src/eldenring/CMakeLists.txt`**

```bash
git rm src/eldenring/CMakeLists.txt
```
(`src/eldenring/` 此时只剩空目录(文件已 git mv 走), 删其 CMakeLists 后目录空。git 不跟踪空目录, 自然消失。)

- [ ] **Step 4: 验证配置通过**

```bash
cmake -S . -B cmake-build-debug -G "Visual Studio 18 2026" -DBUILD_TESTING=ON
```
预期: 配置成功, 无 eldenring 子目录, 无 modloader 链接 eldenring。`extdll_er_param` 目标存在但 provider.c 缺失(生成阶段才暴露)。

- [ ] **Step 5: Commit**

```bash
git add -A
git commit -m "build: remove eldenring static lib from main loader build"
```

---

## Task 4: 扩展 extdlls 顶层 CMakeLists 的子目录分支

**Files:**
- Modify: `src/extdlls/CMakeLists.txt`

**说明:** 让 er_param 由 glob 发现但其有 CMakeLists.txt 时走 `add_subdirectory`, 其它 extdll 走原 `add_project`。所有 extdll link `er_param::headers`。此任务后 er_param 仍因缺 provider.c 不能构建, 但配置/拓扑成立。

- [ ] **Step 1: 改写 `src/extdlls/CMakeLists.txt`**

完整新内容:

```cmake
enable_language(ASM_NASM)

file(GLOB dirs LIST_DIRECTORIES true ./*)
foreach (dir ${dirs})
    if (NOT IS_DIRECTORY ${dir})
        continue()
    endif ()
    file(GLOB files ${dir}/*)
    if (NOT files)
        continue()
    endif ()
    get_filename_component(dir ${dir} NAME)
    if (EXISTS "${dir}/CMakeLists.txt")
        # 子目录自包含构建 (er_param: 定义 INTERFACE headers 目标)
        add_subdirectory(${dir})
    else ()
        add_project(extdll_${dir} SHARED ${files} LANGUAGES C FOLDER extdlls OUTPUT_SUBDIR dll NO_PREFIX OUTPUT_NAME ${dir})
        target_include_directories(extdll_${dir} PRIVATE ..)
        target_link_libraries(extdll_${dir} PRIVATE inih klib shlwapi)
    endif ()
    # 对所有 extdll 统一提供 er_param 头 (CMake 允许引用稍后创建的目标)
    if (TARGET extdll_${dir})
        target_link_libraries(extdll_${dir} PRIVATE er_param::headers)
    endif ()
endforeach ()
```

- [ ] **Step 2: 验证配置通过**

```bash
cmake -S . -B cmake-build-debug -G "Visual Studio 18 2026" -DBUILD_TESTING=ON
```
预期: 成功。`extdll_er_param` 经 `add_subdirectory(er_param)` 创建, `er_param::headers` INTERFACE 目标存在, itemlot_rate/autoloot/no_dup_loot 经 `add_project` 创建并 link `er_param::headers`。

- [ ] **Step 3: Commit**

```bash
git add src/extdlls/CMakeLists.txt
git commit -m "build(extdlls): add subdirectory branch for er_param and link er_param::headers"
```

---

## Task 5: 更新主 loader 接口头 (extdll_api.h V1)

**Files:**
- Modify: `src/modloader/extdll_api.h`

- [ ] **Step 1: 改 `src/modloader/extdll_api.h` 为 V1**

完整新内容(替换第 26-43 行区域, 即 `typedef struct er_param_table_s...` 到 `modloader_ext_init_t`):

旧(第 26-41 行):
```c
typedef struct er_param_table_s er_param_table_t;
typedef struct er_wstring_impl_s er_wstring_impl_t;

typedef struct modloader_ext_api_s {
    /* Common API */
    void *(*get_module_image_base)(const wchar_t *module_name, size_t *size);
    uint8_t *(*sig_scan)(void *base, size_t size, const char *pattern);

    /* ELDEN RING API */
    const er_param_table_t *(*er_param_find_table)(const wchar_t *name);
    const wchar_t *(*er_wstring_impl_str)(const er_wstring_impl_t *str);

    /* V2 Added API */
    void (*hook)(void *target, void *detour, void **original);
    void (*unhook)(void *hook);
} modloader_ext_api_t;
```
新:
```c
typedef struct modloader_ext_api_s {
    /* Common API */
    void *(*get_module_image_base)(const wchar_t *module_name, size_t *size);
    uint8_t *(*sig_scan)(void *base, size_t size, const char *pattern);

    /* Hook API */
    void (*hook)(void *target, void *detour, void **original);
    void (*unhook)(void *hook);
} modloader_ext_api_t;
```

`modloader_ext_def_t`(第 17-24 行)改为:
旧:
```c
typedef struct modloader_ext_def_s {
    const char *name;

    void *userp;

    void (*on_uninit)(void*);
    void (*on_param_initialized)(void*);
} modloader_ext_def_t;
```
新:
```c
typedef struct modloader_ext_def_s {
    const char *name;

    void *userp;

    void (*on_uninit)(void*);
} modloader_ext_def_t;
```

(第 43 行 `modloader_ext_init_t` 声明保持不变。)

- [ ] **Step 2: Commit**

```bash
git add src/modloader/extdll_api.h
git commit -m "feat(modloader): bump ext api to V1, remove param fields"
```

---

## Task 6: 改主 loader extdll.c / extdll.h (移除 param 通知路径)

**Files:**
- Modify: `src/modloader/extdll.c`
- Modify: `src/modloader/extdll.h`

- [ ] **Step 1: 改 `src/modloader/extdll.h` 移除声明**

旧(第 21 行):
```c
extern void extdlls_on_param_initialized();
```
删除该行。结果第 17-22 行:
```c
extern void extdlls_add(const char *name, const wchar_t *path);
extern int extdlls_count();
extern void extdlls_load_all();
extern void extdlls_unload_all();

#ifdef __cplusplus
```

- [ ] **Step 2: 改 `src/modloader/extdll.c` — 移除 include 与 ext_api param 字段**

旧(第 14-15 行):
```c
#include "eldenring/param_internal.h"
#include "eldenring/wstring.h"
```
删除这两行。

旧(第 53-62 行 `ext_api`):
```c
static modloader_ext_api_t ext_api = {
    .get_module_image_base = get_module_image_base,
    .sig_scan = sig_scan,
    .er_param_find_table = er_param_find_table,
    .er_wstring_impl_str = er_wstring_impl_str,

    /* V2 Added API */
    .hook = hook,
    .unhook = unhook,
};
```
新:
```c
static modloader_ext_api_t ext_api = {
    .get_module_image_base = get_module_image_base,
    .sig_scan = sig_scan,

    .hook = hook,
    .unhook = unhook,
};
```

- [ ] **Step 3: 改 `extdll_t` 移除 `on_param_initialized` 字段**

旧(第 27-36 行):
```c
typedef struct extdll_t {
    char *name;
    wchar_t *base_path;
    HMODULE dll_module;
    void *extension_object;

    void *userp;
    void (*on_uninit)(void*);
    void (*on_param_initialized)(void*);
} extdll_t;
```
新:
```c
typedef struct extdll_t {
    char *name;
    wchar_t *base_path;
    HMODULE dll_module;
    void *extension_object;

    void *userp;
    void (*on_uninit)(void*);
} extdll_t;
```

- [ ] **Step 4: 改 `extdlls_load_all` 移除 on_param_initialized 赋值**

旧(第 106-114 行):
```c
        modloader_ext_init_t ml_ext_init = (modloader_ext_init_t)GetProcAddress(dll, "modloader_ext_init");
        if (ml_ext_init) {
            modloader_ext_def_t *def = ml_ext_init(&ext_api);
            if (def) {
                extdll->userp = def->userp;
                extdll->on_uninit = def->on_uninit;
                extdll->on_param_initialized = def->on_param_initialized;
                fwprintf(stdout, L"Initialized external dll %hs (using extdll API)\n", extdll->name);
            }
            continue;
        }
```
新:
```c
        modloader_ext_init_t ml_ext_init = (modloader_ext_init_t)GetProcAddress(dll, "modloader_ext_init");
        if (ml_ext_init) {
            modloader_ext_def_t *def = ml_ext_init(&ext_api);
            if (def) {
                extdll->userp = def->userp;
                extdll->on_uninit = def->on_uninit;
                fwprintf(stdout, L"Initialized external dll %hs (using extdll API)\n", extdll->name);
            }
            continue;
        }
```

- [ ] **Step 5: 改 `extdlls_unload_all` 移除 on_param_initialized 清空**

旧(第 159-161 行):
```c
        extdll->userp = NULL;
        extdll->on_uninit = NULL;
        extdll->on_param_initialized = NULL;
```
新:
```c
        extdll->userp = NULL;
        extdll->on_uninit = NULL;
```

- [ ] **Step 6: 删除 `extdlls_on_param_initialized` 函数**

旧(第 165-173 行整段):
```c
void extdlls_on_param_initialized() {
    for (int i = 0; i < extdll_count; i++) {
        extdll_t *extdll = &extdlls[i];
        if (!extdll->dll_module) continue;
        if (extdll->on_param_initialized) {
            extdll->on_param_initialized(extdll->userp);
        }
    }
}
```
删除整段。

- [ ] **Step 7: 验证构建(主 loader 部分)**

此时主 loader 仍含 `patches/eldenring.c` 的 eldenring include(下个任务改), 故**整体构建仍失败**。此任务不单独验证, 留到 Task 8(主 loader 全改完)统一验证。

- [ ] **Step 8: Commit**

```bash
git add src/modloader/extdll.c src/modloader/extdll.h
git commit -m "refactor(modloader): remove param notification path from extdll"
```

---

## Task 7: 改主 loader config (移除 world_map_cursor_speed)

**Files:**
- Modify: `src/modloader/config.h`
- Modify: `src/modloader/config.c`

- [ ] **Step 1: 移除 `config.h` 的字段**

旧(`src/modloader/config.h:28`):
```c
    float world_map_cursor_speed;
    bool disable_mouse_camera_control;
```
新:
```c
    bool disable_mouse_camera_control;
```

- [ ] **Step 2: 移除 `config.c` 的初始化默认值**

旧(`src/modloader/config.c:21-32`):
```c
config_t config = {
    0,
    false,
    false,
    true,
    false,
    false,
    1.0f,
    false,
    L"",
    L"",
};
```
字段顺序对应: cpu_affinity_strategy(0), reset_achievements_on_new_game(false), enable_ime(false), skip_intro(true), remove_chromatic_aberration(false), remove_vignette(false), world_map_cursor_speed(1.0f), disable_mouse_camera_control(false), replaced_save_filename(L""), replaced_seamless_coop_save_filename(L"")。

移除 world_map_cursor_speed 后新:
```c
config_t config = {
    0,
    false,
    false,
    true,
    false,
    false,
    false,
    L"",
    L"",
};
```

- [ ] **Step 3: 移除 `config.c` 的 ini 解析分支**

旧(`src/modloader/config.c:71-80`):
```c
        } else if (lstrcmpA(name, "world_map_cursor_speed") == 0) {
            config.world_map_cursor_speed = strtof(value, NULL);
            if (config.world_map_cursor_speed <= 0.0f) {
                config.world_map_cursor_speed = 1.0f;
            } else if (config.world_map_cursor_speed < 0.5f) {
                config.world_map_cursor_speed = 0.5f;
            } else if (config.world_map_cursor_speed > 10.0f) {
                config.world_map_cursor_speed = 10.0f;
            }
        } else if (lstrcmpA(name, "disable_mouse_camera_control") == 0) {
```
新:
```c
        } else if (lstrcmpA(name, "disable_mouse_camera_control") == 0) {
```

- [ ] **Step 4: Commit**

```bash
git add src/modloader/config.h src/modloader/config.c
git commit -m "refactor(modloader): remove world_map_cursor_speed config (moved to er_param)"
```

---

## Task 8: 改主 loader patches/eldenring.c (内联 wstring + 移除 param 调用)

**Files:**
- Modify: `src/modloader/patches/eldenring.c`

**说明:** 这是主 loader 最复杂的改动。移除 param 调用、内联 wstring SSO、移除 eldenring include。改完后主 loader 应能独立构建(不依赖 eldenring 静态库与 er_param)。

- [ ] **Step 1: 替换 include 区**

旧(第 21-24 行):
```c
#include "eldenring/wstring.h"
#include "eldenring/param_internal.h"
#include "eldenring/pointers.h"
#include "eldenring/defs/menu_common_param.h"
```
删除这四行。保留第 12 行 `#include "modloader/extdll.h"`(主 loader 内部头)。

同时第 13 行 `#include "modloader/extdll.h"` 现在仍需(extdlls_load_all 等), 保留。

- [ ] **Step 2: 内联 wstring SSO 本地结构体与函数**

在文件顶部(static 变量区, 第 34 行 `static HANDLE async_operations_thread_handle = NULL;` 之前)插入:

```c
typedef struct er_wstring_local_s {
    void *unk;
    wchar_t *string;
    void *unk2;
    uint64_t length;
    uint64_t capacity;
} er_wstring_local_t;

static wchar_t *wstring_str_mutable(er_wstring_local_t *str) {
    return (sizeof(wchar_t) * str->capacity >= 16) ? str->string : (wchar_t*)&str->string;
}
```

- [ ] **Step 3: 改 `async_operation_thread` 移除 param 逻辑**

旧(第 81-94 行):
```c
DWORD WINAPI async_operation_thread(LPVOID arg) {
    er_pointers_init(INIT_CS_REGULATION_MANAGER);
    er_param_load_table();
    extdlls_on_param_initialized();

    if (config.cpu_affinity_strategy != 0) set_process_cpu_affinity_strategy(config.cpu_affinity_strategy);
    if (config.world_map_cursor_speed != 1.0f) {
        const er_param_table_t *t = er_param_find_table(L"MenuCommonParam");
        er_param_table_iterate_begin(t, er_menu_common_param_t, param)
            param->worldMapCursorSpeed *= config.world_map_cursor_speed;
        er_param_table_iterate_end();
    }
    return 0;
}
```
新:
```c
DWORD WINAPI async_operation_thread(LPVOID arg) {
    if (config.cpu_affinity_strategy != 0) set_process_cpu_affinity_strategy(config.cpu_affinity_strategy);
    return 0;
}
```

- [ ] **Step 4: 改 `map_archive_path` 用本地 wstring 类型**

旧(第 96 行 typedef):
```c
typedef void *(__cdecl *map_archive_path_t)(er_wstring_impl_t *path, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6);
```
新:
```c
typedef void *(__cdecl *map_archive_path_t)(er_wstring_local_t *path, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6);
```

旧(第 110 行函数签名):
```c
void *__cdecl map_archive_path(er_wstring_impl_t *path, const uint64_t p2, const uint64_t p3, const uint64_t p4, const uint64_t p5, const uint64_t p6) {
    void *res = old_map_archive_path(path, p2, p3, p4, p5, p6);
    if (path == NULL) return res;
    wchar_t *str = er_wstring_impl_str_mutable(path);
```
新:
```c
void *__cdecl map_archive_path(er_wstring_local_t *path, const uint64_t p2, const uint64_t p3, const uint64_t p4, const uint64_t p5, const uint64_t p6) {
    void *res = old_map_archive_path(path, p2, p3, p4, p5, p6);
    if (path == NULL) return res;
    wchar_t *str = wstring_str_mutable(path);
```

- [ ] **Step 5: 改 `eldenring_uninstall` 移除 er_param_unload**

旧(第 377-386 行):
```c
void eldenring_uninstall() {
    game_running = false;

    /* NOTE: TerminateThread is unsafe (leaks stack, CRT state, held locks).
       We use a longer timeout and accept the thread may still be running on process exit. */
    if (async_operations_thread_handle && WaitForSingleObject(async_operations_thread_handle, 5000) == WAIT_TIMEOUT)
        TerminateThread(async_operations_thread_handle, 0);
    if (reset_achievements_on_new_game_thread_handle && WaitForSingleObject(reset_achievements_on_new_game_thread_handle, 5000) == WAIT_TIMEOUT)
        TerminateThread(reset_achievements_on_new_game_thread_handle, 0);
    er_param_unload();
}
```
新:
```c
void eldenring_uninstall() {
    game_running = false;

    /* NOTE: TerminateThread is unsafe (leaks stack, CRT state, held locks).
       We use a longer timeout and accept the thread may still be running on process exit. */
    if (async_operations_thread_handle && WaitForSingleObject(async_operations_thread_handle, 5000) == WAIT_TIMEOUT)
        TerminateThread(async_operations_thread_handle, 0);
    if (reset_achievements_on_new_game_thread_handle && WaitForSingleObject(reset_achievements_on_new_game_thread_handle, 5000) == WAIT_TIMEOUT)
        TerminateThread(reset_achievements_on_new_game_thread_handle, 0);
}
```

- [ ] **Step 6: 验证主 loader 构建**

```bash
cmake --build cmake-build-debug --config Debug --target modloader_dll
```
预期: modloader_dll 构建成功(已无 eldenring 依赖, 内联 wstring, 无 param 调用)。若失败, 检查是否遗漏 `er_pointers`/`er_param`/`extdlls_on_param_initialized` 的引用。

- [ ] **Step 7: Commit**

```bash
git add src/modloader/patches/eldenring.c
git commit -m "refactor(modloader): inline wstring SSO, remove param calls from eldenring patches"
```

---

## Task 9: 实现 er_param provider.c (核心: modloader_ext_init + api + 观察者 + cursor_speed)

**Files:**
- Create: `src/extdlls/er_param/src/provider.c`
- Create: `src/extdlls/er_param/er_param.ini`

**说明:** 这是新组件的核心。实现 ext init(启动加载线程)、er_param_api_get(返回 api 结构)、观察者机制(CRITICAL_SECTION)、cursor_speed 内置、on_uninit。完成后 er_param.dll 可构建。

- [ ] **Step 1: 创建 `er_param.ini`**

```ini
; World map cursor movement speed multiplier
;  1 = default
world_map_cursor_speed=1.0
```

- [ ] **Step 2: 创建 `src/provider.c`**

完整内容:

```c
/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include <modloader/extdll_api.h>
#include <er_param/er_param_api.h>
#include <er_param/param.h>
#include <er_param/wstring.h>
#include "param_internal.h"
#include "pointers.h"

#include <ini.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct observer_s {
    void (*cb)(void *userp);
    void *userp;
} observer_t;

static modloader_ext_api_t *the_api = NULL;

static CRITICAL_SECTION observers_lock;
static bool observers_inited = false;
static observer_t *observers = NULL;
static int observers_count = 0;
static int observers_capacity = 0;
static bool param_loaded = false;
static float config_world_map_cursor_speed = 1.0f;
static HANDLE param_thread_handle = NULL;

static const er_param_table_t *provider_find_table(const wchar_t *name) {
    return er_param_find_table(name);
}

static const wchar_t *provider_wstring_str(const er_wstring_impl_t *str) {
    return er_wstring_impl_str(str);
}

static bool provider_is_loaded(void) {
    return param_loaded;
}

static bool provider_on_param_loaded(void (*cb)(void *userp), void *userp) {
    if (cb == NULL) return false;
    EnterCriticalSection(&observers_lock);
    if (param_loaded) {
        LeaveCriticalSection(&observers_lock);
        cb(userp);
        return true;
    }
    if (observers_count >= observers_capacity) {
        observers_capacity = observers_capacity == 0 ? 8 : observers_capacity * 2;
        observer_t *new_obs = observers == NULL
            ? LocalAlloc(LMEM_ZEROINIT, observers_capacity * sizeof(observer_t))
            : LocalReAlloc(observers, observers_capacity * sizeof(observer_t), LMEM_ZEROINIT);
        if (new_obs == NULL) {
            LeaveCriticalSection(&observers_lock);
            return false;
        }
        observers = new_obs;
    }
    observers[observers_count].cb = cb;
    observers[observers_count].userp = userp;
    observers_count++;
    LeaveCriticalSection(&observers_lock);
    return true;
}

static void provider_off_param_loaded(void (*cb)(void *userp), void *userp) {
    if (cb == NULL) return;
    EnterCriticalSection(&observers_lock);
    for (int i = 0; i < observers_count; i++) {
        if (observers[i].cb == cb && observers[i].userp == userp) {
            observers[i] = observers[observers_count - 1];
            observers_count--;
            break;
        }
    }
    LeaveCriticalSection(&observers_lock);
}

static const er_param_api_t g_api = {
    .api_version = 1,
    .find_table = provider_find_table,
    .wstring_str = provider_wstring_str,
    .is_loaded = provider_is_loaded,
    .on_param_loaded = provider_on_param_loaded,
    .off_param_loaded = provider_off_param_loaded,
};

__declspec(dllexport)
const er_param_api_t *er_param_api_get(void) {
    return &g_api;
}

static void apply_cursor_speed(void) {
    if (config_world_map_cursor_speed == 1.0f) return;
    const er_param_table_t *t = er_param_find_table(L"MenuCommonParam");
    if (t == NULL) return;
    er_param_table_iterate_begin(t, er_menu_common_param_t, param)
        param->worldMapCursorSpeed *= config_world_map_cursor_speed;
    er_param_table_iterate_end();
}

static int ini_handler(void *user, const char *section, const char *name, const char *value) {
    (void)user;
    if (section == NULL || section[0] == 0) {
        if (lstrcmpA(name, "world_map_cursor_speed") == 0) {
            config_world_map_cursor_speed = strtof(value, NULL);
            if (config_world_map_cursor_speed <= 0.0f) {
                config_world_map_cursor_speed = 1.0f;
            } else if (config_world_map_cursor_speed < 0.5f) {
                config_world_map_cursor_speed = 0.5f;
            } else if (config_world_map_cursor_speed > 10.0f) {
                config_world_map_cursor_speed = 10.0f;
            }
        }
    }
    return 1;
}

static void load_config(HMODULE module) {
    wchar_t ini_path[512];
    GetModuleFileNameW(module, ini_path, sizeof(ini_path) / sizeof(ini_path[0]));
    PathRemoveFileSpecW(ini_path);
    PathAppendW(ini_path, L"er_param.ini");
    FILE *file = _wfopen(ini_path, L"r");
    if (file == NULL) return;
    ini_parse_file(file, ini_handler, NULL);
    fclose(file);
}

DWORD WINAPI param_thread(LPVOID arg) {
    (void)arg;
    size_t size;
    void *base = the_api->get_module_image_base(NULL, &size);
    (void)base;
    er_pointers_init(INIT_CS_REGULATION_MANAGER);
    if (!er_param_load_table()) {
        return 1;
    }
    observer_t *snapshot = NULL;
    int snap_count = 0;
    EnterCriticalSection(&observers_lock);
    param_loaded = true;
    snap_count = observers_count;
    if (snap_count > 0) {
        snapshot = LocalAlloc(0, snap_count * sizeof(observer_t));
        if (snapshot) {
            memcpy(snapshot, observers, snap_count * sizeof(observer_t));
        }
    }
    observers_count = 0;
    LeaveCriticalSection(&observers_lock);

    apply_cursor_speed();

    if (snapshot) {
        for (int i = 0; i < snap_count; i++) {
            snapshot[i].cb(snapshot[i].userp);
        }
        LocalFree(snapshot);
    }
    return 0;
}

static HMODULE g_module = NULL;

modloader_ext_def_t def = {
    "er_param",
    NULL,
    NULL,
};

void on_uninit(void *userp) {
    (void)userp;
    if (param_thread_handle && WaitForSingleObject(param_thread_handle, 5000) == WAIT_TIMEOUT)
        TerminateThread(param_thread_handle, 0);
    if (param_thread_handle) {
        CloseHandle(param_thread_handle);
        param_thread_handle = NULL;
    }
    er_param_unload();
    if (observers) {
        LocalFree(observers);
        observers = NULL;
        observers_count = 0;
        observers_capacity = 0;
    }
    DeleteCriticalSection(&observers_lock);
    observers_inited = false;
}

__declspec(dllexport)
modloader_ext_def_t *modloader_ext_init(modloader_ext_api_t *api) {
    the_api = api;
    if (!observers_inited) {
        InitializeCriticalSection(&observers_lock);
        observers_inited = true;
    }
    load_config(g_module);
    def.on_uninit = on_uninit;
    param_thread_handle = CreateThread(NULL, 0, param_thread, NULL, 0, NULL);
    return &def;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved) {
    (void)reserved;
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            g_module = module;
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
```

**注意点:**
- `param_thread` 里 `the_api->get_module_image_base(NULL, &size)` 拿 base/size 供 `er_pointers_init` 内部用。但 `er_pointers_init`(pointers.c) 自己调 `get_module_image_base(NULL, &image_size)`——它直接用 `process/image.h` 的实现, **不经 the_api**。所以 param_thread 里那两行 `base = ...` 实际多余, 可删。但 pointers.c 的 `get_module_image_base` 来自 link 的 `process` 静态库。确认 `pointers.c` 第 38 行 `void *image_base = get_module_image_base(NULL, &image_size);` 仍可用(因 er_param link process, Task 2 Step 4 已加)。故 param_thread 不需调 the_api 取 base。简化:

将 param_thread 开头的:
```c
    size_t size;
    void *base = the_api->get_module_image_base(NULL, &size);
    (void)base;
    er_pointers_init(INIT_CS_REGULATION_MANAGER);
```
改为:
```c
    er_pointers_init(INIT_CS_REGULATION_MANAGER);
```
(删除多余 base 取值; pointers.c 自带 get_module_image_base via process 库。)

- [ ] **Step 3: 确认 `er_menu_common_param_t` 可见**

`apply_cursor_speed` 用 `er_menu_common_param_t`。该类型在 `include/er_param/defs/menu_common_param.h`。provider.c 已 `#include <er_param/param.h>`(iterate 宏), 但 **未 include defs/menu_common_param.h**。需补 include。

在 provider.c 的 include 区(`#include <er_param/wstring.h>` 之后)加:
```c
#include <er_param/defs/menu_common_param.h>
```

- [ ] **Step 4: 验证 er_param 构建**

```bash
cmake --build cmake-build-debug --config Debug --target extdll_er_param
```
预期: `extdll_er_param` 构建成功, 产出 `er_param.dll`。若报找不到 `process`/`inih`/`klib` 目标, 检查 er_param CMakeLists 的 link(Task 2 Step 4: `process klib inih shlwapi`)。

- [ ] **Step 5: 验证全量构建 + 测试**

```bash
cmake --build cmake-build-debug --config Debug
ctest --test-dir cmake-build-debug -C Debug --output-on-failure
```
预期: 全部目标构建成功(modloader_dll, extdll_*, er_param, launcher, tests)。ctest 3 个 smoke 测试通过(smoke_param/smoke_filecache/smoke_no_dup_loot)。注: itemlot_rate/autoloot 此刻仍用旧接口(`the_api->er_param_find_table`/`on_param_initialized` 字段), 会编译失败(因 ext_api 已无该字段, def 已无 on_param_initialized)。**这些会在 Task 10/11 修复**。因此全量构建此刻仍失败于 extdll_itemlot_rate/extdll_autoloot。

修订: 此 Step 只验证 `modloader_dll` + `extdll_er_param` + tests, 不全量:
```bash
cmake --build cmake-build-debug --config Debug --target modloader_dll extdll_er_param
ctest --test-dir cmake-build-debug -C Debug --output-on-failure
```
预期: modloader_dll + er_param 构建成功; ctest 通过。

- [ ] **Step 6: Commit**

```bash
git add src/extdlls/er_param/src/provider.c src/extdlls/er_param/er_param.ini
git commit -m "feat(er_param): implement provider with observer mechanism and cursor_speed"
```

---

## Task 10: 迁移 itemlot_rate 到 er_param api

**Files:**
- Modify: `src/extdlls/itemlot_rate/main.c`

**说明:** itemlot_rate 是主要 param 消费者。改 include 路径, 用 `er_param_api_get` 拿 api, 注册 `on_param_loaded`, on_uninit 注销, def 去掉 on_param_initialized。

- [ ] **Step 1: 改 include**

旧(第 9-11 行):
```c
#include <modloader/extdll_api.h>
#include <eldenring/param.h>
#include <eldenring/defs/itemlot_param.h>
```
新:
```c
#include <modloader/extdll_api.h>
#include <er_param/param.h>
#include <er_param/defs/itemlot_param.h>
#include <er_param/er_param_api.h>
```

- [ ] **Step 2: 改 `the_api` 旁加 `param_api`**

旧(第 21 行):
```c
static modloader_ext_api_t* the_api;
```
新:
```c
static modloader_ext_api_t* the_api;
static const er_param_api_t* param_api = NULL;
```

- [ ] **Step 3: 改 `on_param_initialized` 为 `on_param_loaded` 并用 param_api**

旧(第 202-217 行):
```c
void on_param_initialized(void* userp) {
    (void)userp;
    const er_param_table_t* table = the_api->er_param_find_table(L"ItemLotParam_map");
    if (table != NULL) {
        er_param_table_iterate_begin(table, er_itemlot_param_t, param) {
            process_param_count(param, 1);
        } er_param_table_iterate_end();
    }
    table = the_api->er_param_find_table(L"ItemLotParam_enemy");
    if (table != NULL) {
        er_param_table_iterate_begin(table, er_itemlot_param_t, param) {
            process_param_rate(param);
            process_param_count(param, 2);
        } er_param_table_iterate_end();
    }
}
```
新:
```c
void on_param_loaded(void* userp) {
    (void)userp;
    if (param_api == NULL) return;
    const er_param_table_t* table = param_api->find_table(L"ItemLotParam_map");
    if (table != NULL) {
        er_param_table_iterate_begin(table, er_itemlot_param_t, param) {
            process_param_count(param, 1);
        } er_param_table_iterate_end();
    }
    table = param_api->find_table(L"ItemLotParam_enemy");
    if (table != NULL) {
        er_param_table_iterate_begin(table, er_itemlot_param_t, param) {
            process_param_rate(param);
            process_param_count(param, 2);
        } er_param_table_iterate_end();
    }
}
```

- [ ] **Step 4: 改 def 与 modloader_ext_init**

旧(第 219-230 行):
```c
modloader_ext_def_t def = {
    "item_lot_rate",
    NULL,
    NULL,
    on_param_initialized
};

__declspec(dllexport)
modloader_ext_def_t* modloader_ext_init(modloader_ext_api_t* api) {
    the_api = api;
    return &def;
}
```
新:
```c
modloader_ext_def_t def = {
    "item_lot_rate",
    NULL,
    NULL,
};

__declspec(dllexport)
modloader_ext_def_t* modloader_ext_init(modloader_ext_api_t* api) {
    the_api = api;
    HMODULE er_param_mod = GetModuleHandleW(L"er_param.dll");
    if (er_param_mod != NULL) {
        er_param_api_get_t get_api = (er_param_api_get_t)GetProcAddress(er_param_mod, "er_param_api_get");
        if (get_api != NULL) {
            param_api = get_api();
        }
    }
    if (param_api != NULL) {
        param_api->on_param_loaded(on_param_loaded, NULL);
    }
    return &def;
}
```

- [ ] **Step 5: 改 DllMain DLL_PROCESS_DETACH 注销回调**

旧(第 232-245 行):
```c
BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            load_config(module);
            break;
        case DLL_PROCESS_DETACH:
            if (config.include_goods != NULL) {
                LocalFree(config.include_goods);
                config.include_goods = NULL;
            }
            break;
    }
    return TRUE;
}
```
新:
```c
BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            load_config(module);
            break;
        case DLL_PROCESS_DETACH:
            if (param_api != NULL) {
                param_api->off_param_loaded(on_param_loaded, NULL);
            }
            if (config.include_goods != NULL) {
                LocalFree(config.include_goods);
                config.include_goods = NULL;
            }
            break;
    }
    return TRUE;
}
```

- [ ] **Step 6: 验证 itemlot_rate 构建**

```bash
cmake --build cmake-build-debug --config Debug --target extdll_itemlot_rate
```
预期: 构建成功。若报 `er_param_api_t`/`er_param_api_get_t` 未定义, 检查 include(Task 10 Step 1)与 er_param::headers link(Task 4)。

- [ ] **Step 7: Commit**

```bash
git add src/extdlls/itemlot_rate/main.c
git commit -m "refactor(itemlot_rate): consume er_param api instead of main loader param path"
```

---

## Task 11: 迁移 autoloot 到 er_param api

**Files:**
- Modify: `src/extdlls/autoloot/main.c`

**说明:** autoloot 用 `on_param_initialized` 做 sig_scan+hook(不访问 param 表)。改为经 er_param api 的 `on_param_loaded` 注册同样逻辑。def 去掉 on_param_initialized 字段。

- [ ] **Step 1: 改 include**

旧(第 1 行):
```c
#include <modloader/extdll_api.h>
```
新:
```c
#include <modloader/extdll_api.h>
#include <er_param/er_param_api.h>
```

- [ ] **Step 2: 加 param_api 静态变量**

旧(第 6 行):
```c
static modloader_ext_api_t* the_api;
```
新:
```c
static modloader_ext_api_t* the_api;
static const er_param_api_t* param_api = NULL;
```

- [ ] **Step 3: 改 on_param_initialized → on_param_loaded**

旧(第 20 行函数名):
```c
void on_param_initialized(void* userp) {
```
新:
```c
void on_param_loaded(void* userp) {
```
函数体不变(仍用 `the_api->sig_scan`/`the_api->hook`)。

- [ ] **Step 4: 改 def 与 modloader_ext_init**

旧(第 33-44 行):
```c
modloader_ext_def_t def = {
    "autoloot",
    NULL,
    on_uninit,
    on_param_initialized,
};

__declspec(dllexport)
modloader_ext_def_t* modloader_ext_init(modloader_ext_api_t* api) {
    the_api = api;
    return &def;
}
```
新:
```c
modloader_ext_def_t def = {
    "autoloot",
    NULL,
    on_uninit,
};

__declspec(dllexport)
modloader_ext_def_t* modloader_ext_init(modloader_ext_api_t* api) {
    the_api = api;
    HMODULE er_param_mod = GetModuleHandleW(L"er_param.dll");
    if (er_param_mod != NULL) {
        er_param_api_get_t get_api = (er_param_api_get_t)GetProcAddress(er_param_mod, "er_param_api_get");
        if (get_api != NULL) {
            param_api = get_api();
        }
    }
    if (param_api != NULL) {
        param_api->on_param_loaded(on_param_loaded, NULL);
    }
    return &def;
}
```

- [ ] **Step 5: 改 on_uninit 注销回调**

旧(第 13-16 行):
```c
void on_uninit(void* userp) {
    (void)userp;
    the_api->unhook(exec_action_button_param_proxy);
}
```
新:
```c
void on_uninit(void* userp) {
    (void)userp;
    if (param_api != NULL) {
        param_api->off_param_loaded(on_param_loaded, NULL);
    }
    the_api->unhook(exec_action_button_param_proxy);
}
```

- [ ] **Step 6: 验证 autoloot 构建**

```bash
cmake --build cmake-build-debug --config Debug --target extdll_autoloot
```
预期: 构建成功。

- [ ] **Step 7: Commit**

```bash
git add src/extdlls/autoloot/main.c
git commit -m "refactor(autoloot): register via er_param on_param_loaded"
```

---

## Task 12: 修正 no_dup_loot def 结构体

**Files:**
- Modify: `src/extdlls/no_dup_loot/main.c`

**说明:** no_dup_loot 不用 param, 仅需去掉 def 里已移除的 `on_param_initialized`(NULL)字段以匹配新 `modloader_ext_def_t`。

- [ ] **Step 1: 改 def**

旧(第 229-234 行):
```c
modloader_ext_def_t def = {
    "no_dup_loot",
    NULL,
    on_uninit,
    NULL
};
```
新:
```c
modloader_ext_def_t def = {
    "no_dup_loot",
    NULL,
    on_uninit,
};
```

- [ ] **Step 2: 验证构建 + 全量**

```bash
cmake --build cmake-build-debug --config Debug
ctest --test-dir cmake-build-debug -C Debug --output-on-failure
```
预期: 全量构建成功(所有目标), ctest 3 个 smoke 通过。这是首次全量绿。

- [ ] **Step 3: Commit**

```bash
git add src/extdlls/no_dup_loot/main.c
git commit -m "refactor(no_dup_loot): drop removed on_param_initialized field"
```

---

## Task 13: 更新 YAERModLoader.ini 与 AGENTS.md

**Files:**
- Modify: `src/YAERModLoader.ini`
- Modify: `AGENTS.md`

- [ ] **Step 1: 改 `src/YAERModLoader.ini`**

移除 `world_map_cursor_speed` 注释项(第 30-32 行):
旧:
```ini
; World map cursor movement speed multiplier
;  1 = default
;world_map_cursor_speed=1.5
```
删除这三行。

`[dlls]` 段(第 48-55 行)加 er_param 示例(注释, 排在前):
旧:
```ini
; dlls to load on game start
;  format: name=path_to_dll
; can use either relative or absolute paths
[dlls]
;itemlot_rate=dll/itemlot_rate.dll
;autoloot=dll/autoloot.dll
;no_dup_loot=dll/no_dup_loot.dll
;seamlesscoop=SeamlessCoop/ersc.dll
```
新:
```ini
; dlls to load on game start
;  format: name=path_to_dll
; can use either relative or absolute paths
;  NOTE: er_param must be listed before dlls that depend on the param API
;        (itemlot_rate, autoloot, and any param-consuming extension).
[dlls]
;er_param=dll/er_param.dll
;itemlot_rate=dll/itemlot_rate.dll
;autoloot=dll/autoloot.dll
;no_dup_loot=dll/no_dup_loot.dll
;seamlesscoop=SeamlessCoop/ersc.dll
```

- [ ] **Step 2: 改 AGENTS.md codegen 与架构说明**

AGENTS.md 第 92 行 codegen 段:
旧:
```
**Param definitions codegen:** `src/eldenring/param_defs.h` and `src/eldenring/defs/*.h` are generated by `src/eldenring/param_to_c.py` from Elden Ring XML definition files (not in repo). Run the script manually when param structs need updating; it reads from `ER/Defs/` and `ER/Meta/` relative to the script's working directory.
```
新:
```
**Param definitions codegen:** `src/extdlls/er_param/include/er_param/param_defs.h` and `src/extdlls/er_param/include/er_param/defs/*.h` are generated by `src/extdlls/er_param/param_to_c.py` from Elden Ring XML definition files (not in repo). Run the script manually when param structs need updating; it reads from `ER/Defs/` and `ER/Meta/` relative to the script's working directory (`src/extdlls/er_param/`).
```

AGENTS.md "What to avoid" 第 126 行:
旧:
```
- Do not edit `src/eldenring/defs/*.h` or `src/eldenring/param_defs.h` by hand; they are generated.
```
新:
```
- Do not edit `src/extdlls/er_param/include/er_param/defs/*.h` or `src/extdlls/er_param/include/er_param/param_defs.h` by hand; they are generated.
```

AGENTS.md Source layout 块(第 36-58 行附近)描述 `eldenring/` 子项:
旧(相关行):
```
  eldenring/      Static lib: game struct definitions, param table access, wstring helpers
```
新:
```
  extdlls/        Optional extension DLLs (auto-discovered by CMake glob)
    er_param/     Param provider DLL (param table access, pointers, wstring, cursor_speed)
```
(注: 原本 extdlls 已在 layout 中列出, 此处细化 er_param; 同时移除 eldenring 行。)

**Extension DLL API** 段(AGENTS.md 第 88-90 行附近):
旧:
```
**Extension DLL API:** External DLLs export a single `modloader_ext_init(modloader_ext_api_t*)` function returning `modloader_ext_def_t*`. The struct provides `on_uninit` and `on_param_initialized` callbacks. See `src/modloader/extdll_api.h` for the full API surface.
```
新:
```
**Extension DLL API (V1):** External DLLs export a single `modloader_ext_init(modloader_ext_api_t*)` function returning `modloader_ext_def_t*`. The struct provides `on_uninit` only (the `on_param_initialized` callback was removed in V1; param-dependent DLLs register via `er_param_api_get()` instead). See `src/modloader/extdll_api.h` for the main loader API, and `src/extdlls/er_param/include/er_param/er_param_api.h` for the param provider API. Param-consuming extdlls must list `er_param` before themselves in the `[dlls]` ini section (load order dependency; no build-time runtime dependency system).
```

- [ ] **Step 3: 验证配置/构建仍通过**

```bash
cmake --build cmake-build-debug --config Debug
```
预期: 成功(ini 与 md 不影响构建)。

- [ ] **Step 4: Commit**

```bash
git add src/YAERModLoader.ini AGENTS.md
git commit -m "docs: update ini and AGENTS for er_param extraction"
```

---

## Task 14: dist 打包追加 er_param.dll

**Files:**
- Modify: `src/CMakeLists.txt`

**说明:** dist 目标把 er_param.dll 纳入发行包。er_param.dll 在 `bin/.../dll/`, dist 输出在 `dist/`。需拷贝并纳入 zip/7z。

- [ ] **Step 1: 改 dist 拷贝命令**

`src/CMakeLists.txt` 第 16-19 行(dist make_directory + copy):
旧:
```cmake
add_custom_command(TARGET dist POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/dist"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:modloader_launcher>" "$<TARGET_FILE:modloader_dll>" "${CMAKE_CURRENT_SOURCE_DIR}/YAERModLoader.ini" "${CMAKE_SOURCE_DIR}/README.md" "${CMAKE_SOURCE_DIR}/LICENSE" "${CMAKE_BINARY_DIR}/dist/"
    COMMENT "Copying files...")
```
新(追加 er_param.dll):
```cmake
add_custom_command(TARGET dist POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/dist/dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:modloader_launcher>" "$<TARGET_FILE:modloader_dll>" "${CMAKE_CURRENT_SOURCE_DIR}/YAERModLoader.ini" "${CMAKE_SOURCE_DIR}/README.md" "${CMAKE_SOURCE_DIR}/LICENSE" "${CMAKE_BINARY_DIR}/dist/"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:extdll_er_param>" "${CMAKE_BINARY_DIR}/dist/dll/"
    COMMENT "Copying files...")
```

- [ ] **Step 2: 改 zip/7z 压缩命令纳入 dll 目录**

第 27-32 行:
旧:
```cmake
add_custom_command(TARGET dist POST_BUILD
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/dist"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${YAERMODLOADER_VERSION}.zip" --format=zip -- "$<TARGET_FILE_NAME:modloader_launcher>" "$<TARGET_FILE_NAME:modloader_dll>" "YAERModLoader.ini" "README.md" "LICENSE"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${YAERMODLOADER_VERSION}.7z" --format=7zip -- "$<TARGET_FILE_NAME:modloader_launcher>" "$<TARGET_FILE_NAME:modloader_dll>" "YAERModLoader.ini" "README.md" "LICENSE"
    COMMENT "Compressing to archives..."
)
```
新:
```cmake
add_custom_command(TARGET dist POST_BUILD
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/dist"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${YAERMODLOADER_VERSION}.zip" --format=zip -- "$<TARGET_FILE_NAME:modloader_launcher>" "$<TARGET_FILE_NAME:modloader_dll>" "YAERModLoader.ini" "README.md" "LICENSE" "dll/er_param.dll"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${YAERMODLOADER_VERSION}.7z" --format=7zip -- "$<TARGET_FILE_NAME:modloader_launcher>" "$<TARGET_FILE_NAME:modloader_dll>" "YAERModLoader.ini" "README.md" "LICENSE" "dll/er_param.dll"
    COMMENT "Compressing to archives..."
)
```

- [ ] **Step 3: 确认 dist 依赖含 er_param**

第 34 行 `add_dependencies(dist ...)`:
旧:
```cmake
add_dependencies(dist #[[embeddll]] modloader_launcher)
```
新:
```cmake
add_dependencies(dist #[[embeddll]] modloader_launcher extdll_er_param)
```

- [ ] **Step 4: 验证 dist 目标(可选, 较重)**

```bash
cmake --build cmake-build-debug --config Debug --target dist
```
预期: `dist/` 含 launcher/dll/ini/README/LICENSE 与 `dist/dll/er_param.dll`, 生成 zip/7z。若 tar 命令对子目录处理报错, 检查 `--` 后路径(相对 WORKING_DIRECTORY `dist`)。

- [ ] **Step 5: Commit**

```bash
git add src/CMakeLists.txt
git commit -m "build: include er_param.dll in dist package"
```

---

## Task 15: 最终全量验证 + 残留清理

**Files:** 检查项

- [ ] **Step 1: 确认 `src/eldenring/` 目录已不存在**

```bash
git ls-files src/eldenring
```
预期: 空输出(所有文件已 git mv, CMakeLists 已 git rm, 空目录不被 git 跟踪)。若有残留文件, 检查是否遗漏迁移。

- [ ] **Step 2: 全量构建(Release, 验证 LTO/静态 CRT 无误)**

```bash
cmake -S . -B cmake-build-release -G "Visual Studio 18 2026" -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release --config Release
```
预期: 全量 Release 构建成功。

- [ ] **Step 3: 测试**

```bash
ctest --test-dir cmake-build-debug -C Debug --output-on-failure
```
预期: smoke_param / smoke_filecache / smoke_no_dup_loot 全 PASS。

- [ ] **Step 4: 搜索残留旧引用**

```bash
rg "eldenring/" src/modloader
rg "er_param_find_table|er_wstring_impl_str|on_param_initialized" src/modloader
rg "eldenring/" src/extdlls
```
预期:
- `src/modloader` 内无 `eldenring/` include(主 loader 已内联 wstring)。
- `src/modloader` 内无 `er_param_find_table`/`er_wstring_impl_str`/`on_param_initialized`(已移除/迁移)。
- `src/extdlls` 内无 `eldenring/` include(已改 er_param)。
若 `autoloot`/`itemlot_rate` 残留 `on_param_initialized` 函数名, 确认已改为 `on_param_loaded`。

- [ ] **Step 5: 最终提交(若有清理改动)**

```bash
git status
# 若有改动:
git add -A
git commit -m "chore: final cleanup after param extraction"
```

---

## Self-Review

(写完计划后自查, 已修正如下:)

**1. Spec coverage:**
- §2.1/§2.2 接口 V1 → Task 5(extdll_api.h)✓
- §2.3 er_param_api_t → Task 1(api 头) + Task 9(provider 实现)✓
- §2.4 公共头 → Task 2(迁移) ✓
- §3.1 加载流程 → Task 9(param_thread)✓
- §3.2 观察者 → Task 9(provider_on_param_loaded/off + param_thread 快照遍历)✓
- §3.3 cursor_speed 内置 → Task 9(apply_cursor_speed + load_config + er_param.ini)✓
- §3.4 on_uninit → Task 9(on_uninit)✓
- §4.1 主 loader 移除项 → Task 3(CMake) + Task 6(extdll.c/h) + Task 7(config) + Task 8(patches)✓
- §4.2 内联 wstring → Task 8 ✓
- §5.1 目录布局 → Task 1/2 ✓
- §5.2 er_param CMakeLists → Task 1 + Task 2 修正 ✓
- §5.3 extdlls glob 分支 → Task 4 ✓
- §5.4 消费者改动 → Task 10(itemlot_rate) + Task 11(autoloot) + Task 12(no_dup_loot)✓
- §5.5 codegen → Task 2 Step 7 ✓
- §5.6 dist → Task 14 ✓
- §6 测试 → Task 12 Step 2 / Task 15 Step 3 ✓
- §7 配置 → Task 13 ✓
- 删除 eldenring → Task 3 + Task 15 Step 1 ✓

**2. Placeholder scan:** 无 TBD/TODO。所有代码步骤含完整代码。

**3. Type consistency:**
- `er_param_api_t` 字段(find_table/wstring_str/is_loaded/on_param_loaded/off_param_loaded)在 Task 1 头定义, Task 9 实现, Task 10/11 消费, 一致 ✓
- `on_param_loaded(void* userp)` 签名: Task 9(provider_on_param_loaded)、Task 10(itemlot on_param_loaded)、Task 11(autoloot on_param_loaded)一致 ✓
- `er_param_api_get_t` / `er_param_api_get` 名称一致 ✓
- `modloader_ext_def_t` 三字段(name/userp/on_uninit): Task 5 定义, Task 9/10/11/12 def 初始化一致 ✓
- `er_param::headers` 目标名: Task 1 CMakeLists 定义, Task 4 引用, 一致 ✓
- `extdll_er_param` 目标名: Task 1/2 CMakeLists, Task 14 dist 引用, 一致 ✓

(自查中发现并已修正: Task 9 Step 2 多余 base 取值已指明删除; Task 9 Step 3 补 menu_common_param.h include; Task 2 Step 3 include 路径需 `${CMAKE_SOURCE_DIR}/src` 而非 `..`; 各任务验证时点已说明避免过早全量构建失败。)