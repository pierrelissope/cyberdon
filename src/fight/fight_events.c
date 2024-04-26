/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** event handling for fighting
*/

#include "fight_entity.h"
#include "struct.h"

int handle_fight_event(game_t *game, fight_t *fight, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(game->window, event)) {
        if (event->type == sfEvtClosed)
            return sfEvtClosed;
    }
    return sfEvtCount;
}
