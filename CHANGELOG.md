#### Unreleased
* Added complete English and Chinese `YAERModLoader.ini` templates and documented all loader options, game sections, and launcher arguments. Distribution packages now include both templates and both README files.
* Added launcher and adapter coverage for Sekiro, plus game-target selection through `--launch-target`; Sekiro still requires field validation for some capabilities, while Dark Souls III remains experimental and does not install game-specific hooks.
* Added the frozen VFS index, domain-specific lookup caches, Dantelion asset routing, BootBoost caching, explicit writable mappings, and long-path handling.
* Avoided ordinary VFS queries when no mods are loaded and made VFS cache hits return stable values without string allocations.
* Removed the built-in Elden Ring visual/input tweaks (`remove_chromatic_aberration`, `remove_vignette`, and `disable_mouse_camera_control`) and removed all project-owned extension DLLs from `src/extdlls` and release packages.

#### 0.6.1
* Fixed possible crash

#### 0.6.0
* Added new external dll: `almighty_kale.dll` — a 1:1 C port of the [Glorious Merchant](https://github.com/ThomasJClark/elden-ring-glorious-merchant) mod (MIT). It patches Kalé's dialogue to add "Browse Inventory" / "Browse Cut Content" submenus that open 22 free shops covering every obtainable item in the game (including DLC and cut content), unlocks all gestures, makes Kalé always alive, zeroes sell values while the shop is open, and keeps key items out of the storage box. Configurable via `almighty_kale.ini` (`auto_upgrade_weapons`).
* Extended `er_param` (API bumped to v2; existing field offsets preserved, new accessors appended): added `from/` C struct headers (`ezstate.h`, `talk_commands.h`, `messages.h`, `game_data.h`) matching the merchant's reverse-engineered layouts, and runtime pointer accessors for `MsgRepositoryImp`, `GameDataMan`, `SoloParamRepositoryImp::LookupShopMenu`/`LookupShopLineup`, `MsgRepositoryImp::LookupEntry`, `EzState::state::Enter`, `CSFD4VirtualMemoryFlag::GetEventFlag`, `GetSellValue`, `GetMaxRepositoryNum`, and `OpenRegularShop` (scanned via signature patterns).
* `src/steam` now also exposes `ISteamApps::GetCurrentGameLanguage` (vtable index 4) via `steam_apps()` / `isteam_apps_get_current_game_language()`, with a `SteamAPI_SteamApps_v008` → `v007` fallback. Used by `almighty_kale` to pick the localized menu text (14 languages; English fallback).
* Fixed `LocalReAlloc` shrinking the `extdlls`/`mods`/`er_param` observers arrays in place: without `LMEM_MOVEABLE`, a fixed block can only grow in place and the realloc silently returns NULL once the heap can't extend it, dropping the entry that triggered the grow (notably the 9th item, since capacity grows 8 -> 16). Extension DLLs/mods listed past the 8th would intermittently go missing from the load list.
* **Breaking (ext API re-anchored to V1):** Moved the Elden Ring param interface out of the main loader into a standalone `er_param.dll` provider. The main mod loader is now a generic loader with no param/wstring/pointers coupling.
  * `modloader_ext_api_t` no longer exposes `er_param_find_table`/`er_wstring_impl_str`; `modloader_ext_def_t` no longer has the `on_param_initialized` callback (the param-ready notification is now decentralized).
  * Param consumers (`itemlot_rate`, `autoloot`) obtain the param API at runtime via `er_param_api_get()` (exported by `er_param.dll`) and register `on_param_loaded` observers; they must list `er_param` before themselves in the `[dlls]` ini section (load-order dependency; no build-time runtime dependency system).
  * `er_param.dll` ships in the release package under `dll/` with its own `er_param.ini`; the `world_map_cursor_speed` setting moved there from `YAERModLoader.ini`'s `[elden_ring]` section.
  * Removed the `src/eldenring/` static library entirely; the `map_archive_path` hook inlines the wstring SSO logic locally so the loader no longer links it.

#### 0.5.1
* Fixed no sound when a mod overrides Wwise audio files (`.wem`/`.bnk`): override files on disk use READ mode instead of READ_EBL
* Updated CREDITS: klib replaces uthash

#### 0.5.0
* Added new option: `disable_mouse_camera_control`
* Added new external dll: `no_dup_loot.dll` — prevents duplicate loot drops
* Fixed use-after-free in `CopyFile_hooked`
* Fixed inverted realloc condition and NULL deref in `itemlot_rate`
* Fixed memory leak and signed char OOB in sig_scan/sig_build
* Fixed race condition: init `image_base` before spawning threads
* Fixed `config_load` dropping absolute file path from env var
* Fixed filecache negative caching never working
* Replaced uthash with klib khash across all hash table usages
* Added smoke tests via CTest

#### 0.4.1
* Fixed a crash caused by save filename changing.

#### 0.4.0
* Added new option: `world_map_cursor_speed`
* Added new options: `replace_save_filename` and `replace_seamless_coop_save_filename`
* Added 2 individual external dlls (uncomment in `YAERModLoader.ini` to enable them)
  * `autoloot.dll`: Auto-loot materials and player corpse runes
  * `itemlot_rate.dll`: Change item drop rate, modify `itemlot_rate.ini` to satisfy your use

#### 0.3.3
* Fixed broken '-p' option

#### 0.3.2
* Fixed mod loading path issue (#2)
* Fixed a critical string matching issue for mod file paths

#### 0.3.1
* Fixed a crash issue

#### 0.3.0
* Added new options: `reset_achievements_on_new_game` and `enable_ime`
* Added compatibility with ModEngine2's mod loading mechanism, which makes SeamlessCoop mod working now (#1)

#### 0.2.0
+ Added following config entries:
    - cpu_affinity
    - skip_intro
    - remove_chromatic_aberration
    - remove_vignette
+ Do not hook certain functions when no mod is added, to improve performance during loadings.

#### 0.1.0
* Initial release
