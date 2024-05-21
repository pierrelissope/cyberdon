/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** item_description
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "entity.h"
#include "struct.h"
#include "inventory.h"

static sfText *create_text(sfVector2f pos, char *str)
{
    sfText *text = sfText_create();

    sfText_setFont(text, FONT);
    sfText_setCharacterSize(text, 36);
    sfText_setString(text, str);
    sfText_setFillColor(text, sfWhite);
    sfText_setPosition(text, pos);
    return text;
}

static char *get_item_description(item_type_t item_type)
{
    for (size_t i = 0; ITEMS_LINK_ARRAY[i].str_type != NULL; ++i)
        if (ITEMS_LINK_ARRAY[i].enum_type == item_type &&
            ITEMS_LINK_ARRAY[i].description)
            return ITEMS_LINK_ARRAY[i].description;
    dprintf(2, "DESCRIPTION ISSUE\n");
    return "?????";
}

static void show_description(sfRenderWindow *window, sfVector2f mouse_pos, item_t *item)
{
    sfRectangleShape *rectangle = sfRectangleShape_create();
    sfText *text = create_text((sfVector2f){mouse_pos.x + 20,
        mouse_pos.y + 20}, get_item_description(item->type));

    sfRectangleShape_setPosition(rectangle, mouse_pos);
    sfRectangleShape_setFillColor(rectangle, GREY);
    sfRectangleShape_setOutlineThickness(rectangle, 1);
    sfRectangleShape_setOutlineColor(rectangle, LIGHT_WHITE);
    sfRectangleShape_setSize(rectangle, (sfVector2f){430, 120});
    if (mouse_pos.x + 430 > 1920) {
        sfRectangleShape_move(rectangle, (sfVector2f){-440, 0});
        sfText_move(text, (sfVector2f){-440, 0});
    }
    sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
    sfRenderWindow_drawText(window, text, NULL);
    sfText_destroy(text);
    sfRectangleShape_destroy(rectangle);
}

static bool is_showing_description(sfRenderWindow *window, sfVector2f mouse_pos,
    inventory_t *inventory, size_t y)
{
    sfFloatRect bounds = {0};

    for (size_t x = 0; x < INVENTORY_SIZE_X; ++x) {
        bounds = sfRectangleShape_getGlobalBounds(inventory->slots[y][x].box);
        if (inventory->slots[y][x].item->type != EMPTY_ITEM &&
            sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y)) {
            show_description(window, mouse_pos, inventory->slots[y][x].item);
            return true;
        }
    }
    return false;
}

void show_item_description(sfRenderWindow *window, sfVector2f mouse_pos,
    inventory_t *inventory)
{
    for (size_t y = 0; y < INVENTORY_SIZE_Y; ++y)
        if (is_showing_description(window, mouse_pos, inventory, y))
            return;
}
