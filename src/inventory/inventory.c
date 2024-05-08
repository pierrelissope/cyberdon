/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** inventory
*/

#include <stdio.h>
#include <stdlib.h>

#include "entity.h"
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

static void update_inventory(inventory_t *inventory, sfVector2f mouse_pos)
{

    for (int y = 0; y < INVENTORY_SIZE_Y; ++y) {
        for (int x = 0; x < INVENTORY_SIZE_X; ++x) {
            update_slot(&inventory->slots[y][x], mouse_pos);
        }
    }
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
}

void dragg_item(inventory_t *inventory, sfVector2f mouse_pos, item_t *dragged_item)
{
    sfFloatRect bounds = {0};
    static bool dragging = false;

    if (dragging == false) {
        for (int y = 0; y < INVENTORY_SIZE_Y; ++y) {
            for (int x = 0; x < INVENTORY_SIZE_X; ++x) {
                bounds = sfRectangleShape_getGlobalBounds(inventory->slots[y][x].box);
                if (inventory->slots[y][x].item->type != EMPTY_ITEM &&
                    sfMouse_isButtonPressed(sfMouseLeft) &&
                    sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y)) {
                    dragged_item->type = inventory->slots[y][x].item->type;
                    dragged_item->sprite = inventory->slots[y][x].item->sprite;
                    inventory->slots[y][x].item->type = EMPTY_ITEM;
                    inventory->slots[y][x].item->sprite = NULL;
                    dragging = true;
                    return;
                }
            }
        }
    } else {
        sfSprite_setPosition(dragged_item->sprite, mouse_pos);
        if (!sfMouse_isButtonPressed(sfMouseLeft)) {
            for (int y = 0; y < INVENTORY_SIZE_Y; ++y) {
                for (int x = 0; x < INVENTORY_SIZE_X; ++x) {
                    bounds = sfRectangleShape_getGlobalBounds(inventory->slots[y][x].box);
                    if (inventory->slots[y][x].item->type == EMPTY_ITEM &&
                        sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y)) {
                        drag_into_slot(&inventory->slots[y][x], dragged_item);
                        dragging = false;
                        return;
                    }
                }
            }
        }
    }
}

void play_inventory(sfRenderWindow *window, dict_t *items_dict)
{
    sfVector2f inventory_position = {50.f, 50.f};
    inventory_t *inventory = create_inventory(inventory_position);
    inventory_t *inventory2 = create_inventory((sfVector2f){1300, 50});

    sfVector2f mouse_pos = {0};
    sfEvent event;
    item_t *dragged_item = calloc(1, sizeof(dragged_item));

    
    insert_item(inventory, SPEED_ORB, items_dict);
    insert_item(inventory, SPEED_ORB, items_dict);
    insert_item(inventory, STRENGTH_ORB, items_dict);
    insert_item(inventory, STRENGTH_ORB, items_dict);

    insert_item(inventory2, SPEED_ORB, items_dict);
    insert_item(inventory2, SPEED_ORB, items_dict);

    while (sfRenderWindow_isOpen(window)) {
        mouse_pos = (sfVector2f)sfRenderWindow_mapPixelToCoords
            (window, sfMouse_getPositionRenderWindow(window), NULL);
        while (sfRenderWindow_pollEvent(window, &event))
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);

        
        update_inventory(inventory, mouse_pos);
        update_inventory(inventory2, mouse_pos);

        dragg_item(inventory, mouse_pos, dragged_item);
        dragg_item(inventory2, mouse_pos, dragged_item);

        sfRenderWindow_clear(window, sfBlack);
        draw_inventory(window, inventory);
        draw_inventory(window, inventory2);

        if (dragged_item != NULL && dragged_item->type != EMPTY_ITEM)
            sfRenderWindow_drawSprite(window, dragged_item->sprite, NULL);
        sfRenderWindow_display(window);
    }
    return;
}
