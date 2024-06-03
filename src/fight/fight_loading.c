/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** fight loading
*/

#include "basics.h"
#include "dict.h"
#include "fight_entity.h"
#include "fight_macros.h"
#include "fight.h"
#include "struct.h"
#include "init_fight_arena.h"
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
#include <time.h>

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

static bool load_fighters(fight_t *fight)
{
    fight->player = init_fighter_entity(fight->player_stats, fight, true);
    if (fight->player == NULL)
        return true;
    fight->npc = init_fighter_entity(fight->npc_stats, fight, false);
    if (fight->npc == NULL)
        return true;
    return false;
}

static void fill_entity_stats(fighter_entity_t *entity,
    physical_entity_t *stats)
{
    entity->base_stats.attack =
        stats->stats.attack + stats->stats.attack_bonus;
    entity->base_stats.speed =
        stats->stats.speed + stats->stats.speed_bonus;
    entity->base_stats.stamina =
        stats->stats.stamina + stats->stats.stamina_bonus;
    entity->base_stats.stamina_regen =
        stats->stats.stamina_regen + stats->stats.stamina_regen_bonus;
    entity->base_stats.defense =
        stats->stats.defense + stats->stats.defense_bonus;
    entity->base_stats.hp =
        stats->stats.hp + stats->stats.hp_bonus;
    entity->stats.hp =
        stats->stats.hp + stats->stats.hp_bonus;
    entity->stats.stamina =
        stats->stats.stamina + stats->stats.stamina_bonus;
}

static void sync_stats(fight_t *fight, physical_entity_t *npc)
{
    fill_entity_stats(fight->npc, fight->npc_stats);
    fill_entity_stats(fight->player, fight->player_stats);
    fight->level = get_npc_level(npc);
    srand(time(0));
}

fight_t *load_fight(game_t *game, physical_entity_t *player,
    physical_entity_t *npc)
{
    fight_t *fight = calloc(1, sizeof(fight_t));

    if (fight == NULL)
        return NULL;
    fight->debug_mode = false;
    fight->arena = get_npc_arena(npc);
    fight->npc_stats = npc;
    fight->player_stats = player;
    fight->view = init_fight_view();
    fight->fps_clock = sfClock_create();
    fight->stamina_clock = sfClock_create();
    fight->end_game_timer = sfClock_create();
    sfRenderWindow_setView(game->window, fight->view);
    sfRenderWindow_setKeyRepeatEnabled(game->window, sfFalse);
    if (load_text(fight) || load_arena(fight) ||
        load_fighters(fight) || load_ui(fight))
        return NULL;
    sync_stats(fight, npc);
    return fight;
}
