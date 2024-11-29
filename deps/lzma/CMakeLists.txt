add_project(lzma STATIC
    7zTypes.h 7zWindows.h
    Alloc.c Alloc.h
    Compiler.h
    CpuArch.c CpuArch.h
    LzmaDec.c LzmaDec.h
    LzmaEnc.c LzmaEnc.h
    LzFind.c LzFind.h
    LzFindMt.c LzFindMt.h
    LzFindOpt.c
    LzHash.h
    Precomp.h
    Threads.c Threads.h
    LANGUAGES C FOLDER libs)
target_include_directories(${PROJECT_NAME} PUBLIC .)
