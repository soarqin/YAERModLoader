# Param 接口移出主 Loader 架构设计

- **日期**: 2026-06-27
- **范围**: 把 Elden Ring param 相关接口从主 mod loader 完全移出，成为独立的 `er_param` provider DLL，通过 ini `[dlls]` 列表顺序加载（在前），其他依赖它的 extdll 随后加载。
- **接口版本**: 重新锚定为 **V1**，不向后兼容旧 extdll（开发阶段，未到 1.0）。

## 1. 背景与目标

### 1.1 现状

当前 param 接口耦合在主 loader 中：

- `src/eldenring/param.c` 实现 `er_param_load_table` / `er_param_find_table` / `er_param_unload`，编译进 `eldenring` 静态库，链接进 `modloader_dll`。
- `src/eldenring/pointers.c` 实现 `er_pointers_init`（sig_scan `cs_regulation_manager`），供 param 加载使用。
- `src/eldenring/wstring.c` 实现 `er_wstring_impl_str` / `er_wstring_impl_str_mutable`（MSVC std::wstring SSO 解引用），被 param 加载和主 loader 的存档路径 hook 同时使用。
- 主 loader `patches/eldenring.c` 的 `async_operation_thread`（`src/modloader/patches/eldenring.c:81`）执行：`er_pointers_init(INIT_CS_REGULATION_MANAGER)` → `er_param_load_table()` → `extdlls_on_param_initialized()`，然后用 `er_param_find_table(L"MenuCommonParam")` 处理 `world_map_cursor_speed`。
- 主 loader 通过 `modloader_ext_api_t`（`src/modloader/extdll_api.h`）把 `er_param_find_table` 和 `er_wstring_impl_str` 分发给 extdll。
- 主 loader 在 `extdlls_on_param_initialized()` 里遍历已注册 extdll 调用各自的 `on_param_initialized` 回调。
- extdll（如 `itemlot_rate`）通过 `the_api->er_param_find_table` 和 `on_param_initialized` 回调消费 param。

### 1.2 目标

让 mod loader 接口更通用：param 接口从主 loader 移出，作为独立 DLL 挂载。所有依赖 param 的 DLL 使用该 DLL 提供的接口。**不引入依赖系统**——DLL 按 ini 列表顺序加载，只要 param provider 排在前即可保证依赖者正常工作。

### 1.3 三个角色的边界

1. **主 loader（`modloader_dll`）**——通用 mod loader。只保留：配置、mod 文件覆盖、存档替换 hook、代理 DLL stub、extdll 加载机制、`hook`/`unhook`/`sig_scan`/`get_module_image_base` 通用 API。**完全移除** param/wstring/pointers 代码，不再链接 `eldenring` 静态库，不参与 param 通知。

2. **`er_param` provider DLL**——新独立 extdll，包含 `param.c`/`pointers.c`/`wstring.c` 及全部相关头（`param.h`/`param_defs.h`/`defs/*.h`/`wstring.h`/`pointers.h`）。职责：通过主 loader api 拿 `sig_scan`，启动自己的 async 线程加载 param 表；维护观察者列表，加载完成后通知依赖者；导出 `er_param_api_get()` 提供 `er_param_api_t`；内置 `world_map_cursor_speed` 处理。

3. **依赖 param 的 extdll（`itemlot_rate` 等）**——通过 `GetModuleHandleW(L"er_param.dll") + GetProcAddress("er_param_api_get")` 拿 `er_param_api_t`，注册 `on_param_loaded` 回调并调用 `find_table`。不再依赖主 loader 的 param 通知路径。

## 2. 接口设计

### 2.1 主 loader `modloader_ext_api_t`（V1）

移除 param 相关字段，只留通用能力：

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

原 `er_param_find_table` / `er_wstring_impl_str` 字段删除。

### 2.2 `modloader_ext_def_t`（V1）

移除 `on_param_initialized` 回调字段（param 通知完全去中心化）：

```c
typedef struct modloader_ext_def_s {
    const char *name;
    void *userp;
    void (*on_uninit)(void*);
    /* on_param_initialized 移除 — param 通知改由 er_param DLL 的观察者机制 */
} modloader_ext_def_t;
```

### 2.3 `er_param_api_t`（er_param provider 对外接口）

er_param 导出单一入口：

```c
typedef const er_param_api_t *(*er_param_api_get_t)(void);
__declspec(dllexport) const er_param_api_t *er_param_api_get(void);
```

返回的结构体：

```c
typedef struct er_param_api_s {
    uint32_t api_version;                                      /* = 1 */
    const er_param_table_t *(*find_table)(const wchar_t *name);
    const wchar_t *(*wstring_str)(const er_wstring_impl_t *str);

    /* 观察者机制: param 表加载完成时通知 */
    bool (*is_loaded)(void);
    /* 注册回调. 若已加载则同步立即调用; 否则加入观察者列表, 异步线程加载完成后调用.
       返回 true 表示成功(含已加载立即调用的情况). */
    bool (*on_param_loaded)(void (*cb)(void *userp), void *userp);
    /* 注销回调(消费者 on_uninit 时调用, 防止 param 线程回调已卸载的代码). 以 (cb,userp) 为键. */
    void (*off_param_loaded)(void (*cb)(void *userp), void *userp);
} er_param_api_t;
```

`param_api_version == 1` 供消费者校验。

### 2.4 公共头（消费者 include）

er_param 项目的 `include/er_param/` 目录对外提供：

- `er_param_api.h`——`er_param_api_t` + `er_param_api_get_t` 定义。
- `param.h`——`er_param_table_t` 结构体 + `er_param_table_iterate_begin/end` 宏 + `param_table_find_id` 宏（内容不变，仅路径迁移）。
- `wstring.h`——`er_wstring_impl_t` 结构体 + 函数声明。
- `param_defs.h` / `defs/*.h`——生成的 param 结构体（menu_common_param.h、itemlot_param.h 等）。

消费者 `#include <er_param/param.h>`、`#include <er_param/defs/itemlot_param.h>` 等访问表字段；通过 `er_param_api_t` 拿函数。

## 3. er_param provider DLL 设计

### 3.1 加载流程

`modloader_ext_init(modloader_ext_api_t *api)` 被主 loader 调用时：

1. 保存 `api`（用其中的 `sig_scan`/`get_module_image_base`，供 pointers.c 使用）。
2. 读取自身 DLL 目录下的 `er_param.ini`（含 `world_map_cursor_speed` 等配置）。
3. 创建 async 线程：
   - `er_pointers_init(INIT_CS_REGULATION_MANAGER)`（使用 `get_module_image_base(NULL, &size)` + `sig_scan`）。
   - `er_param_load_table()`（同现有逻辑，等待 regulation manager 就绪，最多 ~30 秒）。
   - 加锁：设 `is_loaded = true`，遍历观察者列表逐个调用 `cb(userp)`，清空列表。
   - 内置 cursor_speed 处理：`find_table(L"MenuCommonParam")` → `er_param_table_iterate_begin` 遍历，`param->worldMapCursorSpeed *= config.world_map_cursor_speed`（若配置值 ≠ 1.0）。

`er_param_api_get()` 返回静态 `er_param_api_t` 实例（函数指针指向 provider 内部实现）。

### 3.2 观察者机制

- 观察者列表用 CRITICAL_SECTION 保护，存储 `(cb, userp)` 对。
- `on_param_loaded(cb, userp)`：进锁，若 `is_loaded` 为真 → 立即在锁外（或锁内调用，注意避免重入）调用 `cb(userp)` 并返回 true；否则入队，返回 true。**注意**：为避免回调者再调 `on_param_loaded` 导致死锁，回调在锁外执行，但判定 `is_loaded` 与入队必须在锁内原子完成，防止漏通知。
- `off_param_loaded(cb, userp)`：进锁，从列表移除匹配的 `(cb, userp)`，避免 param 线程回调已卸载的消费者代码。
- 加载线程遍历时：拷贝当前列表到局部数组，清空列表，释放锁，再逐个回调（快照式遍历，回调期间允许新的 `on_param_loaded` 立即执行）。

### 3.3 cursor_speed 内置

不单独建 extdll。er_param 自己读 `er_param.ini` 的 `world_map_cursor_speed`（默认 1.0，范围与现有一致 0.5–10.0，≤0 视为 1.0），在 param 加载完成后处理 `MenuCommonParam`。主 loader 不再保留该 config 字段及 ini 解析。

### 3.4 on_uninit

er_param 的 `on_uninit`：等待 async 线程退出（复用主 loader 现有的 5 秒超时 + TerminateThread 兜底模式，因 loader lock 下 FreeLibrary 风险可接受——与主 loader `eldenring_uninstall` 现有注释一致），`er_param_unload()` 清表，销毁临界区。

## 4. 主 loader 改动

### 4.1 移除项

- **链接**：`src/modloader/CMakeLists.txt` 的 `target_link_libraries(modloader_dll ...)` 去掉 `eldenring`。
- **构建**：`src/CMakeLists.txt` 移除 `add_subdirectory(eldenring)`。`src/eldenring/` 目录整体从构建移除（文件迁移至 er_param 项目，见 §5）。
- **`patches/eldenring.c`**：
  - `async_operation_thread`（`src/modloader/patches/eldenring.c:81`）：移除 `er_pointers_init`、`er_param_load_table`、`extdlls_on_param_initialized`、`MenuCommonParam`/`world_map_cursor_speed` 整段。仅保留 `cpu_affinity_strategy` 设置（若 `config.cpu_affinity_strategy != 0`）。
  - `eldenring_uninstall`（`:386`）：移除 `er_param_unload()` 调用。
  - 移除 `#include "eldenring/wstring.h"` / `"eldenring/param_internal.h"` / `"eldenring/pointers.h"` / `"eldenring/defs/menu_common_param.h"`。
- **`extdll.c`**：
  - `ext_api`（`:53`）去掉 `.er_param_find_table` / `.er_wstring_impl_str`。
  - 移除 `extdlls_on_param_initialized()` 函数。
  - `extdll_t` 去掉 `on_param_initialized` 字段；`load_all` 里赋值（`:111`）与 `unload_all` 里清空（`:161`）逻辑删除。
  - 移除 `#include "eldenring/wstring.h"`。
- **`extdll_api.h`**：按 §2.1/§2.2 更新两个结构体。
- **`extdll.h`**：移除 `extdlls_on_param_initialized` 声明。
- **`config.h` / `config.c`**：移除 `config_t::world_map_cursor_speed` 字段及 ini 解析（`[elden_ring]` 段的 `world_map_cursor_speed` 分支）。

### 4.2 主 loader 内联 wstring SSO

`map_archive_path` hook 仍需解引用游戏 wstring，但不再依赖 `er_wstring_impl_str_mutable`。在 `patches/eldenring.c` 本地内联 SSO 逻辑，并保留一个最小本地结构体（字段布局与游戏 wstring 一致）：

```c
/* 内联自 wstring.c 的 SSO 逻辑 (主 loader 不再链接 wstring.c) */
typedef struct er_wstring_local_s {
    void *unk;
    wchar_t *string;
    void *unk2;
    uint64_t length;
    uint64_t capacity;
} er_wstring_local_t;

/* MSVC std::wstring SSO: capacity >= 8 wchar_t (16 bytes) 用堆指针, 否则内联 */
static wchar_t *wstring_str_mutable(er_wstring_local_t *str) {
    return (sizeof(wchar_t) * str->capacity >= 16) ? str->string : (wchar_t*)&str->string;
}
```

`map_archive_path` 的签名与 `er_wstring_impl_t*` 形参改为 `er_wstring_local_t*`（指针布局相同，仅类型名不同）。此结构体仅主 loader 内部使用，不从 er_param include。

## 5. er_param 项目布局与构建

### 5.1 目录布局

```
src/extdlls/er_param/
  CMakeLists.txt                     自包含: 构建 SHARED + 导出 INTERFACE headers
  include/er_param/                   对外公共头 (INTERFACE 导出)
    er_param_api.h                   er_param_api_t + er_param_api_get_t
    param.h                          er_param_table_t + iterate 宏
    wstring.h                        er_wstring_impl_t 结构体
    param_defs.h                     生成 (汇总 include defs/*)
    defs/*.h                         生成 (从 src/eldenring/defs/ 迁入)
  src/                               私有实现
    param.c, param_internal.h
    pointers.c, pointers.h
    wstring.c
    provider.c                       modloader_ext_init + er_param_api_get + 观察者线程 + cursor_speed
  param_to_c.py                       代码生成脚本 (从 src/eldenring/ 迁入)
  er_param.ini                        cursor_speed 等配置
```

迁移说明：`src/eldenring/` 下的 `param.c`/`param_internal.h`/`param.h`/`param_defs.h`/`defs/`/`pointers.c`/`pointers.h`/`wstring.c`/`wstring.h`/`param_to_c.py` 全部移入 `src/extdlls/er_param/`（头文件入 `include/er_param/`，实现入 `src/`，脚本与 ini 入项目根）。`param_internal.h` 的 `#include "param.h"` 改为 `#include <er_param/param.h>`，相应调整其余内部 include 路径。

### 5.2 er_param 自身 CMakeLists.txt

职责：

- 构建共享库：`add_project(extdll_er_param SHARED <src files> ... OUTPUT_NAME er_param OUTPUT_SUBDIR dll NO_PREFIX)` → 产出 `er_param.dll`，放 `bin/.../dll/`。
- 创建 INTERFACE 头目标：`add_library(er_param::headers INTERFACE)` + `target_include_directories(er_param::headers INTERFACE include)`。
- `extdll_er_param` link `klib`（param.c 用 khash）、`shlwapi`（若有 StrCmp 等）、`inih`（er_param.ini 解析，与 itemlot_rate 同款），include 自己 `src/` 与 `include/er_param/`。

### 5.3 extdlls 顶层 CMakeLists.txt（glob 发现 + 子目录分支）

现有 glob 循环扩展为分支规则：

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
        # 子目录自包含构建 (er_param: 需定义 INTERFACE headers 目标)
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

依赖机制：消费者 extdll（itemlot_rate 等）通过 `target_link_libraries(extdll_${dir} PRIVATE er_param::headers)` 引用 `er_param::headers` INTERFACE 目标。即使 er_param 在 glob 循环中排在后面才创建，CMake 允许目标在脚本稍后创建时被引用（CMake 文档规则：被 link 的依赖目标可在脚本后续创建，只要发起 link 的主目标已存在）。CMake 拓扑排序自动保证 `er_param::headers` 先于消费者配置。**不引入运行期依赖系统**——仅编译期头依赖 + 运行期按 ini 列表顺序加载。

### 5.4 消费者 extdll 改动

以 `itemlot_rate` 为例：

- `#include <eldenring/param.h>` / `<eldenring/defs/itemlot_param.h>` 改为 `<er_param/param.h>` / `<er_param/defs/itemlot_param.h>`。
- `#include <modloader/extdll_api.h>` 保留（拿 `sig_scan`/`hook` 等）。
- `on_param_initialized` 回调不再由主 loader 触发。改为：`modloader_ext_init` 时 `GetModuleHandleW(L"er_param.dll") + GetProcAddress("er_param_api_get")` 拿 `er_param_api_t`；若为 NULL 则该 extdll 的 param 功能跳过（不崩溃）；否则 `api->on_param_loaded(my_on_param_loaded, NULL)` 注册回调。
- `my_on_param_loaded(userp)` 内用 `api->find_table(L"ItemLotParam_map")` 等替代 `the_api->er_param_find_table`。
- `on_uninit` 里 `api->off_param_loaded(my_on_param_loaded, NULL)` 注销回调（防 param 线程回调已卸载代码）。
- `def` 结构体去掉 `on_param_initialized` 字段（已从 `modloader_ext_def_t` 移除）。

`autoloot`、`no_dup_loot`：`autoloot` 用 `on_param_initialized` 做 sig_scan + hook（不访问 param 表，仅借 param 加载完成这一时序确保游戏已充分初始化）；改为通过 `er_param_api_t::on_param_loaded` 注册同样的 sig_scan+hook 逻辑即可。`no_dup_loot` 不用 param（其 `def.on_param_initialized` 原为 NULL，`def` 仅需去掉该字段以匹配新 `modloader_ext_def_t`），无需其它改动。

### 5.5 codegen 脚本

`param_to_c.py` 迁入 `src/extdlls/er_param/`，其输出路径相对脚本工作目录（`param_defs.h`、`defs/*.h`）调整为写入 `include/er_param/`。AGENTS.md 的 codegen 说明同步更新指向新位置。

### 5.6 dist 打包

`src/CMakeLists.txt` 的 dist 自定义命令需追加 er_param.dll（及其他新 extdll）。当前 dist 命令仅拷贝 launcher/dll/ini/README/LICENSE；er_param.dll 在 `bin/.../dll/`，需纳入发行包（放 dll/）。具体打包命令在实现阶段补充。

## 6. 测试

- `tests/smoke_param.c` 仅测 `khash_wstr`（src/common），不依赖 eldenring 静态库，**不受影响**，无需改动。
- `smoke_filecache`、`smoke_no_dup_loot` 同理不受影响。
- 不新增针对 er_param 内部逻辑的单元测试（其逻辑依赖游戏运行时，无法在无游戏环境单测）；观察者/竞态逻辑靠代码审查 + 实际游戏加载验证。

## 7. 配置文件

`YAERModLoader.ini` 的 `[elden_ring]` 段移除 `world_map_cursor_speed` 注释项（该功能移交 er_param.ini）。`[dlls]` 段示例追加 `er_param=dll/er_param.dll`（注释示例，需排在依赖者前）。

`er_param.ini`（er_param 项目自带）示例：

```ini
; World map cursor movement speed multiplier
;  1 = default
world_map_cursor_speed=1.0
```

## 8. 改动文件清单（概览）

**新增**：
- `src/extdlls/er_param/`（CMakeLists.txt、include/er_param/*、src/*、param_to_c.py、er_param.ini）。

**迁移**（src/eldenring/ → src/extdlls/er_param/，头入 include/er_param/）：
- `param.c`→`src/param.c`、`param.h`→`include/er_param/param.h`、`param_internal.h`→`src/param_internal.h`、`param_defs.h`→`include/er_param/param_defs.h`、`defs/*.h`→`include/er_param/defs/*.h`、`pointers.c/h`→`src/`、`wstring.c/h`→`src/wstring.c` + `include/er_param/wstring.h`、`param_to_c.py`→项目根、`CMakeLists.txt`（新建，替换原 eldenring CMakeLists）。
- 新增 `provider.c`。

**修改**：
- `src/modloader/extdll_api.h`（§2.1/§2.2 两个结构体）。
- `src/modloader/extdll.h`（移除 `extdlls_on_param_initialized` 声明）。
- `src/modloader/extdll.c`（ext_api、extdll_t、load_all/unload_all）。
- `src/modloader/config.h` / `config.c`（移除 `world_map_cursor_speed`）。
- `src/modloader/patches/eldenring.c`（async_operation_thread、uninstall、内联 wstring、移除 include）。
- `src/modloader/CMakeLists.txt`（去 eldenring 链接）。
- `src/CMakeLists.txt`（移除 `add_subdirectory(eldenring)`，dist 追加 er_param.dll）。
- `src/extdlls/CMakeLists.txt`（glob 分支规则 + er_param::headers link）。
- `src/extdlls/itemlot_rate/main.c`（include + 回调注册改 er_param api）。
- `src/extdlls/autoloot/main.c`（on_param_initialized 改 er_param api 注册）。
- `src/YAERModLoader.ini`（移除 world_map_cursor_speed 注释，[dlls] 加 er_param 示例）。
- `AGENTS.md`（codegen 路径、eldenring 静态库说明、extdll API 说明更新）。

**删除**：
- `src/eldenring/`（整体迁移后移除，CMakeLists.txt 一并删）。

## 9. 风险与权衡

- **运行期依赖靠 ini 顺序**：er_param 必须在 `[dlls]` 列表排在依赖者前。文档与 ini 注释明确此约束；消费者 `GetModuleHandle` 失败时静默跳过 param 功能（不崩溃），降低误配影响。
- **观察者竞态**：`on_param_loaded` 在已加载时立即调用、未加载时入队，临界区保护判定+入队原子性，回调在锁外执行避免死锁。`off_param_loaded` 防止卸载后被回调。
- **loader lock 下线程终止**：er_param `on_uninit` 沿用主 loader 现有 5 秒超时 + TerminateThread 兜底（与 `eldenring_uninstall` 注释一致），接受进程退出时风险。
- **不向后兼容**：旧 extdll（依赖主 loader `on_param_initialized` 路径与 `ext_api->er_param_find_table`）需按新接口迁移；开发阶段可接受。