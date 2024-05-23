/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** menu
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdbool.h>
#include "struct.h"
#include "mh_menu.h"
#include "game.h"
#include "basics.h"

bool my_hover(sfRenderWindow *window, sfText *text)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfFloatRect text_bounds = sfText_getGlobalBounds(text);

    return sfFloatRect_contains(&text_bounds, mouse_pos.x, mouse_pos.y);
}

static void handle_events(sfRenderWindow *window, int *selected_item,
    menu_item_t *menu_items, game_t *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtKeyPressed && event.key.code == game->game_info->key[MOVE_DOWN])
            *selected_item = (*selected_item + 1) % ITM_COUNT;
        if (event.type == sfEvtKeyPressed && event.key.code == game->game_info->key[MOVE_UP])
            *selected_item = (*selected_item + ITM_COUNT - 1) % ITM_COUNT;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape &&
            game->game_info->specifier == 1)
            game->game_state = IN_GAME;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn)
            menu_items[*selected_item].action(window, game->game_info, game);
        if (event.type == sfEvtMouseButtonPressed &&
            event.mouseButton.button == sfMouseLeft)
            menu_items[*selected_item].action(window, game->game_info, game);
    }
}

static void jouer(sfRenderWindow *window,
    game_info_t *game_info, game_t *game)
{
    game->game_info->specifier = 1;
    game->game_state = IN_GAME;
}

static void quitter(sfRenderWindow *window,
    game_info_t *game_info, game_t *game)
{
    sfRenderWindow_close(window);
}

sfText *create_text(char *string, sfVector2f position,
    sfFont *font, bool is_selected)
{
    sfText *text = sfText_create();

    sfText_setString(text, string);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, is_selected ? 70 : 50);
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, position);
    return text;
}

void blink(sfClock *clock, sfRectangleShape *rect)
{
    sfColor color;
    sfBool is_visible;
    sfTime elapsed = sfClock_getElapsedTime(clock);

    if (sfTime_asSeconds(elapsed) > 0.7) {
        is_visible = sfRectangleShape_getOutlineColor(rect).a == 0
                    ? sfTrue
                    : sfFalse;
        color = is_visible ? sfRed : sfTransparent;
        sfRectangleShape_setOutlineColor(rect, color);
        sfClock_restart(clock);
    }
}

sfRectangleShape *create_rectangle(void)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setFillColor(rect, sfTransparent);
    sfRectangleShape_setOutlineColor(rect, sfRed);
    sfRectangleShape_setOutlineThickness(rect, 2);
    return rect;
}

static menu_item_t *my_init_tab(int specifier)
{
    menu_item_t *menu = malloc(sizeof(menu_item_t) * 3);

    if (specifier == 0){
        menu[0].selected_item = my_strdup("Play");
        menu[0].action = jouer;
        menu[1].selected_item = my_strdup("Settings");
        menu[1].action = parametres;
        menu[2].selected_item = my_strdup("Leave");
        menu[2].action = quitter;
        return menu;
    }
    if (specifier == 1){
        menu[0].selected_item = my_strdup("Resume");
        menu[0].action = jouer;
        menu[1].selected_item = my_strdup("Settings");
        menu[1].action = parametres;
        menu[2].selected_item = my_strdup("Leave");
        menu[2].action = quitter;
        return menu;
    }
}

void menu(game_t *game)
{
    menu_item_t *menu_items = my_init_tab(game->game_info->specifier);
    int selected_item = 0;
    sfRectangleShape *rect = create_rectangle();
    sfClock *clock = sfClock_create();

    while (sfRenderWindow_isOpen(game->window) &&
        game->game_state == IN_MENU) {
        handle_events(game->window, &selected_item, menu_items, game);
        blink(clock, rect);
        draw_menu(game->window, rect, &selected_item, menu_items);
    }
}
