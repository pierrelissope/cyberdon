/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** update
*/

#include <string.h>

#include "game.h"
#include "basics.h"
#include "dict.h"
#include "init_texture.h"
#include "struct.h"
#include "inventory.h"

static void update_slot(slot_t *slot, sfVector2f mouse_pos)
{
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(slot->box);

    if (sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y))
        sfRectangleShape_setFillColor(slot->box, LIGHT_GREY);
    else
        sfRectangleShape_setFillColor(slot->box, DARK_GREY);
} 

void update_inventory(inventory_t *inventory, sfVector2f mouse_pos)
{

    for (int y = 0; y < INVENTORY_SIZE_Y; ++y) {
        for (int x = 0; x < INVENTORY_SIZE_X; ++x) {
            update_slot(&inventory->slots[y][x], mouse_pos);
        }
    }
}
