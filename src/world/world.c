/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#include "world.h"
#include "entity.h"
#include "myutils.h"

world_t init_world(void)
{
    world_t world = {0};

    return world;
}

static void stack_chests(linked_objects_t ***array, world_t *world)
{
    sfFloatRect bounds = {0};
    linked_objects_t *object = NULL;
    float bottom = 0;

    for (int i = 0; world->chests && world->chests[i]; i++) {
        bounds = sfSprite_getGlobalBounds(world->chests[i]->sprite);
        bottom = bounds.top + bounds.height;
        bounds.top = bottom - 60;
        object = calloc(1, sizeof(linked_objects_t));
        object->object = world->chests[i];
        object->bounds = bounds;
        bottom = bounds.top + bounds.height;
        object->fct = draw_chest;
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
    stack_chests(&stack, world);
    quicksort(stack, 0, my_arraylen((void **)stack) - 1);
    for (int i = 0; stack && stack[i]; i++)
        stack[i]->fct(stack[i]->object, window);
    free(stack);
    free(floor_stack);
}
