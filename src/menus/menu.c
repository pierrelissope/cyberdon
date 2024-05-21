/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** menu
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include "menu.h"
#include "game.h"
#include <stdbool.h>

bool my_hover(sfRenderWindow *window, sfText *text)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfFloatRect text_bounds = sfText_getGlobalBounds(text);

    return sfFloatRect_contains(&text_bounds, mouse_pos.x, mouse_pos.y);
}

static void handle_events(sfRenderWindow *window, int *selected_item,
    menu_item_t *menu_items, game_info_t *game_info)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown)
            *selected_item = (*selected_item + 1) % ITM_COUNT;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp)
            *selected_item = (*selected_item + ITM_COUNT - 1) % ITM_COUNT;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn)
            menu_items[*selected_item].action(window, game_info);
        if (event.type == sfEvtMouseButtonPressed &&
            event.mouseButton.button == sfMouseLeft)
            menu_items[*selected_item].action(window, game_info);
    }
}

static void jouer(sfRenderWindow *window, game_info_t *game_info)
{
    game_t game = init_game();

    sfRenderWindow_close(window);
    run_game(&game, game_info);
    destroy_game(&game);
}

static void quitter(sfRenderWindow *window)
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

void menu(game_info_t *game_info)
{
    sfVideoMode mode = {1920, 1080, 30};
    sfRenderWindow *window = sfRenderWindow_create(mode,
        "Menu", sfClose, NULL);
    menu_item_t menu_items[] = {
        {"play", jouer},
        {"settings", parametres},
        {"quitter", quitter}
    };
    sfFont *font = sfFont_createFromFile("assets/font/font.ttf");
    int selected_item = 0;
    sfRectangleShape *rect = create_rectangle();
    sfClock *clock = sfClock_create();

    while (sfRenderWindow_isOpen(window)) {
        handle_events(window, &selected_item,
            menu_items, game_info);
        blink(clock, rect);
        draw_menu(window, rect, &selected_item);
    }
}
