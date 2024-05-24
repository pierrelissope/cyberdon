/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** destroy
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "entity.h"
#include "struct.h"
#include "inventory.h"


void destroy_item(item_t *item)
{
    if (item == NULL)
        return;
    sfSprite_destroy(item->sprite);
    free(item);
}

void destroy_inventory(inventory_t *inventory)
{
    if (inventory == NULL)
        return;
    free(inventory->name);
    sfRectangleShape_destroy(inventory->box);
    sfText_destroy(inventory->text);
    for (size_t y = 0; y < INVENTORY_SIZE_Y; y++) {
        for (size_t x = 0; x < INVENTORY_SIZE_X; ++x) {
            sfRectangleShape_destroy(inventory->slots[y][x].box);
            destroy_item(inventory->slots[y][x].item);
        }
        free(inventory->slots[y]);
    }
    free(inventory->slots);
    free(inventory);
}

void destroy_stats(stats_t *stats)
{
    sfRectangleShape_destroy(stats->box);
    sfSprite_destroy(stats->sprite);
    sfRectangleShape_destroy(stats->sprite_rect);
    sfText_destroy(stats->level_text);
    sfText_destroy(stats->xp_text);
    sfText_destroy(stats->hp_text);
    sfText_destroy(stats->defense_text);
    sfText_destroy(stats->attack_text);
    sfText_destroy(stats->speed_text);
    sfText_destroy(stats->strength_text);
    sfText_destroy(stats->stamina_text);
    sfText_destroy(stats->stamina_regen_text);
    sfText_destroy(stats->hp_bonus_text);
    sfText_destroy(stats->defense_bonus_text);
    sfText_destroy(stats->attack_bonus_text);
    sfText_destroy(stats->speed_bonus_text);
    sfText_destroy(stats->strength_bonus_text);
    sfText_destroy(stats->stamina_bonus_text);
    sfText_destroy(stats->stamina_regen_bonus_text);
}
