/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** stacking
*/

#include "world.h"
#include "entity.h"
#include "myutils.h"

static const int COLLISION_OPACITY = 145;

void stack_walls(linked_objects_t ***array, world_t *world)
{
    sfFloatRect bounds = {0};
    linked_objects_t *object = NULL;
    float bottom = 0;

    for (int i = 0; world->walls && world->walls[i]; i++) {
        bounds = sfSprite_getGlobalBounds(world->walls[i]->sprite);
        bottom = bounds.top + bounds.height;
        bounds.top = bottom - 105;
        object = calloc(1, sizeof(linked_objects_t));
        object->object = world->walls[i];
        object->bounds = bounds;
        object->fct = draw_wall;
        append_ptr((void ***)array, object, NULL);
    }
}

void stack_entities(linked_objects_t ***array, world_t *world)
{
    sfFloatRect bounds = {0};
    linked_objects_t *object = NULL;
    sfVector2f center = {0};

    for (int i = 0; world->entities && world->entities[i]; i++) {
        bounds = sfRectangleShape_getGlobalBounds(world->entities[i]->rect);
        center = (sfVector2f){
            (bounds.left) / 50, (bounds.top) / 50};
        center = isom_pos_converter(center);
        bounds.left = center.x;
        bounds.top = center.y;
        bounds.top -= COLLISION_OPACITY;
        object = calloc(1, sizeof(linked_objects_t));
        object->object = world->entities[i];
        object->bounds = bounds;
        object->fct = draw_entity;
        append_ptr((void ***)array, object, NULL);
    }
}

void stack_player(linked_objects_t ***array, physical_entity_t *player)
{
    linked_objects_t *object = NULL;
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(player->rect);
    sfVector2f center = {
        (bounds.left) / 50,
        (bounds.top) / 50,
    };

    center = isom_pos_converter(center);
    bounds.left = center.x;
    bounds.top = center.y;
    bounds.top -= COLLISION_OPACITY;
    object = calloc(1, sizeof(linked_objects_t));
    object->object = player;
    object->bounds = bounds;
    object->fct = draw_entity;
    append_ptr((void ***)array, object, NULL);
}

void stack_floors(linked_objects_t ***array, world_t *world)
{
    sfFloatRect bounds = {0};
    linked_objects_t *object = NULL;

    for (int i = 0; world->floor && world->floor[i]; i++) {
        bounds = sfSprite_getGlobalBounds(world->floor[i]->sprite);
        object = calloc(1, sizeof(linked_objects_t));
        object->object = world->floor[i];
        object->bounds = bounds;
        object->fct = draw_floor;
        append_ptr((void ***)array, object, NULL);
    }
}

void stack_teleporters(linked_objects_t ***array, world_t *world)
{
    sfFloatRect bounds = {0};
    linked_objects_t *object = NULL;

    for (int i = 0; world->teleporters && world->teleporters[i]; i++) {
        bounds = sfSprite_getGlobalBounds(world->teleporters[i]->sprite);
        object = calloc(1, sizeof(linked_objects_t));
        object->object = world->teleporters[i];
        object->priority = true;
        object->bounds = bounds;
        object->fct = draw_teleporters;
        append_ptr((void ***)array, object, NULL);
    }
}
