/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** menu
*/

#include <SFML/Graphics.h>
#include <stdbool.h>
#include "mh_menu.h"

bool my_hover(sfRenderWindow *window, sfText *text)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfFloatRect text_bounds = sfText_getGlobalBounds(text);

    return sfFloatRect_contains(&text_bounds, mouse_pos.x, mouse_pos.y);
}

sfRectangleShape *create_rectangle(void)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setFillColor(rect, sfTransparent);
    sfRectangleShape_setOutlineColor(rect, sfRed);
    sfRectangleShape_setOutlineThickness(rect, 2);
    return rect;
}

void clear_menu(sfText *param_text, sfText *sound_text,
    sfText *keybind_text, sfText *resize_text)
{
    sfText_destroy(param_text);
    sfText_destroy(sound_text);
    sfText_destroy(resize_text);
    sfText_destroy(keybind_text);
}
