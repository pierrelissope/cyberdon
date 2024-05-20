/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** hit handling
*/

#include "fight.h"
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <stdbool.h>
#include <stdio.h>

void hit(fighter_entity_t *entity)
{
    entity->annimation_lock = true;
    entity->velocity.x = 0;
    entity->hit = true;
}


void on_hit(fighter_entity_t *entity)
{
    change_state(entity, HIT);
    entity->annimation_lock = true;
    sfClock_restart(entity->i_counter);
    printf("HIT\n");
}
