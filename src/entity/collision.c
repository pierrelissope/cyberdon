/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** collision
*/

#include "entity.h"

static bool check_still_collide(sfFloatRect *rect, world_t *world, float x)
{
    bool trigger = false;
    sfFloatRect floor = {0};

    for (float y = rect->top; y < rect->top + rect->height; y++) {
        trigger = false;
        for (int i = 0; world->floor && world->floor[i]; i++) {
            floor = sfRectangleShape_getGlobalBounds(world->floor[i]->rect);
            trigger = (sfFloatRect_contains(&floor, x, y) ? true : trigger);
        }
        if (trigger == false)
            return false;
    }
    return true;
}

bool still_collide(sfFloatRect *rect, world_t *world)
{
    for (float x = rect->left; x < rect->left + rect->width; x++) {
        if (check_still_collide(rect, world, x) == false)
            return false;
    }
    return true;
}

bool dont_collide(sfFloatRect *rect, world_t *world)
{
    sfFloatRect walls = {0};

    for (int i = 0; world->walls && world->walls[i]; i++) {
        walls = sfRectangleShape_getGlobalBounds(world->walls[i]->rect);
        if (sfFloatRect_intersects(rect, &walls, NULL))
            return false;
    }
    return true;
}
