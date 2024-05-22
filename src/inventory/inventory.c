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

struct inventory_screen_s {
    sfVector2f mouse_pos;
    sfRenderWindow *window;
    item_t *dragged_item;
    sfTexture* texture;
    sfSprite *bg_sprite;
    bool dragging;
};

static void process_single_inventory(struct inventory_screen_s *content,
    physical_entity_t *player)
{
    content->mouse_pos = (sfVector2f)sfRenderWindow_mapPixelToCoords(
        content->window,
        sfMouse_getPositionRenderWindow(content->window), NULL);
    update_inventory(player->inventory, content->mouse_pos);
    update_stats(&player->stats, player->inventory);
    dragg_item(player->inventory, content->mouse_pos,
        &(content->dragging), content->dragged_item);
    sfRenderWindow_clear(content->window, sfBlack);
    sfRenderWindow_drawSprite(content->window, content->bg_sprite, NULL);
    draw_inventory(content->window, player->inventory);
    draw_stats_menu(content->window, &player->stats);
    show_item_description(content->window,
        content->mouse_pos, player->inventory);
    if (content->dragged_item != NULL &&
        content->dragged_item->type != EMPTY_ITEM)
        sfRenderWindow_drawSprite(content->window,
            content->dragged_item->sprite, NULL);
    sfRenderWindow_display(content->window);
}

void show_single_inventory(sfRenderWindow *window,
    physical_entity_t *player)
{
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    sfEvent event;
    struct inventory_screen_s content = {
        .mouse_pos = {0}, .window = window,
        .dragged_item = calloc(1, sizeof(item_t)),
        .texture = sfTexture_create(windowSize.x, windowSize.y),
        .bg_sprite = sfSprite_create(), .dragging = false};

    sfTexture_updateFromRenderWindow(content.texture, window, 0, 0);
    sfSprite_setTexture(content.bg_sprite, content.texture, sfTrue);
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
    while (sfRenderWindow_isOpen(window)) {
        if (handle_inventory_event(window, &event) == sfEvtClosed)
            break;
        process_single_inventory(&content, player);
    }
}

static void process_multiple_inventory(sfRenderWindow *window,
    struct inventory_screen_s *content, inventory_t *inv1, inventory_t *inv2)
{
    update_inventory(inv1, content->mouse_pos);
    update_inventory(inv2, content->mouse_pos);
    dragg_item(inv1, content->mouse_pos, &content->dragging,
        content->dragged_item);
    dragg_item(inv2, content->mouse_pos, &content->dragging,
        content->dragged_item);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, content->bg_sprite, NULL);
    draw_inventory(window, inv1);
    draw_inventory(window, inv2);
    show_item_description(window, content->mouse_pos, inv1);
    show_item_description(window, content->mouse_pos, inv2);
    if (content->dragged_item != NULL &&
        content->dragged_item->type != EMPTY_ITEM)
        sfRenderWindow_drawSprite(window, content->dragged_item->sprite, NULL);
    sfRenderWindow_display(window);
}

void play_inventory(sfRenderWindow *window,
    inventory_t *inventory, inventory_t *inventory2)
{
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    sfEvent event;
    struct inventory_screen_s content = {
        .mouse_pos = {0}, .window = window,
        .dragged_item = calloc(1, sizeof(item_t)),
        .texture = sfTexture_create(windowSize.x, windowSize.y),
        .bg_sprite = sfSprite_create(), .dragging = false};

    sfTexture_updateFromRenderWindow(content.texture, window, 0, 0);
    sfSprite_setTexture(content.bg_sprite, content.texture, sfTrue);
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
    while (sfRenderWindow_isOpen(window)) {
        content.mouse_pos = (sfVector2f)sfRenderWindow_mapPixelToCoords
            (window, sfMouse_getPositionRenderWindow(window), NULL);
        if (handle_inventory_event(window, &event) == sfEvtClosed)
            break;
        process_multiple_inventory(window, &content, inventory, inventory2);
    }
}
