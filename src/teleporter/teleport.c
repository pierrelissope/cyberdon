/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** teleport
*/

#include "entity.h"
#include "utils.h"
#include "init_texture.h"
#include "teleporter.h"
#include "mymenu.h"

static const float TELEPORTATION_COOLDOWN = 1.0;

bool level_have_been_visited(const char *destination_level,
     char *const *const visited_levels)
{
    for (int i = 0; visited_levels[i] != NULL &&
        visited_levels[i] != NULL; i++) {
        if (strcmp(visited_levels[i], destination_level) == 0)
            return true;
    }
    return false;
}

void teleporter_detected(game_t *game, teleporter_t *teleporter,
    status_t *status)
{
    sfRectangleShape_setPosition(game->player->rect,
        teleporter->destination_coord);
    if (level_have_been_visited(
        teleporter->destination_level, game->visited_levels) == false) {
        game->game_state = IN_CINEMATIC;
        sfView_zoom(game->player_view, 1.5);
    }
    load_level(game, teleporter->destination_level,
        game->tiles_dict, game->sheets_dict);
    play_loading_screen(game->window, &game->loading_page);
    sfClock_restart(status->teleportation_clock);
    game->player->current_sprite_sheet =
        dict_get(game->player->sprite_sheets, IDLE);
    sfClock_restart(game->clock);
}

void teleport_player(game_t *game, teleporter_t **teleporters,
    status_t *status)
{
    sfFloatRect tp_bounds = {0};
    sfFloatRect player_bounds =
        sfRectangleShape_getGlobalBounds(game->player->rect);
    float now = sfTime_asSeconds(
        sfClock_getElapsedTime(status->teleportation_clock));

    if (now < TELEPORTATION_COOLDOWN)
        return;
    for (int i = 0; teleporters && teleporters[i]; ++i) {
        tp_bounds = sfRectangleShape_getGlobalBounds(teleporters[i]->rect);
        if (sfFloatRect_intersects(&player_bounds, &tp_bounds, NULL)) {
            teleporter_detected(game, teleporters[i], status);
            break;
        }
    }
}
