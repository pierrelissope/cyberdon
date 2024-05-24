/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-tanvir-mahtab.miah
** File description:
** draw_menu
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include "menu.h"
#include "game.h"
#include <stdbool.h>

static void init_ressouces(sfFont **font, sfVector2f *jouer_text_pos,
    sfVector2f *param_text_pos, sfVector2f *quitter_text_pos)
{
    *font = sfFont_createFromFile("assets/font/font.ttf");
    *jouer_text_pos = (sfVector2f){900, 450};
    *param_text_pos = (sfVector2f){900, 550};
    *quitter_text_pos = (sfVector2f){900, 650};
}

static void create_menu_texts(sfText **texts,
    sfFont *font, int selected_item, menu_item_t *ptr_fct)
{
    sfVector2f positions[] = {{900, 450}, {900, 550}, {900, 650}};

    for (int i = 0; i < 3; ++i) {
        texts[i] = create_text_mh(ptr_fct[i].selected_item, positions[i],
            font, selected_item == i);
    }
}

static void update_selected_item(sfRenderWindow *window,
    int *selected_item, sfText **texts)
{
    for (int i = 0; i < 3; ++i) {
        if (my_hover(window, texts[i])) {
            *selected_item = i;
        }
    }
}

static void draw_menu_texts(sfRenderWindow *window, sfText **texts)
{
    for (int i = 0; i < 3; ++i) {
        sfRenderWindow_drawText(window, texts[i], NULL);
    }
}

static void draw_selection_rectangle(sfRenderWindow *window,
    sfRectangleShape *rect, sfText *selected_text)
{
    sfFloatRect text_rect = sfText_getGlobalBounds(selected_text);
    sfVector2f rect_pos = {text_rect.left - 10, text_rect.top - 5};
    sfVector2f rect_size = {text_rect.width + 20, text_rect.height + 10};

    sfRectangleShape_setPosition(rect, rect_pos);
    sfRectangleShape_setSize(rect, rect_size);
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
}

static void cleanup_resources(sfFont *font, sfText **texts)
{
    for (int i = 0; i < 3; ++i) {
        sfText_destroy(texts[i]);
    }
    sfFont_destroy(font);
}

void draw_menu_image(sfRenderWindow *window, int specifier)
{
    sfTexture *bg;
    sfSprite *bg_sprite = sfSprite_create();

    if (specifier == 0)
        bg = sfTexture_createFromFile("./assets/bg.png", NULL);
    else
        bg = sfTexture_createFromFile("./assets/bg2.png", NULL);
    sfSprite_setTexture(bg_sprite, bg, sfTrue);
    sfRenderWindow_drawSprite(window, bg_sprite, NULL);
}

void draw_menu(sfRenderWindow *window,
    sfRectangleShape *rect, int *selected_item, menu_item_t *ptr_fct)
{
    sfFont *font;
    sfVector2f jouer_text_pos;
    sfVector2f param_text_pos;
    sfVector2f quitter_text_pos;
    sfText *texts[3];

    init_ressouces(&font, &jouer_text_pos, &param_text_pos, &quitter_text_pos);
    create_menu_texts(texts, font, *selected_item, ptr_fct);
    update_selected_item(window, selected_item, texts);
    draw_menu_texts(window, texts);
    draw_selection_rectangle(window, rect, texts[*selected_item]);
    sfRenderWindow_display(window);
    cleanup_resources(font, texts);
}
