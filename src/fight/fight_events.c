/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** event handling for fighting
*/

#include "fight_entity.h"
#include "struct.h"
#include "fight.h"
#include "fight_actions.h"
#include <SFML/Window/Event.h>
#include <stdbool.h>

int handle_fight_event(game_t *game, fight_t *fight, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(game->window, event)) {
        if (event->type == sfEvtClosed)
            return sfEvtClosed;
        if (sfEvtKeyPressed == event->type) {
            if (FIGHT_ACTIONS[fight->player->state] != NULL)
                FIGHT_ACTIONS[fight->player->state](fight->player);
        }
   }
    return sfEvtCount;
}
