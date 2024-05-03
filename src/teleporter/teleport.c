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

void teleport_player(game_t *game, teleporter_t **teleporters)
{
    sfFloatRect tp_bounds = {0};
    sfFloatRect player_bounds =
        sfRectangleShape_getGlobalBounds(game->player->rect);

    for (int i = 0; teleporters && teleporters[i]; ++i) {
        tp_bounds = sfRectangleShape_getGlobalBounds(teleporters[i]->rect);
        if (sfFloatRect_intersects(&player_bounds, &tp_bounds, NULL)) {
            sfRectangleShape_setPosition(game->player->rect,
                teleporters[i]->destination_coord);
            game->world = (world_t){0};
            load_level(&game->world, teleporters[i]->destination_level,
                game->tiles_dict, game->sheets_dict);
            break;
        }
    }
}
