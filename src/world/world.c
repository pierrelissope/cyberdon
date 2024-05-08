/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#include "world.h"
#include "entity.h"

const int COLLISION_OPACITY = 145;
const int TILE_SIZE = 50;

world_t init_world(void)
{
    world_t world = {0};

    return world;
}

void draw_wall(void *wall, sfRenderWindow *window)
{
    block_t *new_wall = wall;

    sfRenderWindow_drawSprite(window, new_wall->sprite, NULL);
}

static void stack_walls(linked_objects_t ***array, world_t *world)
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

static void stack_entities(linked_objects_t ***array, world_t *world)
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

static void stack_player(linked_objects_t ***array, physical_entity_t *player)
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

void draw_teleporters(void *entity, sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, ((teleporter_t *)entity)->sprite, NULL);
}

void draw_floor(void *entity, sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, ((block_t *)entity)->sprite, NULL);
}

static void stack_floors(linked_objects_t ***array, world_t *world)
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

static void stack_teleporters(linked_objects_t ***array, world_t *world)
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

void draw_level(sfRenderWindow *window, world_t *world,
    physical_entity_t *player)
{
    linked_objects_t **stack = NULL;
    linked_objects_t **floor_stack = NULL;

    stack_teleporters(&floor_stack, world);
    stack_floors(&floor_stack, world);
    quicksort(floor_stack, 0, my_arraylen((void **)floor_stack) - 1);
    for (int i = 0; floor_stack && floor_stack[i]; i++)
        floor_stack[i]->fct(floor_stack[i]->object, window);
    stack_walls(&stack, world);
    stack_entities(&stack, world);
    stack_player(&stack, player);
    quicksort(stack, 0, my_arraylen((void **)stack) - 1);
    for (int i = 0; stack && stack[i]; i++)
        stack[i]->fct(stack[i]->object, window);
    free(stack);
    free(floor_stack);
}
