if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message( FATAL_ERROR "This subset of minhook only supports x64 targets")
endif()

set(SOURCES_MINHOOK 
  "buffer.c"
  "hook.c"
  "trampoline.c"
)
set(SOURCES_HDE "hde64.c")

add_project(minhook STATIC ${SOURCES_MINHOOK} ${SOURCES_HDE} LANGUAGES C FOLDER extlibs)

target_include_directories(minhook PUBLIC .)
