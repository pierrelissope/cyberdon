/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** event
*/

#include "entity.h"
#include "fight.h"
#include <SFML/Window/Keyboard.h>

int handle_event(game_t *game, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(game->window, event)) {
        if (event->type == sfEvtClosed)
            return sfEvtClosed;
        if (sfKeyboard_isKeyPressed(sfKeyF)) {
            test(game);
            return sfEvtClosed;
        }
    }
    return sfEvtCount;
}
