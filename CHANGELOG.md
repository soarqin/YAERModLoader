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
