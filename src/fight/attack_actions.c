/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** movement actions func
*/

#include "fight.h"

void attack_up(fighter_entity_t *entity)
{
    entity->velocity.x = 0;
    entity->annimation_lock = true;
}

void attack_down(fighter_entity_t *entity)
{
    entity->velocity.x = 0;
    entity->annimation_lock = true;
}

void attack(fighter_entity_t *entity)
{
    entity->velocity.x = 0;
    entity->annimation_lock = true;
}

void attack_crouch(fighter_entity_t *entity)
{
    entity->velocity.x = 0;
    entity->annimation_lock = true;
}

void attack_jump(fighter_entity_t *entity)
{
    entity->velocity.x = 0;
    entity->annimation_lock = true;
}
