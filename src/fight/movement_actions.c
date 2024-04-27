/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** movement actions func
*/

#include "fight.h"
#include "struct.h"

void jump(fighter_entity_t *entity)
{
    annimation_t *current = entity->annimation_sheets[entity->state];

    if (current->current_frame > current->n_of_frames / 2)
        entity->velocity.y = 3;
    else
        entity->velocity.y = -5;
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
