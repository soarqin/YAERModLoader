# Yet Another Elden Ring Mod Loader

[中文说明](README.zhCN.md)

## Introduction
This is a mod loader for Elden Ring. It is inspred by [ModEngine](https://github.com/soulsmods/ModEngine2), and is designed to be simple and easy to use.

## Why Another Mod Loader?
- [ModEngine](https://github.com/soulsmods/ModEngine2) is great, but it is not maintained anymore.
- [me3](https://github.com/garyttierney/me3) is in development, but not so active.
- I just need a simple codebase which generates minimal overhead (less than 200KB at present).
- I may add new features eventually.

## Features
- Load dlls on game start
- Load mods like ModEngine

## Changelog
Check [CHANGELOG.md](CHANGELOG.md) for details.

## Installation
- You can download the latest release from the [release page](https://github.com/soarqin/YAERModLoader/releases), and choose one of the following methods to install the loader:
  1. Start the loader individually (recommended)
     1. Extract `YAERModLoader.exe` and `YAERModLoader.ini` to ANY folder you  (You do not need `YAERModLoader.dll` here).
     2. Modify `YAERModLoader.ini` to fit your needs.
     3. Run `YAERModLoader.exe` to start the game.
     4. This is recommended because you can start the loader only when you need it and it won't pollute your game folder.
  2. Load the loader with game automatically
     1. Extract `YAERModLoader.dll` and `YAERModLoader.ini` to the game folder (where `eldenring.exe` is, You do not need `YAERModLoader.exe` here).
     2. Rename `YAERModLoader.dll` to either `dxgi.dll`, `dinput8.dll` or `winhttp.dll`.
     3. Modify `YAERModLoader.ini` to fit your needs.
     4. Run the game [w/o EAC](https://steamcommunity.com/sharedfiles/filedetails/?id=2763986548):
        - Create a text file `steam_appid.txt` in the same folder as `eldenring.exe`, put `1245620` in it, save and close, then **start the game with eldenring.exe**. 
- You can also remove `YAERModLoader.ini` and put ModEngine2's `config_eldenring.toml` in the same folder as `YAERModLoader.dll` to use old config file as well.
- You can add parameters to `YAERModLoader.exe` to change some behaviors:
  - `-c` or `--config`: Specify the path of the config file.
  - `-p` or `--game-path`: Specify the path of the game, you can set it to full-path of `eldenring.exe`, or its `Game` folder, or even the upper-level folder(normally `ELDEN RING`).
  - `-d` or `--modengine-dll` or `--modloader-dll`: Specify the path of the replacement dll for loading. Note: `--modengine-dll` is just a compatibility option for ModEngine2.
  - `-s` or `--suspend`: Start game in suspended mode, only for debugging purpose.

## Credits
- [ModEngine](https://github.com/soulsmods/ModEngine2): The original mod loader for Souls games.
- [Detours](https://github.com/microsoft/Detours): I stripped this library to a subset of its functions, to do dll injections only.
- [minhook](https://github.com/TsudaKageyu/minhook): Used to hook functions in the game.
- [uthash](https://github.com/troydhanson/uthash): The library used to handle hash tables.
- [inih](https://github.com/benhoyt/inih): The library used to parse ini files.
- [toml-c](https://github.com/arp242/toml-c): The library used to parse toml files, for ModEngine config file compatibility.
- [wingetopt](https://github.com/alex85k/wingetopt): The library used to parse command line arguments.
- [libofdf](https://github.com/Jan200101/libofdf): The library used to parse Valve's VDF files, for locating game folder.
- [LZMA SDK](https://7-zip.org/sdk.html): The library used to embed dll as compressed data, the SDK is in public domain.
- exe LOGO from [logowik](https://logowik.com/elden-ring-logo-vector-svg-pdf-ai-eps-cdr-free-download-12207.html)
