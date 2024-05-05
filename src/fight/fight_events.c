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
#include <SFML/Config.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <stdbool.h>

fighter_state_t pick_attack(fighter_entity_t *fighter, fighter_state_t action)
{
    if (action == ATTACK && fighter->state == JUMP)
        return ATTACK_JUMP;
    if (action == ATTACK && fighter->looking_down)
        return ATTACK_DOWN;
    if (action == ATTACK && fighter->looking_up)
        return ATTACK_UP;
    return action;
}

int handle_pre_fight_event(game_t *, fight_t *fight)
{
    fight->player->looking_down = false;
    fight->player->looking_up = false;
    fight->player->velocity.x = 0;
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        fight->player->velocity.x = 4;
    }
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        fight->player->velocity.x = -4;
    }
    if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        fight->player->looking_up = true;
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        fight->player->looking_down = true;
    }
    return 0;
}

bool pick_walking_annimation(fighter_entity_t *entity)
{
    if (entity->state == IDLE && entity->velocity.x != 0) {
        if (entity->velocity.x > 0)
            change_state(entity, BACKWARD);
        if (entity->velocity.x < 0)
            change_state(entity, FORWARD);
        return true;
    }
    return false;
}

int handle_fight_event(game_t *game, fight_t *fight, sfEvent *event)
{
    fighter_state_t action = IDLE;

    handle_pre_fight_event(game, fight);
    while (sfRenderWindow_pollEvent(game->window, event)) {
        if (event->type == sfEvtClosed)
            return sfEvtClosed;
        if (sfEvtKeyPressed == event->type) {
            if (sfKeyboard_isKeyPressed(sfKeyX))
                action = ATTACK;
            if (sfKeyboard_isKeyPressed(sfKeySpace) && fight->player->velocity.y == 0)
                action = JUMP;
        }
    }
    action = pick_attack(fight->player, action);
    pick_walking_annimation(fight->player);
    change_state(fight->player, action);
    if (FIGHT_ACTIONS[fight->player->state] != NULL)
        FIGHT_ACTIONS[fight->player->state](fight->player);
    return sfEvtCount;
}
