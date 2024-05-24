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
