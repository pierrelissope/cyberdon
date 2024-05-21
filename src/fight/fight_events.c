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

static fighter_state_t pick_attack(fighter_entity_t *fighter,
    fighter_state_t action)
{
    if (action == ATTACK && fighter->state == JUMP)
        return ATTACK_JUMP;
    if (action == ATTACK && fighter->looking_down)
        return ATTACK_DOWN;
    if (action == ATTACK && fighter->looking_up)
        return ATTACK_UP;
    if (action == ATTACK && fighter->crouching)
        return ATTACK_CROUCH;
    return action;
}

static int handle_pre_fight_event(game_t *, fight_t *fight,
    fighter_state_t *action)
{
    fight->player->looking_down = false;
    fight->player->looking_up = false;
    fight->player->crouching = false;
    fight->player->velocity.x = 0;
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        fight->player->velocity.x = 10;
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        fight->player->velocity.x = -10;
    if (sfKeyboard_isKeyPressed(sfKeyUp))
        fight->player->looking_up = true;
    if (sfKeyboard_isKeyPressed(sfKeyDown))
        fight->player->looking_down = true;
    if (sfKeyboard_isKeyPressed(sfKeyC)) {
        *action = CROUCH;
        fight->player->crouching = true;
    }
    return 0;
}

static fighter_state_t pick_walking_annimation(fighter_entity_t *entity,
    int action)
{
    if (action == IDLE && entity->velocity.x != 0) {
        if (entity->velocity.x > 0)
            return FORWARD;
        if (entity->velocity.x < 0)
            return BACKWARD;
    }
    return action;
}

static void handle_ai_actions(fight_t *fight)
{
    fighter_state_t action = IDLE;

    fight->npc->looking_down = false;
    fight->npc->looking_up = false;
    fight->npc->crouching = false;
    fight->npc->velocity.x = 0;
    ai_movement_pick(fight);
    action = ai_action_pick(fight);
    action = pick_attack(fight->npc, action);
    action = pick_walking_annimation(fight->npc, action);
    change_state(fight->npc, action);
    if (FIGHT_ACTIONS[fight->npc->state] != NULL)
        FIGHT_ACTIONS[fight->npc->state](fight->npc);
}

static void handle_player_actions(fight_t *fight, fighter_state_t action)
{
    action = pick_attack(fight->player, action);
    action = pick_walking_annimation(fight->player, action);
    change_state(fight->player, action);
    if (FIGHT_ACTIONS[fight->player->state] != NULL)
        FIGHT_ACTIONS[fight->player->state](fight->player);
}

static int key_events(fight_t *fight)
{
    fighter_state_t action = IDLE;

<<<<<<< HEAD
=======
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        fight->debug_mode = !fight->debug_mode;
    }
>>>>>>> 0075cc99a01a5a1ead9cb38460c2a65508c62303
    if (sfKeyboard_isKeyPressed(sfKeyX)) {
        if (decrease_stamina(fight->player, 5))
            action = ATTACK;
    }
    if (sfKeyboard_isKeyPressed(sfKeySpace) &&
        fight->player->velocity.y == 0) {
        if (decrease_stamina(fight->player, 5))
            action = JUMP;
    }
    return action;
}

int handle_fight_event(game_t *game, fight_t *fight, sfEvent *event)
{
    fighter_state_t action = IDLE;

    handle_pre_fight_event(game, fight, &action);
    while (sfRenderWindow_pollEvent(game->window, event)) {
        if (event->type == sfEvtClosed)
            return sfEvtClosed;
        if (event->type == sfEvtKeyPressed) {
            action = key_events(fight);
        }
    }
    handle_player_actions(fight, action);
    handle_ai_actions(fight);
    return sfEvtCount;
}
