/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** inventory
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "entity.h"
#include "struct.h"
#include "inventory.h"

void show_single_inventory(sfRenderWindow *window,
    physical_entity_t *player)
{
    sfVector2f mouse_pos = {0};
    sfEvent event;
    item_t *dragged_item = calloc(1, sizeof(item_t));
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    sfTexture* texture = sfTexture_create(windowSize.x, windowSize.y);
    sfTexture_updateFromRenderWindow(texture, window, 0, 0);
    sfSprite *bg_sprite = sfSprite_create();
    bool dragging = false;

    sfSprite_setTexture(bg_sprite, texture, sfTrue);
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
    while (sfRenderWindow_isOpen(window)) {
        mouse_pos = (sfVector2f)sfRenderWindow_mapPixelToCoords
            (window, sfMouse_getPositionRenderWindow(window), NULL);
        while (sfRenderWindow_pollEvent(window, &event))
            if (sfKeyboard_isKeyPressed(sfKeyEscape))
                return;
        update_inventory(player->inventory, mouse_pos);
        update_stats(&player->stats, player->inventory);
        dragg_item(player->inventory, mouse_pos, &dragging, dragged_item);
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, bg_sprite, NULL);
        draw_inventory(window, player->inventory);
        draw_stats_menu(window, &player->stats);
        show_item_description(window, mouse_pos, player->inventory);
        if (dragged_item != NULL && dragged_item->type != EMPTY_ITEM)
            sfRenderWindow_drawSprite(window, dragged_item->sprite, NULL);
        sfRenderWindow_display(window);
    }
    return;
}

void play_inventory(sfRenderWindow *window,
    inventory_t *inventory, inventory_t *inventory2)
{
    sfVector2f mouse_pos = {0};
    sfEvent event;
    item_t *dragged_item = calloc(1, sizeof(item_t));
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    sfTexture* texture = sfTexture_create(windowSize.x, windowSize.y);
    sfTexture_updateFromRenderWindow(texture, window, 0, 0);
    sfSprite *bg_sprite = sfSprite_create();
    bool dragging = false;

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

        dragg_item(inventory, mouse_pos, &dragging, dragged_item);
        dragg_item(inventory2, mouse_pos, &dragging, dragged_item);

        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, bg_sprite, NULL);
        draw_inventory(window, inventory);
        draw_inventory(window, inventory2);
        show_item_description(window, mouse_pos, inventory);
        show_item_description(window, mouse_pos, inventory2);
        if (dragged_item != NULL && dragged_item->type != EMPTY_ITEM)
            sfRenderWindow_drawSprite(window, dragged_item->sprite, NULL);
        sfRenderWindow_display(window);
    }
    return;
}
