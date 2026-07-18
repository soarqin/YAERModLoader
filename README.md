# Yet Another Elden Ring Mod Loader

[中文说明](README.zhCN.md)

YAERModLoader is a Windows mod loader for FromSoftware games. It provides a
standalone launcher, proxy DLL support, ordered loose-file overrides, and
external DLL loading.

## Supported games

| Game | Launcher target | Status |
| --- | --- | --- |
| Elden Ring | `eldenring` | Stable |
| Sekiro: Shadows Die Twice | `sekiro` | Stable adapter; field validation is still required for some capabilities |
| Dark Souls III | `darksouls3` | Experimental registry entry; game-specific hooks are not enabled yet |

Elden Ring remains the primary target. The `sekiro` target is selected with
`--launch-target sekiro`. Without an explicit target, the launcher starts
Elden Ring.

## Installation

### Standalone launcher

1. Extract `YAERModLoader.exe`, `YAERModLoader.dll`, and `YAERModLoader.ini`
   into a directory of choice.
2. Edit `YAERModLoader.ini` and enable the required DLLs or mods.
3. Run `YAERModLoader.exe`.

The launcher finds the game in its current directory, from an explicit path,
or through the Steam library. It starts the game suspended, injects the loader
DLL, and resumes the game unless `--suspend` is used.

### Proxy DLL

1. Put `YAERModLoader.dll` and `YAERModLoader.ini` in the game directory.
2. Rename `YAERModLoader.dll` to `dxgi.dll`, `dinput8.dll`, or `winhttp.dll`.
3. Start the game without Easy Anti-Cheat.

For a direct `eldenring.exe` launch, create `steam_appid.txt` beside the game
executable and put `1245620` in it. The corresponding Steam App ID is selected
automatically for other launcher targets.

## Configuration

The complete template is `src/YAERModLoader.ini` and is copied into release
packages as `YAERModLoader.ini`. Boolean values accept `true`, `yes`, `on`, or
`1`; other values are false.

### Global options

These options are outside a section:

| Option | Default | Description |
| --- | --- | --- |
| `debug` | `0` | Open a debug console. |
| `log_level` | `info` | Minimum log level: `trace`, `debug`, `info`, `warn`, `error`, or `off`. |
| `cpu_affinity` | `0` | Select the Elden Ring process CPU affinity strategy. Values `1`–`4` select the documented core subsets. |
| `reset_achievements_on_new_game` | `0` | Reset Elden Ring achievements when a new game starts. |
| `enable_ime` | `0` | Keep IME enabled for mods that need CJK text input. |

### Game sections

The section must match the current executable: `[elden_ring]` for Elden Ring,
`[sekiro]` for Sekiro, or `[darksouls3]` for the experimental registry target.
Dark Souls III currently stops before installing game-specific hooks.

| Option | Elden Ring | Sekiro | Dark Souls III | Description |
| --- | --- | --- | --- | --- |
| `skip_intro` | Yes | Yes | No hooks | Skip the intro logo. |
| `remove_chromatic_aberration` | Yes | No | No hooks | Remove chromatic aberration. |
| `remove_vignette` | Yes | No | No hooks | Remove the vignette effect. |
| `disable_mouse_camera_control` | Yes | No | No hooks | Disable mouse camera control. |
| `prevent_regulation_save_write` | Yes | Yes | No hooks | Prevent raw modded or oversized regulation data from being written to saves. |
| `patch_mem` | Yes | Yes | Partial | Use the mimalloc-backed Dantelion allocator. |
| `patch_mem_heap_size` | Yes | Yes | Partial | Dedicated heap size in MB; `0` uses the default heap size. |
| `patch_mem_hook_cs_graphics` | Yes | No | No hooks | Hook `CSGraphicsImp` as part of `patch_mem`. |
| `boot_boost` | Yes | Yes | No hooks | Cache decrypted BHD headers to reduce archive startup time. |
| `replace_save_filename` | Yes | Yes | No hooks | Replace the save filename; a leading dot replaces only the extension. |
| `replace_seamless_coop_save_filename` | Yes | No | No hooks | Replace the Seamless Co-op `.co2` filename. |

Options marked `No hooks` are still shown in the template for consistency;
the current game adapter does not install the corresponding functionality.

### DLLs and mods

The `[dlls]` section loads external DLLs at game startup. Paths can be relative
to the configuration file or absolute. `er_param` must be listed before
`almighty_kale`, `itemlot_rate`, `autoloot`, or another extension that consumes
the param API. Project-owned Elden Ring extensions are skipped for non-Elden
Ring processes when applicable.

The `[mods]` section lists directories containing loose-file overrides. Paths
can be relative to the configuration file or absolute. When multiple mods
contain the same file, the later declaration overrides the earlier one.

Project extensions may have their own configuration files:

- `dll/er_param.ini`: `world_map_cursor_speed`, a multiplier from `0.5` to `10.0`; `1.0` is the default.
- `dll/almighty_kale.ini`: `auto_upgrade_weapons`, which defaults to `true` and controls the upgrade level shown by the merchant shops.
- `dll/itemlot_rate.ini`: `include_weapons`, `include_arrows`, `include_armors`, `include_goods`, and the `[alter_count]` entries. Each alter-count entry uses `item_id=drop|loot|all,count`.

### ModEngine2 TOML compatibility

If `YAERModLoader.ini` is absent, the loader looks for the game-specific
ModEngine2 file: `config_eldenring.toml`, `config_sekiro.toml`, or
`config_darksouls3.toml`. The `-c` launcher option or `MODLOADER_CONFIG`
environment variable can select another configuration path.

## Launcher options

```text
-t, --launch-target <game>  Select eldenring, sekiro, or darksouls3.
-p, --game-path <path>      Game executable or game directory.
-c, --config <path>         Configuration file or directory.
-d, --modloader-dll <path> Loader DLL to inject.
    --modengine-dll <path> Compatibility alias for --modloader-dll.
-s, --suspend               Leave the game suspended after injection.
```

## Changelog

See [CHANGELOG.md](CHANGELOG.md).

## Credits

- [ModEngine](https://github.com/soulsmods/ModEngine2): original Souls mod loader.
- [minhook](https://github.com/TsudaKageyu/minhook): function hooking.
- [klib](https://github.com/attractivechaos/klib): hash tables.
- [inih](https://github.com/benhoyt/inih): INI parsing.
- [toml-c](https://github.com/arp242/toml-c): ModEngine2 TOML compatibility.
- [wingetopt](https://github.com/alex85k/wingetopt): command-line parsing.
- [mimalloc](https://github.com/microsoft/mimalloc): loader allocator.
- [libofdf](https://github.com/Jan200101/libofdf): Steam library discovery.
- [LZMA SDK](https://7-zip.org/sdk.html): public-domain compression SDK.
- [Glorious Merchant Mod](https://github.com/ThomasJClark/elden-ring-glorious-merchant): `almighty_kale` behavior reference.
