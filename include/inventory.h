/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** inventory
*/

#pragma once

#define INVENTORY_SIZE_X 5
#define INVENTORY_SIZE_Y 3
#define SLOT_SIZE 100
#define SLOT_MARGIN 10
#define SLOTS_MARGIN_TOP 100
#define OUTLINE_THIKNESS 1
#define ITEM_SIZE 80

#define LIGHT_GREY sfColor_fromRGB(50, 50, 50)
#define GREY sfColor_fromRGB(39, 40, 44)
#define DARK_GREY sfColor_fromRGB(31, 32, 34)
#define LIGHT_WHITE sfColor_fromRGBA(150, 150, 150, 100)

#include "entity.h"

inventory_t* create_inventory(sfVector2f position);
void destroy_inventory(inventory_t *inventory);
void play_inventory(sfRenderWindow *window, dict_t *items_dict);
void insert_item(inventory_t *inventory,
    item_type_t item, dict_t *items_dict);
void drag_into_slot(slot_t *slot, item_t *item);
