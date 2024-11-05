## 介绍
这是一个适用于《艾尔登法环》的模组加载器。它受到了[ModEngine](https://github.com/soulsmods/ModEngine2)启发，旨在设计上简单易用。

[README in English](README.md)

## 为什么重造轮子？
- [ModEngine](https://github.com/soulsmods/ModEngine2)很棒，但已经不再维护。
- [me3](https://github.com/garyttierney/me3)正在开发中，但活跃度不高。
- 我需要一个简单的代码库，生成的可执行文件尽可能小（目前不到200KB）。
- 我可能会时不时突发灵感添加新功能。

## 特性
- 在游戏启动时加载dll
- 类似ModEngine的模组加载

## 安装
- 你可以从[发布页面](https://github.com/soarqin/YAERModLoader/releases)下载最新版本，然后选择以下方法之一安装加载器：
    1. 单独启动加载器（推荐）
        1. 将zip文件解压到任意你喜欢的文件夹。
        2. 修改`YAERModLoader.ini`以满足你的需求。
        3. 运行`YAERModLoader.exe`启动游戏。
        4. 这是推荐的方式，因为你可以在需要时单独启动加载器，而且不会污染游戏文件夹。
    2. 自动启动加载器
        1. 将`YAERModLoader.dll`和`YAERModLoader.ini`解压到游戏文件夹(即`eldenring.exe`所在的文件夹)。
        2. 将`YAERModLoader.dll`重命名为`dxgi.dll`、`dinput8.dll`或`winhttp.dll`中的任何一个。
        3. 修改`YAERModLoader.ini`以适应你的需求。
        4. 以不加载小蓝熊方式启动游戏：
            - 在`eldenring.exe`所在目录创建一个文本文件`steam_appid.txt`，在里面写上数字`1245620`，保存并关闭，然后**用 eldenring.exe 启动游戏**。
- 你也可以删除`YAERModLoader.ini`，并将ModEngine2的`config_eldenring.toml`放在`YAERModLoader.dll`所在的文件夹，以使用旧的配置文件。
- 你可以给`YAERModLoader.exe`添加参数以改变一些启动行为：
    - `-c`或`--config`：指定配置文件的路径。
    - `-p`或`--game-path`：指定游戏的路径，可以设置为`eldenring.exe`的完整路径，或其所在`Game`文件夹，甚至是上一级文件夹（通常是`ELDEN RING`）。
    - `-d`或`--modengine-dll`或`--modloader-dll`：指定用于加载的替换dll的路径。注意：`--modengine-dll`只是为了兼容ModEngine2。
    - `-s`或`--suspend`：以挂起模式启动游戏，仅用于调试目的。

## 鸣谢
- [ModEngine](https://github.com/soulsmods/ModEngine2): 魂系游戏的原始模组加载器。
- [Detours](https://github.com/microsoft/Detours): 我只保留了这个库的一部分功能，用于dll注入。
- [minhook](https://github.com/TsudaKageyu/minhook): 用于在游戏中挂钩函数。
- [uthash](https://github.com/troydhanson/uthash): 用于处理哈希表的库。
- [inih](https://github.com/benhoyt/inih): 用于解析ini文件的库。
- [toml-c](https://github.com/arp242/toml-c): 用于解析toml文件的库，以兼容ModEngine的配置文件。
- [wingetopt](https://github.com/alex85k/wingetopt): 用于解析命令行参数的库。
- [libofdf](https://github.com/Jan200101/libofdf): 用于解析Valve的VDF文件的库，用于定位游戏所在文件夹。
- exe LOGO来自[logowik](https://logowik.com/elden-ring-logo-vector-svg-pdf-ai-eps-cdr-free-download-12207.html)
