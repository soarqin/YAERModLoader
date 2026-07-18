# YAFSML 缺陷修复与结构重构计划

本文件记录一次系统性的代码审查结论、缺陷清单与分阶段执行计划。目标:审查仓库代码、修复已确认缺陷、并在保持行为的前提下重构使结构更合理。

## 决策基线（已确认）

- **ER 适配器迁移**:迁移到共用的 `win32_hooks` + `save_mapping`,并把存档映射扩展到 `.co2` 无缝联机存档;作为**独立的末阶段**执行,可单独回退。
- **proxy 转发修复**:用 **NASM 生成 `jmp` 裸桩**,消除对编译器尾调用优化的依赖。
- **死代码**:全部删除,并同步清理测试与 CMake。
- **`steam/vdf.c`**:修复其真实内存安全问题(第三方 vendored 代码,但位于 `src/steam`)。

## 执行原则

- 每个阶段结束都跑一次完整验证,绿了才进下一阶段;阶段之间可单独回退。
- 缺陷修复不改变对外行为（ER 迁移除外,它是有意的行为收敛）。
- 遵循 `AGENTS.md`:C11-only、主 DLL 用 `mi_*`/共享代码用 `yaer_mem_*`、`wchar_t` 路径、surgical changes、匹配既有风格。
- 版本策略:仅在 `CHANGELOG.md` 的 `#### Unreleased` 段补记条目,**不**改 `src/CMakeLists.txt` 的 `YAFSML_VERSION`,不发版。

## 验证命令（每阶段复用）

```
cmake -S . -B cmake-build-debug -G "Visual Studio 18 2026" -DBUILD_TESTING=ON
cmake --build cmake-build-debug --config Debug
ctest --test-dir cmake-build-debug -C Debug --output-on-failure
```

---

## 阶段 0 — 基线

配置 + 构建 + 跑测,确认改动前 smoke 测试全绿,作为对照基线。

---

## 阶段 1 — 已确认缺陷修复（内存安全 / 正确性,不改行为）

### 1a. `process/scanner.c` 下溢越界（高）
- `sig_scan_without_mask`（:61）、`sig_scan_with_mask`（:110）函数首部加
  `if (pat_size == 0 || base == NULL || data_size < pat_size) return NULL;`,
  消除 `while (s <= data_size - pat_size)` 中 `size_t` 减法下溢导致的越界读。
- `:285-287` 两处 `LocalAlloc` 加 NULL 检查。
- 简化 `patches/allocator.c:65` `find_last_table_entry` 与 `dl_allocator.c` 中误导性的
  `remaining >= 19` 循环守卫（安全性现由 scanner 内部保证）。
- **新增 `tests/smoke_scanner.c`**:覆盖正常命中、无命中、`pat_size > data_size`、`data_size == 0`。
  scanner.c 已在 `process` 静态库、由 `SMOKE_COMMON_LIBRARIES` 链接,无需改 CMake。

### 1b. `process/singleton.c` fd4 竞态（中）
- `singleton_find_slot`（:709）对 fd4 map 的 `kh_get` 纳入 `singleton_fd4_lock` 共享锁,
  与持锁的 `kh_put`（:641-675,可 rehash）配对。
- `singleton_fd4_finished`（:78）改为 `volatile LONG` + Interlocked 读写。
- `reflection_va`（:553）补节归属校验,与 `slot_va` / `get_name_va` 对齐,防签名误报导致的错误函数调用。

### 1c. `steam/vdf.c` + `steam/app.c`（中）
- `vdf.c:236` 改 `_wfopen(path, L"rb")` 二进制模式;`:241` 校验 `ftell`（<0 失败）;`:246` 校验 `fread` 字节数;缓冲末尾补 NUL 或以 `size` 显式限界。
- 内层无界扫描（:190-191, :202-203）加 `end` 边界判断。
- `assert`（:170-172, :197, :149-150）改为畸形输入时优雅返回 / 跳过。
- 全部 `LocalAlloc` / `LocalReAlloc`（:32, :68, :132, :157, :176, :245）加 NULL 检查。
- `isdigit` / `isalpha`（:97-100）入参转 `(unsigned char)`。
- `app.c:40, :60` 根 `key == NULL` 先判空再 `strcmp`;`vdf.c:279` 同理。
- `app.c:56, :69` 的 `%hs`（CP_ACP）改为 `MultiByteToWideChar(CP_UTF8, ...)`,修复非 ASCII 库路径损坏。

### 1d. modloader / process 其余低危项
- `patches/properties.c:86-87` `text_size` / `rdata_size` 初始化为 0。
- `patches/window_flash.c:29` 静态刷子用 `InterlockedCompareExchangePointer` 惰性初始化,消除竞态与 GDI 泄漏。
- `patches/allocator.c:129, :164` `get_module_image_base` 返回 NULL 检查;`:190` ER graphics 分支失败走 `heap_allocator_failed` 日志。
- `process/util.c:46` `GetProcessAffinityMask` 返回值检查。
- `process/pe.c:19-24`、`image.c:20-27` 补 `e_lfanew` 上界与 `Magic` 校验。
- `patches/common.c:139-144` Wwise 签名回退目标校验落在镜像内。

**验证**:build + ctest 全绿（含新增 `smoke_scanner`）。

---

## 阶段 2 — 死代码删除（同步清理测试 / CMake）

- 删 `modloader/filecache.c` + `filecache.h`;从 `modloader/CMakeLists.txt:34` 移除;
  从 `tests/CMakeLists.txt:21-22` 移除映射;删 `tests/smoke_filecache_mt.c`。
  `smoke_filecache.c` 实为独立 khash 测试（不依赖 filecache.c）,保留并重命名为 `smoke_khash_wstr.c` 以正名。
- 删 `dl_allocator.c:93-134`（`table_first` / `table_last_er` / `fill_table`）+ `dl_allocator.h:67-69`。
- 删 `dl_device.c` `seen_targets` + `ml_dl_device_seen` / `mark_seen` + `dl_device.h:123-124`。
- 删 `mod.c:71-73` `mods_file_search_prefixed` + `mod.h:26`;删 `mod.h:19` 悬空 `typedef struct mod_t`。
- 删 `vfs.c:653-678` `vfs_route_read_path_a` + `vfs.h:49`;改 `smoke_vfs.c:167` 对应断言。
- 删 `eldenring.c:157-162` `warn_once_bool`、`:89-109` 注释的 `get_game_version`。
- 删 `launcher.c:15-18, :183-260, :292-297` 注释的 LZMA 块及 `LzmaDec` / `Alloc` include。

**验证**:build + ctest 全绿（确认无链接错误）。

---

## 阶段 3 — 低风险结构重构（行为不变）

### 3a. `vfs.c` 去重与热路径优化
- 抽取通用"双检缓存插入"助手,收敛 `vfs_lookup_domain`（:369-423）、`vfs_virtual_to_uid`（:465-512）、`vfs_route_writable_path`（:589-635）。
- 抽取"容量翻倍增长数组"助手（7 处）。
- `vfs_is_package_path`（:582）由 O(N) 全表扫描改为索引期构建的物理路径 khash 集合,
  消除每次 `CreateFile` 命中游戏目录内路径时的线性扫描。此项触碰热路径,由 `smoke_vfs*` 三个测试守护。

### 3b. 全局收敛
- `extdll.c:30-32`、`mod.c:23,25` 的非 static 外部链接全局改 `static`,统一走
  `extdlls_count()` / `mods_count()` 访问器,移除头文件 `extern`。

### 3c. include 风格统一
- patches 内统一为 `"modloader/xxx.h"` / `"process/xxx.h"` 形式,消除 `"../lifecycle.h"` 之类相对混用。

### 3d. ANSI→宽转换统一
- `mod.c:91-108` 内联转换改用 `path_convert.c` 的 `ml_path_from_ansi`。

### 3e. `asset_hooks.c`（1028 行）拆分
- RSA/DER 解析（:229-320）+ MountEbl 模式匹配（:147-194）抽到 `asset_sig.c`（纯函数,可测）。
- BootBoost 挂载编排（:322-523）抽到 `boot_boost.c`。
- detour / 安装留在 `asset_hooks.c`。保持 `ML_ASSET_HOOKS_TEST` 测试入口不变。

**验证**:build + ctest 全绿（`smoke_asset_hooks`、`smoke_vfs*` 重点确认）。

---

## 阶段 4 — proxy NASM jmp 裸桩（中）

- 新增 `proxy/proxy_stubs.asm`:用 NASM 宏为每个导出生成 `jmp [rel <ptr>]`,寄存器 / 栈参原样穿透,Debug / Release 均正确。
- `.c` 保留启动期 `GetProcAddress` 填充指针,删除手写 `Fake*` 返回式转发器;`.def` 继续控制导出名。
- 补 proxy 内 `GetSystemDirectoryW` 返回值检查、`Original` 指针 NULL 检查。

**验证**:build 后 `dumpbin /exports` 对照三个 `.def`,导出名与数量一致（winhttp 82 / dxgi 20 / dinput8 6）。

---

## 阶段 5 — ER 适配器迁移（最高风险,独立末阶段）

### 5a. 扩展 `save_mapping`
- `ml_save_mapping_route` 的扩展名匹配（:215 硬编码 `.sl2`）改为支持 {扩展名 → override 名} 小表。
- `ml_save_mapping_init` 接受主存档（`.sl2`）与无缝联机（`.co2`）两组 override。
- 为双扩展映射补 `smoke_save_mapping` 用例。

### 5b. 重写 `eldenring.c`
- 改用 `common_install` + `ml_win32_file_hooks_install` + 扩展后的 `ml_save_mapping_init`,
  替换其自带的 CreateFileW/A/2、CopyFileW、DeleteFileW/A、CreateDirectoryW/A/ExW hook 与 `route_replaced_file`。

### 5c. 保留 ER 专属能力
- `map_archive_path`（归档位置解析器 hook）、成就重置线程、CPU 亲和性、SteamAPI 延迟 hook。
- 删除 `:116-395` 旧 hook 体系与 `replaced_save_filename*` 静态区（改由 save_mapping 承担）。
- 预计 `eldenring.c` 539 → ~200 行,且不再直接调 MinHook。

### 5d. `gamehook.c`
- ER 分支的 install / uninstall 与 win32_hooks / save_mapping 对称化。

**验证**:build + ctest（save_mapping 用例）。

> ⚠️ **游戏内文件 hook 行为无法冒烟测试**。此阶段完成后需要在真实 Elden Ring
> （含无缝联机存档改名场景）手动验证。交付时会附手测清单。

---

## 收尾

- 在 `CHANGELOG.md` 的 `#### Unreleased` 段补记本次修复 / 重构条目（不改 `YAFSML_VERSION`,不发版）。
- 全量 build + ctest 最终确认。

---

## 未纳入项（低收益 / 高 churn,如需可再加）

- `process/util.c` 移出 process 库。
- `steam` 目标拆分 app/vdf（launcher 用）与 api（DLL 用）。
- proxy 表驱动化以外的进一步抽象。
- config `is_current_game_section` 缓存 game 描述符。

---

## 缺陷清单速查（审查产出）

### 高
- `scanner.c:72,121` + `patches/allocator.c:65` + `regulation.c:94`:`data_size - pat_size` 无符号下溢 → 越界读;allocator 路径的越界误报可放大为 `fill_allocator_table` 任意范围写。

### 中
- `singleton.c:709 vs 641-675, 78`:fd4 map 无锁读 vs 持锁写 + 非原子 finished 标志。
- `singleton.c:553-567`:reflection 指针未验证 + get_name 取首个匹配。
- `vdf.c:170-172,197,149`:Release 下 assert 失效 → NULL 解引用 / `data_value[-1]` 越界。
- `vdf.c:190-191,202-203,245`:无 NUL 终结缓冲被无界扫描。
- `vdf.c:236,241,246`:文本模式 + ftell/fread 未校验 → 解析未初始化内存。
- `app.c:40`（及 `vdf.c:279`）:根 key 为 NULL 时 strcmp 崩溃。
- `app.c:56,69`:`%hs` ANSI 转换 UTF-8 VDF → 非 ASCII 路径损坏。
- proxy `Fake*` 零参转发依赖尾调用优化,Debug 构建下多参 API 传坏参数。

### 低（择要）
- `scanner.c:285`、`vdf.c` 多处分配未检查。
- `properties.c:115-129` 节缺失读未初始化;`:31,73` 无卸载 / 标志不可复位。
- `window_flash.c:29` 静态刷子竞态 + GDI 泄漏。
- `util.c:32-46` affinity mask 未初始化使用 / Size==0 死循环。
- `pe.c:19-24`、`image.c:20-27` 头字段校验不完整。
- `dl_device.c:225` expand_path 分配尺寸溢出未检查;`:449-536` restore/push 逐字节相同（存疑）。
- proxy `GetSystemDirectoryW` 未检查 / `Original` NULL 未检查。

### 死代码
- `filecache.c/.h`、`dl_allocator.c:93-134`、`dl_device.c` seen 系列、`mod.c` `mods_file_search_prefixed`、`vfs.c` `vfs_route_read_path_a`、`eldenring.c` `warn_once_bool` 与注释 `get_game_version`、`launcher.c` 注释 LZMA 块、`mod.h:19` 悬空 typedef。

---

## 执行结果与偏差记录

全部阶段已执行完毕,`cmake-build-msvc`(VS 2026,Debug)全量构建通过、32 个 smoke 测试全绿(新增 `smoke_scanner`,删除 `smoke_filecache_mt`,`smoke_filecache`→`smoke_khash_wstr`)。

**阶段 1（缺陷修复,全部完成）**:scanner 下溢守卫 + 分配检查 + 新增测试;singleton fd4 竞态改共享锁 + `volatile LONG` + reflection 指针对齐校验;vdf 二进制模式/`ftell`·`fread` 校验/NUL 终结/畸形输入优雅返回/分配检查/ctype 转换,app.c NULL-key 守卫 + UTF-8 路径解码;properties 未初始化 size、window_flash 刷子原子化、util affinity 检查 + `Size==0` 守卫、image.c 头校验、common Wwise 回退目标校验、allocator graphics 分支日志。

**阶段 2（死代码,全部完成）**:按清单删除,同步清理 CMake 与测试。附带删除因此孤立的 `vfs_lookup_prefixed`(仅被已删的 `mods_file_search_prefixed` 调用)。

**阶段 3（部分完成,含经评估的偏差）**:
- ✅ 3b 全局静态化(`extdll.c`/`mod.c`);✅ 3e 抽出 `asset_sig.c`(纯签名/crypto 函数,测试覆盖)。
- ⏭️ 3a **未做 `vfs_is_package_path` 改哈希集合与"双检缓存插入"助手抽取**。原因:前者要求与 `CompareStringOrdinal(TRUE)` 完全一致的大小写不敏感哈希,对全 Unicode 难以无风险等价,且改动位于并发敏感热路径,违背本阶段"行为不变"约束;后者三处结构差异较大(代际门控/锁/取值时机),强行统一会比重复更晦涩。均属"避免过度抽象"的取舍。
- ⏭️ 3d **未做 ANSI→宽转换统一**:`mod.c` 的 `mods_file_route_read_a` 使用 `MAX_PATH` 栈缓冲快路径,是有意的性能优化,并非意外重复;换成 `ml_path_from_ansi`(始终堆分配)会在热路径引入退化。
- ⏭️ 3c **未做全局 include 风格清扫**:纯风格化、跨文件 churn 大、收益低;仅在 Phase 5 重写 `eldenring.c` 时顺带修正了其 `"../lifecycle.h"` 相对包含。

**阶段 4（完成）**:proxy 全部纯转发导出改为 `proxy/proxy_stubs.asm` 中的 NASM `jmp` 裸桩,`.def` 保持不变(导出名不变,导出表风险低);补 `GetSystemDirectoryW` 返回值检查。`dumpbin /exports` 确认 `YAFSML.dll` 仍导出 107 个符号,含 `WinHttpOpen`/`WinHttpSendRequest`/`DXGID3D10CreateDevice` 等多参函数。裸桩对 `Original==NULL` 的处理与原 C 版一致(NULL 时崩溃),未逐桩加 NULL 检查(正确返回值不可知,保持行为对等)。

**阶段 5（完成,需手动验证)**:save_mapping 扩展为「扩展名→override 名」小表(新增 `ml_save_mapping_init_root` / `ml_save_mapping_add_extension`,保留 `ml_save_mapping_init` 兼容),`smoke_save_mapping` 增补 ER `.sl2`+`.co2` 双扩展用例;`eldenring.c` 由 510 行精简到约 300 行,删除自带的 9 个 Win32 hook 与 `route_replaced_file`,改用 `ml_win32_file_hooks_*` + `ml_save_mapping_*`,其余仅保留 ER 专属(归档解析器、成就重置线程、CPU 亲和、SteamAPI 延迟 hook),并把归档解析器/Steam hook 改用 `ml_hook_install`;`gamehook.c` ER 分支无需改动(common 的 install/uninstall 本已对称)。

### ⚠️ Phase 5 需要在真实 Elden Ring 手动验证的项
游戏内文件 hook 行为无法用冒烟测试覆盖,请在真实环境确认:
1. 加载含 mod 的存档,确认 mod 资源(`regulation.bin`、`.dcx` 等)生效(归档解析器 + Win32 VFS + Dantelion 资产 hook 通路)。
2. 设置 `replace_save_filename`,确认主存档被重定向到新文件名(`.sl2` 与 `.sl2.bak`),原版 `ER0000.sl2` 不被写入。
3. 设置 `replace_seamless_coop_save_filename` 并配合无缝联机,确认 `.co2`/`.co2.bak` 被重定向。
4. 仅设置其中一个(只主存档 / 只联机存档),确认另一个不受影响。
5. `reset_achievements_on_new_game=true` 时新游戏成就重置仍工作;`cpu_affinity` 策略生效。
