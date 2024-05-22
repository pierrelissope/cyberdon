/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** destroy
*/

#include "entity.h"
#include "dict.h"
#include "inventory.h"

void destroy_spritesheet(void *data)
{
    sfSprite *sprite = data;

    sfSprite_destroy(sprite);
}

void destroy_entity(physical_entity_t *entity)
{
    if (entity == NULL)
        return;
    destroy_inventory(entity->inventory);
    sfRectangleShape_destroy(entity->rect);
    sfClock_destroy(entity->clock);
    destroy_stats(&entity->stats);
    dict_destroy(entity->sprite_sheets, destroy_spritesheet);
    sfFont_destroy(entity->font);
    free(entity);
}
