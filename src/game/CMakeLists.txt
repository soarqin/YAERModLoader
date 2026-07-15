add_project(game_registry STATIC
    game.h
    context.c
    registry.c
    FOLDER libs
)

target_link_libraries(game_registry PRIVATE shlwapi)
