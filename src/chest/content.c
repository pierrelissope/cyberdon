/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** content
*/

#include <stdlib.h>
#include <string.h>

#include "myutils.h"
#include "entity.h"
#include "inventory.h"
#include "init_texture.h"

static const float open_area = 50; 

void check_openned_chest(game_t *game)
{
    static bool in_chest = false;
    sfFloatRect player_hitbox =
        sfRectangleShape_getGlobalBounds(game->player->rect);
    sfFloatRect chest_hitbox = {0};

    player_hitbox.left -= open_area;
    player_hitbox.top -= open_area;
    player_hitbox.height += 2 * open_area;
    player_hitbox.width += 2 * open_area;
    for (size_t i = 0; game->world.chests && game->world.chests[i]; ++i) {
        sfSprite_setTextureRect(game->world.chests[i]->sprite,
            (sfIntRect){0, 0, 128, 94});
        chest_hitbox =
            sfRectangleShape_getGlobalBounds(game->world.chests[i]->rect);
        if (sfFloatRect_intersects(&player_hitbox, &chest_hitbox, NULL)) {
            sfSprite_setTextureRect(game->world.chests[i]->sprite,
                (sfIntRect){128, 0, 128, 94});
            if (sfKeyboard_isKeyPressed(sfKeyEnter))
                play_inventory(game->window, game->items_dict, game->player->inventory, game->world.chests[i]->inventory);
        }
    }
}
