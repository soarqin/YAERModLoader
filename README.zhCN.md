# Yet Another Elden Ring Mod Loader

[README in English](README.md)

YAERModLoader 是面向 Windows 的 FromSoftware 游戏模组加载器，提供独立
启动器、代理 DLL、按声明顺序生效的散文件覆盖，以及兼容 ModEngine 的外部
DLL 加载。

## 支持的游戏

| 游戏 | 启动目标 | 状态 |
| --- | --- | --- |
| Elden Ring | `eldenring` | 稳定支持 |
| Sekiro: Shadows Die Twice | `sekiro` | 稳定适配器，部分能力仍需现场验证 |
| Dark Souls III | `darksouls3` | 实验性适配器，不包含 Arxan 中和 |

Elden Ring 仍是主要目标。使用 `--launch-target sekiro` 选择 Sekiro；未指定
启动目标时默认启动 Elden Ring。

## 安装

### 独立启动器

1. 将 `YAERModLoader.exe`、`YAERModLoader.dll` 和 `YAERModLoader.ini` 解压到任意目录。
2. 修改 `YAERModLoader.ini`，启用所需的外部 DLL 或模组。
3. 运行 `YAERModLoader.exe`。

启动器会依次尝试当前目录、显式路径和 Steam 库定位游戏。启动游戏后，启动器
会先保持主进程挂起，注入加载器 DLL；除非指定 `--suspend`，否则随后恢复游戏。

### 代理 DLL

1. 将 `YAERModLoader.dll` 和 `YAERModLoader.ini` 放入游戏目录。
2. 将 `YAERModLoader.dll` 重命名为 `dxgi.dll`、`dinput8.dll` 或 `winhttp.dll`。
3. 在不加载 Easy Anti-Cheat 的情况下启动游戏。

直接运行 `eldenring.exe` 时，可在游戏可执行文件旁创建 `steam_appid.txt`，写入
`1245620`。其他启动目标会自动使用对应的 Steam App ID。

## 配置

完整模板位于 `src/YAERModLoader.ini`，发布包中的文件名为
`YAERModLoader.ini`。布尔值支持 `true`、`yes`、`on` 和 `1`；其他值均视为 false。

### 全局选项

以下选项位于所有 section 之外：

| 选项 | 默认值 | 说明 |
| --- | --- | --- |
| `debug` | `0` | 打开调试控制台。 |
| `log_level` | `info` | 最低日志级别：`trace`、`debug`、`info`、`warn`、`error` 或 `off`。 |
| `cpu_affinity` | `0` | 选择 Elden Ring 进程的 CPU 亲和性策略。`1`–`4` 对应模板中的核心子集。 |
| `reset_achievements_on_new_game` | `0` | Elden Ring 开始新游戏时重置成就。 |
| `enable_ime` | `0` | 为需要 CJK 文本输入的模组保持 IME 启用。 |

### 游戏 section

section 名称必须与当前可执行文件匹配：Elden Ring 使用 `[elden_ring]`，Sekiro
使用 `[sekiro]`，Dark Souls III 实验性适配器使用 `[darksouls3]`。Dark Souls III
会安装共享 Host 能力，但不包含 dearxan 或等效 Arxan 中和；游戏可能阻止或恢复
部分 Hook，实际状态必须以日志为准。

| 选项 | Elden Ring | Sekiro | Dark Souls III | 说明 |
| --- | --- | --- | --- | --- |
| `skip_intro` | 支持 | 支持 | 实验性 | 跳过开场 Logo。 |
| `prevent_regulation_save_write` | 支持 | 支持 | 实验性 | 阻止原始、修改后或过大的 regulation 数据写入存档。 |
| `patch_mem` | 支持 | 支持 | 实验性 | 使用基于 mimalloc 的 Dantelion 分配器。 |
| `patch_mem_heap_size` | 支持 | 支持 | 实验性 | 专用堆大小，单位为 MB；`0` 使用默认大小。 |
| `patch_mem_hook_cs_graphics` | 支持 | 不支持 | 不支持 | 作为 `patch_mem` 的一部分 Hook `CSGraphicsImp`。 |
| `boot_boost` | 支持 | 支持 | 实验性 | 缓存解密后的 BHD 标头，减少归档启动时间。 |
| `replace_save_filename` | 支持 | 支持 | 实验性 | 替换存档文件名；以点号开头时只替换扩展名。 |
| `replace_seamless_coop_save_filename` | 支持 | 不支持 | 不支持 | 替换 Seamless Co-op 的 `.co2` 存档文件名。 |

Dark Souls III 能力在完成目标版本签名验证和至少一次实际 Hook 安装验证前均保持实验性。

### DLL 与模组

`[dlls]` section 用于在游戏启动时加载外部 DLL。路径可以是相对于配置文件的路径，
也可以是绝对路径。项目自带的扩展 DLL 已不再随此仓库发布。

`[mods]` section 用于声明包含散文件覆盖的目录。路径可以是相对路径或绝对路径；多个
模组包含同名文件时，后声明的模组覆盖先声明的模组。

### ModEngine2 TOML 兼容

未找到 `YAERModLoader.ini` 时，加载器会查找对应游戏的 ModEngine2 文件：
`config_eldenring.toml`、`config_sekiro.toml` 或 `config_darksouls3.toml`。
启动器的 `-c` 选项或 `MODLOADER_CONFIG` 环境变量可指定其他配置路径。

## 启动器选项

```text
-t, --launch-target <game>  选择 eldenring、sekiro 或 darksouls3。
-p, --game-path <path>      指定游戏可执行文件或游戏目录。
-c, --config <path>         指定配置文件或配置目录。
-d, --modloader-dll <path> 指定要注入的加载器 DLL。
    --modengine-dll <path> --modloader-dll 的兼容别名。
-s, --suspend               注入后保持游戏挂起。
```

## 更新记录

详见 [CHANGELOG.md](CHANGELOG.md)。

## 鸣谢

- [ModEngine](https://github.com/soulsmods/ModEngine2)：原始 Souls 游戏模组加载器。
- [minhook](https://github.com/TsudaKageyu/minhook)：函数 Hook。
- [klib](https://github.com/attractivechaos/klib)：哈希表。
- [inih](https://github.com/benhoyt/inih)：INI 解析。
- [toml-c](https://github.com/arp242/toml-c)：ModEngine2 TOML 兼容。
- [wingetopt](https://github.com/alex85k/wingetopt)：命令行解析。
- [mimalloc](https://github.com/microsoft/mimalloc)：加载器分配器。
- [libofdf](https://github.com/Jan200101/libofdf)：Steam 库定位。
- [LZMA SDK](https://7-zip.org/sdk.html)：公有领域压缩 SDK。
