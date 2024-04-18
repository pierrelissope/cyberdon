/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** event
*/

#include "entity.h"

int handle_event(game_t *game, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(game->window, event)) {
        move_entity(&(game->player), event, &(game->world));
        if (event->type == sfEvtClosed)
            return sfEvtClosed;
    }
    return sfEvtCount;
}
