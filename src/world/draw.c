/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** draw
*/

#include "world.h"
#include "entity.h"
#include "myutils.h"

void draw_teleporters(void *entity, sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, ((teleporter_t *)entity)->sprite, NULL);
}

void draw_wall(void *wall, sfRenderWindow *window)
{
    block_t *new_wall = wall;

    sfRenderWindow_drawSprite(window, new_wall->sprite, NULL);
}

void draw_floor(void *entity, sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, ((block_t *)entity)->sprite, NULL);
}

void draw_chest(void *chest, sfRenderWindow *window)
{
    chest_t *new_chest = chest;

    sfRenderWindow_drawSprite(window, new_chest->sprite, NULL);
}
