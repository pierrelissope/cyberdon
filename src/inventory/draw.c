/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** draw
*/

#include <string.h>

#include "game.h"
#include "basics.h"
#include "dict.h"
#include "init_texture.h"
#include "struct.h"
#include "inventory.h"

void draw_stats_menu(sfRenderWindow *window, stats_t *stats)
{
    sfRenderWindow_drawRectangleShape(window, stats->box, NULL);
    sfRenderWindow_drawRectangleShape(window, stats->sprite_rect, NULL);
    sfRenderWindow_drawSprite(window, stats->sprite, NULL);
    sfRenderWindow_drawText(window, stats->level_text, NULL);
    sfRenderWindow_drawText(window, stats->xp_text, NULL);
    sfRenderWindow_drawText(window, stats->hp_text, NULL);
    sfRenderWindow_drawText(window, stats->defense_text, NULL);
    sfRenderWindow_drawText(window, stats->attack_text, NULL);
    sfRenderWindow_drawText(window, stats->speed_text, NULL);
    sfRenderWindow_drawText(window, stats->strength_text, NULL);
    sfRenderWindow_drawText(window, stats->stamina_text, NULL);
    sfRenderWindow_drawText(window, stats->stamina_regeneration_text, NULL);
    sfRenderWindow_drawText(window, stats->hp_bonus_text, NULL);
    sfRenderWindow_drawText(window, stats->defense_bonus_text, NULL);
    sfRenderWindow_drawText(window, stats->attack_bonus_text, NULL);
    sfRenderWindow_drawText(window, stats->strength_bonus_text, NULL);
    sfRenderWindow_drawText(window, stats->speed_bonus_text, NULL);
    sfRenderWindow_drawText(window, stats->stamina_bonus_text, NULL);
    sfRenderWindow_drawText(window,
        stats->stamina_regeneration_bonus_text, NULL);    
}

void draw_inventory(sfRenderWindow *window, inventory_t *inventory)
{
    sfRenderWindow_drawRectangleShape(window, inventory->box, NULL);
    for (int y = 0; y < INVENTORY_SIZE_Y; ++y) {
        for (int x = 0; x < INVENTORY_SIZE_X; ++x) {
            sfRenderWindow_drawRectangleShape(
                window, inventory->slots[y][x].box, NULL);
            if (inventory->slots[y][x].item->type != EMPTY_ITEM)
                sfRenderWindow_drawSprite(window, inventory->slots[y][x].item->sprite, NULL);
        }
    }
    sfRenderWindow_drawText(window, inventory->text, NULL);
}
