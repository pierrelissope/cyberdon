/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** loading of text
*/

#include "basics.h"
#include "dict.h"
#include "fight_entity.h"
#include "fight_macros.h"
#include "fight.h"
#include "init_ui.h"
#include "struct.h"
#include "init_fighters.h"

static bool load_fighter_text(fight_t *fight,
    fighter_init_t const *init_info, bool player)
{
    char *concat_path = NULL;
    int moves_counter = 0;
    fight_textures_t text_beg = NPC_IDLE_TEXT;
    fight_textures_t text_end = NPC_TEXTURES_END;

    if (player) {
        text_beg = PLAYER_IDLE_TEXT;
        text_end = PLAYER_TEXTURES_END;
    }
    for (fight_textures_t i = text_beg;
        i < text_end; ++i) {
        concat_path = my_strcat(2, init_info->fighter_folder,
            MOVES_INIT[moves_counter].text_file);
        dict_insert(&(fight->text_dict), i,
            sfTexture_createFromFile(concat_path, NULL));
        free(concat_path);
        moves_counter++;
    }
    return false;
}

static bool load_ui_text(fight_t *fight)
{
    char *concat_path = my_strcat(2,
        FIGHTER_INIT[fight->player_stats->fighter_skin].fighter_folder,
        "portrait.png");

    dict_insert(&fight->text_dict, PLAYER_PORTRAIT_TEXT,
        sfTexture_createFromFile(concat_path, &PLAYER_PORTRAIT));
    free(concat_path);
    concat_path = my_strcat(2,
        FIGHTER_INIT[get_npc_skin(fight->npc_stats)].fighter_folder,
        "portrait.png");
    dict_insert(&fight->text_dict, NPC_PORTRAIT_TEXT,
        sfTexture_createFromFile(concat_path, &NPC_PORTRAIT));
    free(concat_path);
    dict_insert(&fight->text_dict, LOSE_TEXT,
        sfTexture_createFromFile("assets/spritesheets/fight/lose.png",
        &END_TEXT_TEXT));
    dict_insert(&fight->text_dict, WIN_TEXT,
        sfTexture_createFromFile("assets/spritesheets/fight/win.png",
        &END_TEXT_TEXT));
    return false;
}

bool load_text(fight_t *fight)
{
    if (load_fighter_text(fight,
        &(FIGHTER_INIT[fight->player_stats->fighter_skin]), true))
        return true;
    if (load_fighter_text(fight,
        &(FIGHTER_INIT[get_npc_skin(fight->npc_stats)]), false))
        return true;
    if (load_ui_text(fight))
        return true;
    return false;
}
