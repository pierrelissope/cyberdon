/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** view
*/

#include "entity.h"
#include "view.h"

static const float CINEMATIC_TIME = 7;

sfView *init_player_view(void)
{
    sfFloatRect view_rect = {0, 0, 1920, 1080};
    sfView *player_view = sfView_createFromRect(view_rect);

    if (!player_view)
        return NULL;
    sfView_zoom(player_view, 0.70);
    return player_view;            
}

void center_view(sfView *view, sfRectangleShape *player_rect, game_t *game)
{
    sfFloatRect player_bounds = sfRectangleShape_getGlobalBounds(player_rect);
    sfVector2f center = {
        (player_bounds.left) / 50,
        (player_bounds.top) / 50,
    };

    if (game->game_state != IN_CINEMATIC) {
        center = isom_pos_converter(center);
        sfView_setCenter(view, center);
    } else {
        game->view_pos.x += 2;
        game->view_pos.y += 2;
        sfView_setCenter(view, game->view_pos);
        if (sfTime_asSeconds(sfClock_getElapsedTime(game->clock)) > CINEMATIC_TIME) {
            game->game_state = IN_GAME;
            sfView_zoom(game->player_view, 1 / 1.5);
            game->view_pos = (sfVector2f){0, 0};
        }
    }
}
