/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** event handling for fighting
*/

#include "fight_entity.h"
#include "fight_macros.h"
#include "struct.h"
#include "fight.h"
#include "fight_actions.h"
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <stdbool.h>

void pick_attack(fighter_entity_t *fighter)
{
    if (fighter->state == IDLE) {
        if (sfKeyboard_isKeyPressed(sfKeyUp))
            change_state(fighter, ATTACK_UP);
        if (sfKeyboard_isKeyPressed(sfKeyDown))
            change_state(fighter, ATTACK_DOWN);
        if (!sfKeyboard_isKeyPressed(sfKeyUp) &&
            !sfKeyboard_isKeyPressed(sfKeyUp))
            change_state(fighter, ATTACK);
    }
    if (fighter->state == JUMP)
        change_state(fighter, ATTACK_JUMP);
    if (fighter->state == CROUCH)
        change_state(fighter, ATTACK_CROUCH);
}

int handle_fight_event(game_t *game, fight_t *fight, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(game->window, event)) {
        if (event->type == sfEvtClosed)
            return sfEvtClosed;
        if (sfEvtKeyPressed == event->type) {
            if (sfKeyboard_isKeyPressed(sfKeySpace)) {
                change_state(fight->player, JUMP);
            }
            if (sfKeyboard_isKeyPressed(sfKeyX)) {
                pick_attack(fight->player);
            }
            if (FIGHT_ACTIONS[fight->player->state] != NULL)
                FIGHT_ACTIONS[fight->player->state](fight->player);
        }
   }
    return sfEvtCount;
}
