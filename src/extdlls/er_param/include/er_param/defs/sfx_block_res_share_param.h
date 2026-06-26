#pragma once

typedef struct er_sfx_block_res_share_param_s {
    /* ブロックSfxリソース参照先マップ番号
     *   リソースを参照するマップ番号。マップ番号を数値化した値を設定します。(m12_34_56_78→12345678)
     * Shared Resource Block - Map UID
     *   The map number that references the resource. Set the numerical value of the map number. (m12_34_56_78  12345678) */
    unsigned int shareBlockRsMapUidVal;
} er_sfx_block_res_share_param_t;
