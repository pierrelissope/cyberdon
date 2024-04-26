/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** view
*/

#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/View.h>
#include "view.h"
#include "utils.h"

sfView *init_player_view(void)
{
    sfFloatRect view_rect = {0, 0, 1920, 1080};
    sfView *player_view = sfView_createFromRect(view_rect);

    if (!player_view)
        return NULL;
    sfView_zoom(player_view, 0.70);
    return player_view;
}

void center_view(sfView *view, sfRectangleShape *player_rect)
{
    sfFloatRect player_bounds = sfRectangleShape_getGlobalBounds(player_rect);
    sfVector2f center = {
        (player_bounds.left) / 50,
        (player_bounds.top) / 50,
    };
    center = isom_pos_converter(center);
    sfView_setCenter(view, center);
}

sfView *init_fight_view(void)
{
    sfFloatRect view_rect = {0, 0, 1920, 1080};
    sfView *view = sfView_createFromRect(view_rect);

    return view;
}
