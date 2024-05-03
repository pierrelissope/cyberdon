/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** fight loading
*/

#include "dict.h"
#include "fight_macros.h"
#include "fight_entity.h"
#include "struct.h"
#include "init_fight_arena.h"
#include "init_fighters.h"
#include "view.h"

#include <SFML/Config.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <stdlib.h>

static bool load_arena(fight_t *fight)
{
    char *concat_path = my_strcat(2, ARENA_FOLDERS[fight->arena], "background.png");

    dict_insert(&fight->text_dict, BACKGROUND_TEXT,
        sfTexture_createFromFile(concat_path, NULL));
    free(concat_path);
    concat_path = my_strcat(2, ARENA_FOLDERS[fight->arena], "forground.png");
    dict_insert(&fight->text_dict, FORGROUND_TEXT,
        sfTexture_createFromFile(concat_path, NULL));
    free(concat_path);
    fight->background = sfRectangleShape_create();
    fight->foreground = sfRectangleShape_create();
    sfRectangleShape_setTexture(fight->background, dict_get(fight->text_dict, BACKGROUND_TEXT), sfFalse);
    sfRectangleShape_setTexture(fight->foreground, dict_get(fight->text_dict, FORGROUND_TEXT), sfFalse);
    sfRectangleShape_setSize(fight->background, (sfVector2f) {BACKGROUND_REC.height, BACKGROUND_REC.width});
    sfRectangleShape_setSize(fight->foreground, (sfVector2f) {BACKGROUND_REC.height, BACKGROUND_REC.width});
    return false;
}

static bool load_text(fight_t *fight)
{
    char *concat_path = NULL;
    int moves_counter = 0;

    for (int i = PLAYER_IDLE_TEXT; i < PLAYER_TEXTURES_END; i++) {
        concat_path = my_strcat(2, FIGHTER_FOLDERS[PLAYER_FIGHTER],
            MOVES_INIT[moves_counter].text_file);
        dict_insert(&(fight->text_dict), i, sfTexture_createFromFile(concat_path, NULL));
        free(concat_path);
        moves_counter++;
    }
    moves_counter = 0;
    for (int i = NPC_IDLE_TEXT; i < NPC_TEXTURES_END; i++) {
        concat_path = my_strcat(2, FIGHTER_FOLDERS[NPC1], // replace with correspond fighter
            MOVES_INIT[moves_counter].text_file);
        dict_insert(&(fight->text_dict), i, sfTexture_createFromFile(concat_path, NULL));
        free(concat_path);
        moves_counter++;
    }
    return false;
}

static bool load_fighters(fight_t *fight)
{
    fight->player = init_fighter_entity(fight->player_stats, fight);
    fight->npc = init_fighter_entity(fight->npc_stats, fight);
    return false;
}

fight_t *load_fight(game_t *game, physical_entity_t *player,
     physical_entity_t *npc, arenas_t arena)
{
    fight_t *fight = calloc(1, sizeof(fight_t));

    if (fight == NULL)
        return NULL;
    fight->debug_mode = true;
    fight->arena = arena;
    fight->npc_stats = npc;
    fight->player_stats = player;
    fight->view = init_fight_view();
    sfRenderWindow_setView(game->window, fight->view);
    sfRenderWindow_setKeyRepeatEnabled(game->window, sfFalse);
    load_text(fight);
    load_arena(fight);
    load_fighters(fight);
    return fight;
}
