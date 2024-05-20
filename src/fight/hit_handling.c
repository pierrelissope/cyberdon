/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** hit handling
*/

#include "fight.h"
#include <SFML/System/Clock.h>
#include <stdbool.h>

void hit(fighter_entity_t *entity)
{
    entity->annimation_lock = true;
    entity->velocity.x = 0;
    entity->hit = true;
}
