/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** event
*/

#include "entity.h"
#include <SFML/Window/Keyboard.h>

int handle_event(game_t *game, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(game->window, event)) {
        if (event->type == sfEvtClosed)
            return sfEvtClosed;
        if (sfKeyboard_isKeyPressed(sfKeyEscape) && sfTime_asSeconds(
            sfClock_getElapsedTime(game->status.escape_clock)) > 0.2) {
            sfClock_restart(game->status.escape_clock);
            game->game_state = IN_MENU;
        }
    }
    return sfEvtCount;
}

int handle_inventory_event(sfRenderWindow *window, sfEvent *event,
    game_t *game)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return sfEvtClosed;
        }
        if (sfKeyboard_isKeyPressed(sfKeyEscape) && sfTime_asSeconds(
            sfClock_getElapsedTime(game->status.escape_clock)) > 0.2) {
            sfClock_restart(game->status.escape_clock);
            return sfEvtClosed;
        }
    }
    return sfEvtCount;
}
