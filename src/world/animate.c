/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** animate
*/

#include "entity.h"
#include "world.h"

static void animate_block(block_t *block)
{
    int now = sfTime_asMilliseconds(sfClock_getElapsedTime(block->clock));
    int last_update = sfTime_asMilliseconds(block->last_animation_update);
    sfIntRect frame_rect = {0};

    block->current_frame %= block->frame_nb;
    frame_rect = (sfIntRect){
        (int)(block->current_frame * block->sprite_rect.width), 0,
        block->sprite_rect.width, block->sprite_rect.height};
    if (now - last_update > BLOCK_ANIMATION_COOLDOWN) {
        sfSprite_setTextureRect(
            block->sprite, frame_rect);
        block->current_frame += 1;
        block->last_animation_update = sfClock_getElapsedTime(block->clock);
    }
}

void animate_world(world_t *world)
{
    for (int i = 0; world->floor && world->floor[i]; i++)
        if (world->floor[i]->frame_nb > 1)
            animate_block(world->floor[i]);
    for (int i = 0; world->walls && world->walls[i]; i++)
        if (world->walls[i]->frame_nb > 1)
            animate_block(world->walls[i]);
}
