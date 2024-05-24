/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** drag_item
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "entity.h"
#include "struct.h"
#include "inventory.h"

static bool is_dragging(inventory_t *inventory, sfVector2f mouse_pos,
    item_t *dragged_item, size_t y)
{
    sfFloatRect bounds = {0};

    for (int x = 0; x < INVENTORY_SIZE_X; ++x) {
        bounds = sfRectangleShape_getGlobalBounds(inventory->slots[y][x].box);
        if (inventory->slots[y][x].item->type != EMPTY_ITEM &&
            sfMouse_isButtonPressed(sfMouseLeft) &&
            sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y)) {
            dragged_item->type = inventory->slots[y][x].item->type;
            dragged_item->sprite = inventory->slots[y][x].item->sprite;
            inventory->slots[y][x].item->type = EMPTY_ITEM;
            inventory->slots[y][x].item->sprite = NULL;
            return true;
        }
    }
    return false;
}

static void process_dragging(inventory_t *inventory, sfVector2f mouse_pos,
    bool *dragging, item_t *dragged_item)
{
    for (int y = 0; y < INVENTORY_SIZE_Y; ++y) {
        if (is_dragging(inventory, mouse_pos, dragged_item, y)) {
            *dragging = true;
            return;
        }
    }
}

static bool isnt_dragging(inventory_t *inventory, sfVector2f mouse_pos,
    item_t *dragged_item, size_t y)
{
    sfFloatRect bounds = {0};

    for (int x = 0; x < INVENTORY_SIZE_X; ++x) {
        bounds = sfRectangleShape_getGlobalBounds(inventory->slots[y][x].box);
        if (inventory->slots[y][x].item->type == EMPTY_ITEM &&
            sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y)) {
            drag_into_slot(&inventory->slots[y][x], dragged_item);
            return true;
        }
    }
    return false;
}

static void process_undragging(inventory_t *inventory, sfVector2f mouse_pos,
    bool *dragging, item_t *dragged_item)
{
    sfSprite_setPosition(dragged_item->sprite, mouse_pos);
    if (sfMouse_isButtonPressed(sfMouseLeft))
        return;
    for (int y = 0; y < INVENTORY_SIZE_Y; ++y) {
        if (isnt_dragging(inventory, mouse_pos, dragged_item, y)) {
            *dragging = false;
            return;
        }
    }
}

void dragg_item(inventory_t *inventory, sfVector2f mouse_pos,
    bool *dragging, item_t *dragged_item)
{
    if (*dragging == false)
        process_dragging(inventory, mouse_pos, dragging, dragged_item);
    else
        process_undragging(inventory, mouse_pos, dragging, dragged_item);
}
