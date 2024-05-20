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

void handle_events(sfRenderWindow *window, int *selected_item,
    int item_count, menu_item_t *menu_items, game_info_t *game_info)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown)
            *selected_item = (*selected_item + 1) % item_count;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp)
            *selected_item = (*selected_item + item_count - 1) % item_count;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn)
            menu_items[*selected_item].action(window, game_info);
        if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft)
            menu_items[*selected_item].action(window, game_info);
    }
}

void parametres(sfRenderWindow *window, game_info_t *game_info)
{
    sfFont *font = sfFont_createFromFile("assets/font/font.ttf");
    sfText *param_text = create_text("Parametres",
        (sfVector2f){850, 500}, font, false);
    sfText *resize_text = create_text("Resize",
        (sfVector2f){850, 560}, font, false);
    int selected_item = 0;
    sfClock *clock = sfClock_create();
    sfRectangleShape *rect = create_rectangle();
    sfVector2u sizes[] = {{800, 600}, {1280, 720}, {1920, 1080}};
    int current_size_index = 1;
    sfEvent event;

    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed ||
                (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape))
                return;
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown)
                selected_item = (selected_item + 1) % 2;
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp)
                selected_item = (selected_item + 1) % 2;
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyRight && selected_item == 1)
                current_size_index = (current_size_index + 1) % 3;
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyLeft && selected_item == 1)
                current_size_index = (current_size_index + 2) % 3;
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn) {
                if (selected_item == 0) {
                } else if (selected_item == 1) {
                    sfVector2u new_size = sizes[current_size_index];
                    printf("x : %d, y : %d\n", new_size.x, new_size.y);
                    printf("avant : x : %d, y : %d\n", game_info->screen_res.x, game_info->screen_res.y);
                    game_info->screen_res.x = new_size.x;
                    game_info->screen_res.y = new_size.y;
                    printf("après : x : %d, y : %d\n", game_info->screen_res.x, game_info->screen_res.y);
                    sfRenderWindow_setSize(window, new_size);
                }
            }
        }
        char size_text[32];
        snprintf(size_text, sizeof(size_text), "Resize: %ux%u", sizes[current_size_index].x, sizes[current_size_index].y);
        sfText *param_text = create_text("Parametres", (sfVector2f){850, 500}, font, selected_item == 0);
        sfText *resize_text = create_text(size_text, (sfVector2f){850, 560}, font, selected_item == 1);
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawText(window, param_text, NULL);
        sfRenderWindow_drawText(window, resize_text, NULL);
        sfRenderWindow_display(window);
        sfText_destroy(param_text);
        sfText_destroy(resize_text);
    }
    sfFont_destroy(font);
    sfClock_destroy(clock);
    sfRectangleShape_destroy(rect);
}

void jouer(sfRenderWindow *window, game_info_t *game_info)
{
    game_t game = init_game();

    sfRenderWindow_close(window);
    run_game(&game, game_info);
    destroy_game(&game);
}

void quitter(sfRenderWindow *window)
{
    sfRenderWindow_close(window);
}

void update_resolution(game_info_t *game_info, sfVector2u new_resolution)
{
    game_info->screen_res = new_resolution;
}

sfText *create_text(char *string, sfVector2f position, sfFont *font, bool is_selected)
{
    sfText *text = sfText_create();
    sfText_setString(text, string);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, is_selected ? 70 : 50);
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, position);
    return text;
}

void draw_menu(sfRenderWindow *window, sfRectangleShape *rect, int *selected_item)
{
    sfFont *font = sfFont_createFromFile("assets/font/font.ttf");
    sfVector2f jouer_text_pos = {915, 500};
    sfVector2f param_text_pos = {915, 560};
    sfVector2f quitter_text_pos = {915, 620};
    sfText *selected_text;
    sfFloatRect text_rect;
    sfText *jouer_text = create_text("play", jouer_text_pos, font, *selected_item == 0);
    sfText *param_text = create_text("settings", param_text_pos, font, *selected_item == 1);
    sfText *quitter_text = create_text("quit", quitter_text_pos, font, *selected_item == 2);
    sfVector2f rect_pos;
    sfVector2f rect_size;

    sfText *texts[] = {jouer_text, param_text, quitter_text};
    for (int i = 0; i < 3; i++) {
        if (my_hover(window, texts[i])) {
            *selected_item = i;
        }
    }
    selected_text = texts[*selected_item];
    text_rect = sfText_getGlobalBounds(selected_text);
    rect_pos = (sfVector2f){text_rect.left - 10, text_rect.top - 5};
    rect_size = (sfVector2f){text_rect.width + 20, text_rect.height + 10};
    sfRenderWindow_clear(window, sfBlack);
    for (int i = 0; i < 3; i++) {
        sfRenderWindow_drawText(window, texts[i], NULL);
    }
    sfRectangleShape_setPosition(rect, rect_pos);
    sfRectangleShape_setSize(rect, rect_size);
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
    sfRenderWindow_display(window);
    for (int i = 0; i < 3; i++) {
        sfText_destroy(texts[i]);
    }
    sfFont_destroy(font);
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
    sfRenderWindow *window = sfRenderWindow_create(mode, "Menu", sfClose, NULL);
    menu_item_t menu_items[] = {
        {"play", jouer},
        {"settings", parametres},
        {"quitter", quitter}
    };
    int selected_item = 0;
    int item_count = sizeof(menu_items) / sizeof(menu_item_t);
    sfRectangleShape *rect = create_rectangle();
    sfClock *clock = sfClock_create();

    while (sfRenderWindow_isOpen(window)) {
        handle_events(window, &selected_item, item_count, menu_items, game_info);
        blink(clock, rect);
        draw_menu(window, rect, &selected_item);
    }
}
