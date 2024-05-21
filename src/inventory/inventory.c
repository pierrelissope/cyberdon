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

void show_single_inventory(sfRenderWindow *window,
    dict_t *items_dict, physical_entity_t *player)
{
    sfVector2f mouse_pos = {0};
    sfEvent event;
    item_t *dragged_item = calloc(1, sizeof(item_t));
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    sfTexture* texture = sfTexture_create(windowSize.x, windowSize.y);
    sfTexture_updateFromRenderWindow(texture, window, 0, 0);
    sfSprite *bg_sprite = sfSprite_create();

    sfSprite_setTexture(bg_sprite, texture, sfTrue);
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
    while (sfRenderWindow_isOpen(window)) {
        mouse_pos = (sfVector2f)sfRenderWindow_mapPixelToCoords
            (window, sfMouse_getPositionRenderWindow(window), NULL);
        while (sfRenderWindow_pollEvent(window, &event))
            if (sfKeyboard_isKeyPressed(sfKeyEscape))
                return;
        update_inventory(player->inventory, mouse_pos);
        dragg_item(player->inventory, mouse_pos, dragged_item);
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, bg_sprite, NULL);
        draw_inventory(window, player->inventory);
        draw_stats_menu(window, &player->stats);
        if (dragged_item != NULL && dragged_item->type != EMPTY_ITEM)
            sfRenderWindow_drawSprite(window, dragged_item->sprite, NULL);
        sfRenderWindow_display(window);
    }
    return;
}

void play_inventory(sfRenderWindow *window, dict_t *items_dict,
    inventory_t *inventory, inventory_t *inventory2)
{
    sfVector2f mouse_pos = {0};
    sfEvent event;
    item_t *dragged_item = calloc(1, sizeof(item_t));
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    sfTexture* texture = sfTexture_create(windowSize.x, windowSize.y);
    sfTexture_updateFromRenderWindow(texture, window, 0, 0);
    sfSprite *bg_sprite = sfSprite_create();

    sfSprite_setTexture(bg_sprite, texture, sfTrue);
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
    while (sfRenderWindow_isOpen(window)) {
        mouse_pos = (sfVector2f)sfRenderWindow_mapPixelToCoords
            (window, sfMouse_getPositionRenderWindow(window), NULL);
        while (sfRenderWindow_pollEvent(window, &event))
            if (sfKeyboard_isKeyPressed(sfKeyEscape))
                return;
        
        update_inventory(inventory, mouse_pos);
        update_inventory(inventory2, mouse_pos);

        dragg_item(inventory, mouse_pos, dragged_item);
        dragg_item(inventory2, mouse_pos, dragged_item);

        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, bg_sprite, NULL);
        draw_inventory(window, inventory);
        draw_inventory(window, inventory2);

        if (dragged_item != NULL && dragged_item->type != EMPTY_ITEM)
            sfRenderWindow_drawSprite(window, dragged_item->sprite, NULL);
        sfRenderWindow_display(window);
    }
    return;
}
