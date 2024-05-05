/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** movement actions func
*/

#include "fight.h"
#include "struct.h"
#include <stdbool.h>

void jump(fighter_entity_t *entity)
{
    annimation_t *current = entity->annimation_sheets[entity->state];

    if (current->current_frame < current->n_of_frames / 2) {
        entity->velocity.y = -14;
    }
    entity->annimation_lock = true;
}

void idle(fighter_entity_t *entity)
{
    entity->velocity.x = 0;
}

void crouch(fighter_entity_t *entity)
{
    entity->velocity.x = 0;
}

void backward(fighter_entity_t *entity)
{
    entity->velocity.x = 4;
}

void forward(fighter_entity_t *entity)
{
    entity->velocity.x = -4;
}
