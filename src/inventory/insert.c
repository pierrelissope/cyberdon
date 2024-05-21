/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** insert
*/

#include "inventory.h"
#include "dict.h"
#include "struct.h"

void drag_into_slot(slot_t *slot, item_t *dragged_item)
{
    sfVector2f slot_center_pos = sfRectangleShape_getPosition(slot->box);

    slot->item->sprite = dragged_item->sprite;
    slot->item->type = dragged_item->type;
    slot_center_pos.x += SLOT_SIZE / 2;
    slot_center_pos.y += SLOT_SIZE / 2;
    sfSprite_setPosition(slot->item->sprite, slot_center_pos);
    dragged_item->sprite = NULL;
    dragged_item->type = EMPTY_ITEM;
}

void insert_into_slot(slot_t *slot, item_type_t item, dict_t *items_dict)
{
    sfVector2f slot_center_pos = sfRectangleShape_getPosition(slot->box);

    slot->item->type = item;
    slot->item->sprite = sfSprite_create();
    sfSprite_setTexture(slot->item->sprite,
        dict_get(items_dict, item), sfTrue);
    sfSprite_setOrigin(slot->item->sprite,
        (sfVector2f){ITEM_SIZE / 2, ITEM_SIZE / 2});
    slot_center_pos.x += SLOT_SIZE / 2;
    slot_center_pos.y += SLOT_SIZE / 2;
    sfSprite_setPosition(slot->item->sprite, slot_center_pos);
}

static bool browse_inventory(inventory_t *inventory,
    item_type_t item, dict_t *items_dict, size_t y)
{
    for (int x = 0; x < INVENTORY_SIZE_X; ++x) {
        if (inventory->slots[y][x].item->type == EMPTY_ITEM) {
            insert_into_slot(&inventory->slots[y][x],
                item, items_dict);
            return true;
        }
    }
    return false;
}

void insert_item(inventory_t *inventory,
    item_type_t item, dict_t *items_dict)
{
    for (size_t y = 0; y < INVENTORY_SIZE_Y; ++y) {
        if (browse_inventory(inventory, item, items_dict, y))
            return;
    }
}
