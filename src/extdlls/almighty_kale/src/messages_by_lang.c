/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "messages.h"

/* 17 entries per language, matching ermerchant_messages_by_lang.cpp exactly.
 * Wide-string literals preserved byte-for-byte. */

static const ak_msg_entry_t ak_msg_english[] = {
    {AK_MSG_weapons, L"Weapons"},
    {AK_MSG_armor, L"Armor"},
    {AK_MSG_spells, L"Sorceries/Incantations"},
    {AK_MSG_talismans, L"Talismans"},
    {AK_MSG_ammunition, L"Arrows/Bolts"},
    {AK_MSG_ashes_of_war, L"Ashes of War"},
    {AK_MSG_consumables, L"Consumables"},
    {AK_MSG_spirit_summons, L"Spirit Ashes"},
    {AK_MSG_materials, L"Materials"},
    {AK_MSG_miscellaneous_items, L"Miscellaneous Items"},
    {AK_MSG_gestures, L"Gestures"},
    {AK_MSG_browse_inventory, L"Browse Inventory"},
    {AK_MSG_items, L"Items"},
    {AK_MSG_browse_cut_content, L"Browse Cut Content"},
    {AK_MSG_goods, L"Goods"},
    {AK_MSG_unlock, L"Unlock"},
    {AK_MSG_dlc, L"DLC Items"},
};

static const ak_msg_entry_t ak_msg_german[] = {
    {AK_MSG_weapons, L"Waffen"},
    {AK_MSG_armor, L"Rüstung"},
    {AK_MSG_spells, L"Zaubereien/Anrufungen"},
    {AK_MSG_talismans, L"Talismane"},
    {AK_MSG_ammunition, L"Pfeile/Bolzen"},
    {AK_MSG_ashes_of_war, L"Kriegsasche"},
    {AK_MSG_consumables, L"Verbrauchsgüter"},
    {AK_MSG_spirit_summons, L"Geisterasche"},
    {AK_MSG_materials, L"Materialien"},
    {AK_MSG_miscellaneous_items, L"Miscellaneous Items"},
    {AK_MSG_gestures, L"Gesten"},
    {AK_MSG_browse_inventory, L"Inventar durchsuchen"},
    {AK_MSG_items, L"Objekte"},
    {AK_MSG_browse_cut_content, L"Entfernte Inhalte durchsuchen"},
    {AK_MSG_goods, L"Goods"},
    {AK_MSG_unlock, L"Unlock"},
    {AK_MSG_dlc, L"DLC Items"},
};

static const ak_msg_entry_t ak_msg_french[] = {
    {AK_MSG_weapons, L"Armes"},
    {AK_MSG_armor, L"Armure"},
    {AK_MSG_spells, L"Tous les sorts"},
    {AK_MSG_talismans, L"Talismans"},
    {AK_MSG_ammunition, L"Flèches/Carreaux"},
    {AK_MSG_ashes_of_war, L"Cendres de guerre"},
    {AK_MSG_consumables, L"Consommables"},
    {AK_MSG_spirit_summons, L"Cendres spirituelles"},
    {AK_MSG_materials, L"Matériaux"},
    {AK_MSG_miscellaneous_items, L"Miscellaneous Items"},
    {AK_MSG_gestures, L"Émotes"},
    {AK_MSG_browse_inventory, L"Parcourir l'inventaire"},
    {AK_MSG_items, L"Objets"},
    {AK_MSG_browse_cut_content, L"Parcourir le contenu supprimé"},
    {AK_MSG_goods, L"Goods"},
    {AK_MSG_unlock, L"Unlock"},
    {AK_MSG_dlc, L"DLC Items"},
};

static const ak_msg_entry_t ak_msg_italian[] = {
    {AK_MSG_weapons, L"Armi"},
    {AK_MSG_armor, L"Armature"},
    {AK_MSG_spells, L"Stregonerie/Incantesimi"},
    {AK_MSG_talismans, L"Talismani"},
    {AK_MSG_ammunition, L"Frecce/Dardi"},
    {AK_MSG_ashes_of_war, L"Ceneri di guerra"},
    {AK_MSG_consumables, L"Consumabili"},
    {AK_MSG_spirit_summons, L"Ceneri di spirito"},
    {AK_MSG_materials, L"Materiali"},
    {AK_MSG_miscellaneous_items, L"Miscellaneous Items"},
    {AK_MSG_gestures, L"Gesti"},
    {AK_MSG_browse_inventory, L"Sfoglia l'inventario"},
    {AK_MSG_items, L"Oggetti"},
    {AK_MSG_browse_cut_content, L"Sfoglia i contenuti rimossi"},
    {AK_MSG_goods, L"Goods"},
    {AK_MSG_unlock, L"Unlock"},
    {AK_MSG_dlc, L"DLC Items"},
};

/* Japanese localization by Furisuke */
static const ak_msg_entry_t ak_msg_japanese[] = {
    {AK_MSG_weapons, L"武器"},
    {AK_MSG_armor, L"防具"},
    {AK_MSG_spells, L"魔術/祈祷"},
    {AK_MSG_talismans, L"タリスマン"},
    {AK_MSG_ammunition, L"矢/ボルト"},
    {AK_MSG_ashes_of_war, L"戦灰"},
    {AK_MSG_consumables, L"消費アイテム"},
    {AK_MSG_spirit_summons, L"遺灰"},
    {AK_MSG_materials, L"製作素材"},
    {AK_MSG_miscellaneous_items, L"その他アイテム"},
    {AK_MSG_gestures, L"ジェスチャー"},
    {AK_MSG_browse_inventory, L"インベントリを見る"},
    {AK_MSG_items, L"アイテム"},
    {AK_MSG_browse_cut_content, L"カットコンテンツを見る"},
    {AK_MSG_goods, L"アイテム"},
    {AK_MSG_unlock, L"解放"},
    {AK_MSG_dlc, L"DLCアイテム"},
};

static const ak_msg_entry_t ak_msg_koreana[] = {
    {AK_MSG_weapons, L"무기"},
    {AK_MSG_armor, L"방어구"},
    {AK_MSG_spells, L"모든 마술/기도"},
    {AK_MSG_talismans, L"탈리스만"},
    {AK_MSG_ammunition, L"화살/볼트"},
    {AK_MSG_ashes_of_war, L"전회"},
    {AK_MSG_consumables, L"소비 아이템"},
    {AK_MSG_spirit_summons, L"뼛가루 유무"},
    {AK_MSG_materials, L"소재 아이템"},
    {AK_MSG_miscellaneous_items, L"Miscellaneous Items"},
    {AK_MSG_gestures, L"제스처"},
    {AK_MSG_browse_inventory, L"인벤토리 찾아보기"},
    {AK_MSG_items, L"아이템"},
    {AK_MSG_browse_cut_content, L"컷 콘텐츠 찾아보기"},
    {AK_MSG_goods, L"Goods"},
    {AK_MSG_unlock, L"Unlock"},
    {AK_MSG_dlc, L"DLC Items"},
};

static const ak_msg_entry_t ak_msg_polish[] = {
    {AK_MSG_weapons, L"Broń"},
    {AK_MSG_armor, L"Zbroja"},
    {AK_MSG_spells, L"Czary/Inkantacje"},
    {AK_MSG_talismans, L"Talizmany"},
    {AK_MSG_ammunition, L"Strzały/bełty"},
    {AK_MSG_ashes_of_war, L"Popioły wojny"},
    {AK_MSG_consumables, L"Przedmioty jednorazowe"},
    {AK_MSG_spirit_summons, L"Prochy duchów"},
    {AK_MSG_materials, L"Materiały"},
    {AK_MSG_miscellaneous_items, L"Miscellaneous Items"},
    {AK_MSG_gestures, L"Gesty"},
    {AK_MSG_browse_inventory, L"Przeglądaj Ekwipunek"},
    {AK_MSG_items, L"Przedmioty"},
    {AK_MSG_browse_cut_content, L"Przeglądaj wyciętą zawartość"},
    {AK_MSG_goods, L"Goods"},
    {AK_MSG_unlock, L"Unlock"},
    {AK_MSG_dlc, L"DLC Items"},
};

/* Brazilian Portuguese localization by LucasGabranth */
static const ak_msg_entry_t ak_msg_brazilian[] = {
    {AK_MSG_weapons, L"Armas"},
    {AK_MSG_armor, L"Armadura"},
    {AK_MSG_spells, L"Feitiços/Encantamentos"},
    {AK_MSG_talismans, L"Talismãs"},
    {AK_MSG_ammunition, L"Flechas/Setas"},
    {AK_MSG_ashes_of_war, L"Cinzas de Guerra"},
    {AK_MSG_consumables, L"Consumíveis"},
    {AK_MSG_spirit_summons, L"Cinzas de espíritos"},
    {AK_MSG_materials, L"Materiais"},
    {AK_MSG_miscellaneous_items, L"Itens variados"},
    {AK_MSG_gestures, L"Gestos"},
    {AK_MSG_browse_inventory, L"Navegar no inventário"},
    {AK_MSG_items, L"Itens"},
    {AK_MSG_browse_cut_content, L"Navegar pelo conteúdo removido"},
    {AK_MSG_goods, L"Mercadorias"},
    {AK_MSG_unlock, L"Desbloqueios"},
    {AK_MSG_dlc, L"Itens da DLC"},
};

static const ak_msg_entry_t ak_msg_russian[] = {
    {AK_MSG_weapons, L"Оружие"},
    {AK_MSG_armor, L"Доспехи"},
    {AK_MSG_spells, L"Чары/молитвы"},
    {AK_MSG_talismans, L"Талисманы"},
    {AK_MSG_ammunition, L"Стрелы/болты"},
    {AK_MSG_ashes_of_war, L"Пепел Войны"},
    {AK_MSG_consumables, L"Расход. материалы"},
    {AK_MSG_spirit_summons, L"Прах для призыва"},
    {AK_MSG_materials, L"Материалы"},
    {AK_MSG_miscellaneous_items, L"Miscellaneous Items"},
    {AK_MSG_gestures, L"Жесты"},
    {AK_MSG_browse_inventory, L"Просмотреть инвентарь"},
    {AK_MSG_items, L"Предметы"},
    {AK_MSG_browse_cut_content, L"Browse cut content"},
    {AK_MSG_goods, L"Goods"},
    {AK_MSG_unlock, L"Unlock"},
    {AK_MSG_dlc, L"DLC Items"},
};

static const ak_msg_entry_t ak_msg_latam[] = {
    {AK_MSG_weapons, L"Armas"},
    {AK_MSG_armor, L"Armadura"},
    {AK_MSG_spells, L"Hechicerías/Encantamientos"},
    {AK_MSG_talismans, L"Talismanes"},
    {AK_MSG_ammunition, L"Flechas/Virotes"},
    {AK_MSG_ashes_of_war, L"Cenizas de guerra"},
    {AK_MSG_consumables, L"Consumibles"},
    {AK_MSG_spirit_summons, L"Cenizas de espíritus"},
    {AK_MSG_materials, L"Materiales"},
    {AK_MSG_miscellaneous_items, L"Miscellaneous Items"},
    {AK_MSG_gestures, L"Gestos"},
    {AK_MSG_browse_inventory, L"Explorar inventario"},
    {AK_MSG_items, L"Objetos"},
    {AK_MSG_browse_cut_content, L"Explorar contenidos eliminados"},
    {AK_MSG_goods, L"Goods"},
    {AK_MSG_unlock, L"Unlock"},
    {AK_MSG_dlc, L"DLC Items"},
};

static const ak_msg_entry_t ak_msg_spanish[] = {
    {AK_MSG_weapons, L"Armas"},
    {AK_MSG_armor, L"Armadura"},
    {AK_MSG_spells, L"Hechizos/encantamientos"},
    {AK_MSG_talismans, L"Talismanes"},
    {AK_MSG_ammunition, L"Flechas/saetas"},
    {AK_MSG_ashes_of_war, L"Cenizas de guerra"},
    {AK_MSG_consumables, L"Consumibles"},
    {AK_MSG_spirit_summons, L"Cenizas de espíritu"},
    {AK_MSG_materials, L"Materiales"},
    {AK_MSG_miscellaneous_items, L"Miscellaneous Items"},
    {AK_MSG_gestures, L"Gestos"},
    {AK_MSG_browse_inventory, L"Explorar inventario"},
    {AK_MSG_items, L"Objetos"},
    {AK_MSG_browse_cut_content, L"Explorar contenidos eliminados"},
    {AK_MSG_goods, L"Goods"},
    {AK_MSG_unlock, L"Unlock"},
    {AK_MSG_dlc, L"DLC Items"},
};

/* Thai localization by Perapat Chainpattanakij */
static const ak_msg_entry_t ak_msg_thai[] = {
    {AK_MSG_weapons, L"อาวุธ"},
    {AK_MSG_armor, L"เครือง​ปองกัน"},
    {AK_MSG_spells, L"คาถา/​มน​ตรา​ทังหมด"},
    {AK_MSG_talismans, L"เครืองราง"},
    {AK_MSG_ammunition, L"ลูก​ธนู/​ลูกดอก"},
    {AK_MSG_ashes_of_war, L"เถ้า​สงคราม"},
    {AK_MSG_consumables, L"ไอ​เทม​ประเภท​ใช้​แล้ว" L"​หมด​ไป"},
    {AK_MSG_spirit_summons, L"ใช้​ธุลี​หรือ​ไม่"},
    {AK_MSG_materials, L"ไอ​เท​ม​วัตถุดิบ"},
    {AK_MSG_miscellaneous_items, L"สิ่งของเบ็ดเตล็ด"},
    {AK_MSG_gestures, L"ท่าทาง"},
    {AK_MSG_browse_inventory, L"เรียกดู คลัง​ไอ​เทม"},
    {AK_MSG_items, L"รายการ"},
    {AK_MSG_browse_cut_content, L"ดูเนื้อหาที่ถูกตัดออก"},
    {AK_MSG_goods, L"สินค้า"},
    {AK_MSG_unlock, L"ปลดล็อค"},
    {AK_MSG_dlc, L"สิ่งของจาก DLC"},
};

/* Simplified Chinese localization by quantumfallout */
static const ak_msg_entry_t ak_msg_schinese[] = {
    {AK_MSG_weapons, L"武器"},
    {AK_MSG_armor, L"防具"},
    {AK_MSG_spells, L"全部的魔法、祷告"},
    {AK_MSG_talismans, L"护符"},
    {AK_MSG_ammunition, L"箭／弩箭"},
    {AK_MSG_ashes_of_war, L"战灰"},
    {AK_MSG_consumables, L"消耗道具"},
    {AK_MSG_spirit_summons, L"骨灰"},
    {AK_MSG_materials, L"材料道具"},
    {AK_MSG_miscellaneous_items, L"杂项道具"},
    {AK_MSG_gestures, L"肢体动作"},
    {AK_MSG_browse_inventory, L"浏览置物包"},
    {AK_MSG_items, L"全部道具"},
    {AK_MSG_browse_cut_content, L"浏览删减内容"},
    {AK_MSG_goods, L"其他物品"},
    {AK_MSG_unlock, L"解锁"},
    {AK_MSG_dlc, L"DLC道具"},
};

/* Traditional Chinese localization by quantumfallout */
static const ak_msg_entry_t ak_msg_tchinese[] = {
    {AK_MSG_weapons, L"武器"},
    {AK_MSG_armor, L"防具"},
    {AK_MSG_spells, L"全部的魔法、禱告"},
    {AK_MSG_talismans, L"護符"},
    {AK_MSG_ammunition, L"箭／弩箭"},
    {AK_MSG_ashes_of_war, L"戰灰"},
    {AK_MSG_consumables, L"消耗道具"},
    {AK_MSG_spirit_summons, L"骨灰"},
    {AK_MSG_materials, L"材料道具"},
    {AK_MSG_miscellaneous_items, L"雜項道具"},
    {AK_MSG_gestures, L"肢體動作"},
    {AK_MSG_browse_inventory, L"浏览置物包"},
    {AK_MSG_items, L"全部道具"},
    {AK_MSG_browse_cut_content, L"浏览刪減內容"},
    {AK_MSG_goods, L"其他物品"},
    {AK_MSG_unlock, L"解鎖"},
    {AK_MSG_dlc, L"DLC道具"},
};

static const ak_msg_entry_t ak_msg_arabic[] = {
    {AK_MSG_weapons, L"اﻷﺳﻠﺣﺔ"},
    {AK_MSG_armor, L"اﻟﻭاﻗﻲ"},
    {AK_MSG_spells, L"اﻷﺳﺣﺎر/اﻟﺗﻌﺎوﻳﺫ"},
    {AK_MSG_talismans, L"اﻟﻁﻼﺳﻡ"},
    {AK_MSG_ammunition, L"اﻷﺳﻬﻡ/اﻷﺳﻬﻡ اﻟﺻﻐﻳﺭة"},
    {AK_MSG_ashes_of_war, L"رﻣﺎد اﻟﺣﺭب"},
    {AK_MSG_consumables, L"اﻟﻣﻭاد اﻟﻘﺎﺑﻠﺔ ﻟﻼﺳﺗﻬﻼك"},
    {AK_MSG_spirit_summons, L"رﻣﺎد اﻷرواح"},
    {AK_MSG_materials, L"اﻟﻣﻭاد"},
    {AK_MSG_miscellaneous_items, L"Miscellaneous Items"},
    {AK_MSG_gestures, L"اﻹﻳﻣﺎءات"},
    {AK_MSG_browse_inventory, L"Browse Inventory"},
    {AK_MSG_items, L"أغراض"},
    {AK_MSG_browse_cut_content, L"Browse Cut Content"},
    {AK_MSG_goods, L"Goods"},
    {AK_MSG_unlock, L"Unlock"},
    {AK_MSG_dlc, L"DLC Items"},
};

const ak_lang_messages_t ak_event_text_for_talk_by_lang[] = {
    {"english",   ak_msg_english,   sizeof(ak_msg_english)   / sizeof(ak_msg_entry_t)},
    {"german",    ak_msg_german,    sizeof(ak_msg_german)    / sizeof(ak_msg_entry_t)},
    {"french",    ak_msg_french,    sizeof(ak_msg_french)    / sizeof(ak_msg_entry_t)},
    {"italian",   ak_msg_italian,   sizeof(ak_msg_italian)   / sizeof(ak_msg_entry_t)},
    {"japanese",  ak_msg_japanese,  sizeof(ak_msg_japanese)  / sizeof(ak_msg_entry_t)},
    {"koreana",   ak_msg_koreana,   sizeof(ak_msg_koreana)   / sizeof(ak_msg_entry_t)},
    {"polish",    ak_msg_polish,    sizeof(ak_msg_polish)    / sizeof(ak_msg_entry_t)},
    {"brazilian", ak_msg_brazilian, sizeof(ak_msg_brazilian) / sizeof(ak_msg_entry_t)},
    {"russian",   ak_msg_russian,   sizeof(ak_msg_russian)   / sizeof(ak_msg_entry_t)},
    {"latam",     ak_msg_latam,     sizeof(ak_msg_latam)     / sizeof(ak_msg_entry_t)},
    {"spanish",   ak_msg_spanish,   sizeof(ak_msg_spanish)   / sizeof(ak_msg_entry_t)},
    {"thai",      ak_msg_thai,      sizeof(ak_msg_thai)      / sizeof(ak_msg_entry_t)},
    {"schinese",  ak_msg_schinese,  sizeof(ak_msg_schinese)  / sizeof(ak_msg_entry_t)},
    {"tchinese",  ak_msg_tchinese,  sizeof(ak_msg_tchinese)  / sizeof(ak_msg_entry_t)},
    {"arabic",    ak_msg_arabic,    sizeof(ak_msg_arabic)    / sizeof(ak_msg_entry_t)},
};

const size_t ak_event_text_for_talk_by_lang_count =
    sizeof(ak_event_text_for_talk_by_lang) / sizeof(ak_lang_messages_t);