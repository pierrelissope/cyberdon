/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** destroy
*/

#include "entity.h"

typedef void (*custom_destroy_t)(void *);

void destroy_entity(physical_entity_t *entity)
{
    if (entity->rect)
        sfRectangleShape_destroy(entity->rect);
    if (entity->clock)
        sfClock_destroy(entity->clock);
}
