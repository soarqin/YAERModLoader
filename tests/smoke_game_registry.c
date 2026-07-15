#include <stdio.h>

#include "test_common.h"
#include "game/game.h"

int main(void) {
    const ml_game_descriptor_t *game;

    game = ml_game_by_key(L"er");
    EXPECT_NOT_NULL(game);
    EXPECT_EQ(game->id, ML_GAME_ELDEN_RING);
    EXPECT_EQ(game->steam_app_id, 1245620);
    EXPECT_STREQ_W(game->exe_relpaths[0], L"Game\\eldenring.exe");
    EXPECT_EQ(game->runtime_ready_trigger, ML_RUNTIME_READY_STEAM_API_INIT);
    EXPECT_EQ(game->logo_strategy, ML_LOGO_STRATEGY_FD4);

    game = ml_game_by_key(L"sekiro");
    EXPECT_NOT_NULL(game);
    EXPECT_EQ(game->stl_abi, ML_STL_ABI_MSVC2015);
    EXPECT_EQ(game->ebl_bhd_holder_offset, 0xB0);
    EXPECT_EQ(game->runtime_ready_trigger, ML_RUNTIME_READY_UNSUPPORTED);
    EXPECT_EQ(game->logo_strategy, ML_LOGO_STRATEGY_SPRJ);

    game = ml_game_by_key(L"ds3");
    EXPECT_NOT_NULL(game);
    EXPECT_EQ(game->support_level, ML_SUPPORT_EXPERIMENTAL);
    EXPECT_EQ(game->stl_abi, ML_STL_ABI_MSVC2012);
    EXPECT_EQ(game->ebl_bhd_holder_offset, 0xC0);
    EXPECT_EQ(game->runtime_ready_trigger, ML_RUNTIME_READY_UNSUPPORTED);
    EXPECT_EQ(game->logo_strategy, ML_LOGO_STRATEGY_SPRJ);

    EXPECT_EQ(ml_game_by_exe_path(L"C:\\Games\\Sekiro\\sekiro.exe")->id, ML_GAME_SEKIRO);
    EXPECT_NULL(ml_game_by_key(L"unknown"));
    EXPECT_NULL(ml_game_by_exe_path(L"C:\\Games\\game.exe"));

    printf("smoke_game_registry: all tests passed\n");
    return 0;
}
