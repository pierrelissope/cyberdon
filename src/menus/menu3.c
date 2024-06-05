/*
** EPITECH PROJECT, 2024
** RPG22
** File description:
** menu3
*/

#include <SFML/Graphics.h>
#include <SFML/Window/Event.h>
#include <stdio.h>
#include <stdbool.h>
#include "struct.h"
#include "mh_menu.h"
#include "game.h"
#include "xp.h"
#include "basics.h"

void draw_button(sfRenderWindow *window, button_t button)
{
    sfRenderWindow_drawRectangleShape(window, button.shape, NULL);
    sfRenderWindow_drawText(window, button.text, NULL);
    sfRenderWindow_drawText(window, button.desc, NULL);
    if (button.sprite != NULL)
        sfRenderWindow_drawSprite(window, button.sprite, NULL);
}

void destroy_button(button_t button)
{
    sfRectangleShape_destroy(button.shape);
    sfText_destroy(button.text);
    sfText_destroy(button.desc);
}

sfRenderWindow *init_window()
{
    sfVideoMode mode = {1920, 1080, 32};

    return sfRenderWindow_create(mode, "Menu", sfResize | sfClose, NULL);
}

sfSprite *load_background(const char *image_path)
{
    sfTexture *texture = sfTexture_createFromFile(image_path, NULL);
    sfSprite *sprite = sfSprite_create();

    sfSprite_setTexture(sprite, texture, sfTrue);
    return sprite;
}

sfText *create_hover_text(sfFont *font)
{
    sfText *text = sfText_create();

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 90);
    sfText_setPosition(text, (sfVector2f){123, 866});
    sfText_setFillColor(text, sfWhite);
    return text;
}

void init_buttons(button_t *buttons, sfFont *font)
{
    buttons[0] = create_button(font,
        &BUTTON_INIT[PLAY], "assets/picto/fist.png");
    buttons[1] = create_button(font,
        &BUTTON_INIT[NEW_GAME], "assets/picto/new.png");
    buttons[2] = create_button(font,
        &BUTTON_INIT[LOAD], "assets/picto/load.png");
    buttons[3] = create_button(font,
        &BUTTON_INIT[LEAVE], "assets/picto/exit.png");
    buttons[4] = create_button(font,
        &BUTTON_INIT[SETTINGS], "assets/picto/settings.png");
}
