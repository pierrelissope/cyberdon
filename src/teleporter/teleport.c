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
            sfRectangleShape_setPosition(game->player->rect,
                teleporters[i]->destination_coord);
            game->world = (world_t){0};
            load_level(&game->world, teleporters[i]->destination_level,
                game->tiles_dict, game->sheets_dict);
            play_loading_screen(game->window, &game->loading_page);
            sfClock_restart(status->teleportation_clock);
            game->game_state = IN_CINEMATIC;
            game->player->current_sprite_sheet = dict_get(game->player->sprite_sheets, IDLE);
            sfView_zoom(game->player_view, 1.5);
            sfClock_restart(game->clock);
            break;
        }
    }
}
