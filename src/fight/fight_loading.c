/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** fight loading
*/

#include "dict.h"
#include "fight_entity.h"
#include "fight_macros.h"
#include "fight.h"
#include "struct.h"
#include "init_fight_arena.h"
#include "init_fighters.h"
#include "view.h"

#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <stdlib.h>

static bool init_rects(fight_t *fight)
{
    fight->background = sfRectangleShape_create();
    if (fight->background == NULL)
        return true;
    fight->foreground = sfRectangleShape_create();
    if (fight->foreground == NULL)
        return true;
    sfRectangleShape_setTexture(fight->background,
        dict_get(fight->text_dict, BACKGROUND_TEXT), sfFalse);
    sfRectangleShape_setTexture(fight->foreground,
        dict_get(fight->text_dict, FORGROUND_TEXT), sfFalse);
    sfRectangleShape_setSize(fight->background,
        (sfVector2f) {BACKGROUND_REC.height, BACKGROUND_REC.width});
    sfRectangleShape_setSize(fight->foreground,
        (sfVector2f) {BACKGROUND_REC.height, BACKGROUND_REC.width});
    return false;
}

static bool load_arena(fight_t *fight)
{
    char *concat_path = my_strcat(2,
        ARENA_FOLDERS[fight->arena], "background.png");

    if (concat_path == NULL)
        return true;
    dict_insert(&fight->text_dict, BACKGROUND_TEXT,
        sfTexture_createFromFile(concat_path, NULL));
    free(concat_path);
    concat_path = my_strcat(2, ARENA_FOLDERS[fight->arena], "forground.png");
    if (concat_path == NULL)
        return true;
    dict_insert(&fight->text_dict, FORGROUND_TEXT,
        sfTexture_createFromFile(concat_path, NULL));
    free(concat_path);
    return init_rects(fight);
}

static bool load_fighter_text(fight_t *fight, fighter_init_t const *init_info)
{
    char *concat_path = NULL;
    int moves_counter = 0;

    for (fight_textures_t i = init_info->text_beg;
        i < init_info->text_end; ++i) {
        concat_path = my_strcat(2, init_info->fighter_folder,
            MOVES_INIT[moves_counter].text_file);
        dict_insert(&(fight->text_dict), i,
            sfTexture_createFromFile(concat_path, NULL));
        free(concat_path);
        moves_counter++;
    }
    return false;
}

// REPLACE [NPC1] with npc's skin
static bool load_text(fight_t *fight)
{
    if (load_fighter_text(fight, &(FIGHTER_INIT[PLAYER_FIGHTER])))
        return true;
    if (load_fighter_text(fight, &(FIGHTER_INIT[NPC1])))
        return true;
    return false;
}

static bool load_fighters(fight_t *fight)
{
    fight->player = init_fighter_entity(fight->player_stats, fight);
    if (fight->player == NULL)
        return true;
    fight->npc = init_fighter_entity(fight->npc_stats, fight);
    if (fight->npc == NULL)
        return true;
    return false;
}

static void fill_entity_stats(fighter_entity_t *entity)
{
    entity->base_stats.attack = 1;
    entity->base_stats.speed = 1;
    entity->base_stats.stamina = 10;
    entity->base_stats.stamina_regen = 1;
    entity->base_stats.defense = 1;
    entity->base_stats.health = 100;
    entity->stats.health = 100;
    entity->stats.stamina = 10;
}

static void sync_stats(fight_t *fight)
{
    fill_entity_stats(fight->npc);
    fill_entity_stats(fight->player);
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
    fight->fps_clock = sfClock_create();
    fight->stamina_clock = sfClock_create();
    if (fight->view == NULL)
        return NULL;
    sfRenderWindow_setView(game->window, fight->view);
    sfRenderWindow_setKeyRepeatEnabled(game->window, sfFalse);
    if (load_text(fight) || load_arena(fight) ||
        load_fighters(fight) || load_ui(fight))
        return NULL;
    sync_stats(fight);
    return fight;
}
