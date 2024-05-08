/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** destroy
*/

#include "world.h"
#include "entity.h"

void destroy_block(block_t *block)
{
    if (block->sprite != NULL)
        sfSprite_destroy(block->sprite);
    if (block->rect != NULL)
        sfRectangleShape_destroy(block->rect);
    if (block->clock != NULL)
        sfClock_destroy(block->clock);
}

void destroy_teleporter(teleporter_t *teleporter)
{
    if (teleporter->sprite != NULL)
        sfSprite_destroy(teleporter->sprite);
    if (teleporter->rect != NULL)
        sfRectangleShape_destroy(teleporter->rect);
    if (teleporter->destination_level != NULL)
        free(teleporter->destination_level);
}

world_t destroy_world(world_t *world)
{
    for (int i = 0; world->floor != NULL && world->floor[i] != NULL; ++i)
        destroy_block(world->floor[i]);
    for (int i = 0; world->walls != NULL && world->walls[i] != NULL; ++i)
        destroy_block(world->walls[i]);
    for (int i = 0; world->teleporters != NULL &&
        world->teleporters[i] != NULL; ++i)
        destroy_teleporter(world->teleporters[i]);
    for (int i = 0; world->entities != NULL &&
        world->entities[i] != NULL; ++i)
        destroy_entity(world->entities[i]);
    if (world->current_level != NULL)
        free(world->current_level);
    return (world_t){0};
}
