/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** movement
*/

#include "fight.h"
#include "fight_entity.h"
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>

static void change_state(fighter_entity_t *entity, fighter_state_t new_state)
{
    if (entity->state != new_state) {
        entity->annimation_sheets[entity->state]->current_frame = 0;
        entity->annimation_sheets[entity->state]->text_rec.left = 0;
        sfClock_restart(entity->clock);
        entity->state = new_state;
    }
}

static void from_movement(fighter_entity_t *entity)
{
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        change_state(entity, FORWARD);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        change_state(entity, BACKWARD);
    }
    if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        change_state(entity, JUMP);
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        change_state(entity, CROUCH);
    }
}

static void update_player_state(fighter_entity_t *entity)
{
    if (!sfKeyboard_isKeyPressed(sfKeyDown) &&
        !sfKeyboard_isKeyPressed(sfKeyUp) &&
        !sfKeyboard_isKeyPressed(sfKeyLeft) &&
        !sfKeyboard_isKeyPressed(sfKeyRight))
        change_state(entity, IDLE);
    else
        from_movement(entity);
}

void update_fight(fight_t *fight)
{
    update_player_state(fight->player);
    annimate_fighter(fight->player);
    annimate_fighter(fight->npc);
}
