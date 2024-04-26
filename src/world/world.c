/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#include "world.h"
#include "entity.h"

const int COLLISION_OPACITY = 60;

world_t init_world(void)
{
    world_t world = {0};

    return world;
}

int load_level(world_t *world, int level, dict_t *tiles, dict_t *sheets_dict)
{
    char **floor = load_floor(level);
    char **walls = load_walls(level);

    world->entities = load_level_entities(level, sheets_dict);
    if (!floor || !walls) {
        freef("%t%t", floor, walls);
        return EXIT_FAILURE;
    }
    for (int y = 0; floor[y]; y++)
        if (parse_floor_line(floor, world, y, tiles) == EXIT_FAILURE) {
            freef("%t%t", floor, walls);
            return EXIT_FAILURE;
        }
    for (int y = 0; walls[y]; y++)
        if (parse_walls_line(walls, world, y, tiles) == EXIT_FAILURE) {
            freef("%t%t", floor, walls);
            return EXIT_FAILURE;
        }
    free_str_array(floor);
    return 0;
}

static void draw_wall(void *wall, sfRenderWindow *window)
{
    block_t *new_wall = wall;

    sfRenderWindow_drawSprite(window, new_wall->sprite, NULL);
    //sfRenderWindow_drawRectangleShape(window, new_wall->rect, NULL);
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

    for (int i = 0; world->entities && world->entities[i]; i++) {
        bounds = sfSprite_getGlobalBounds(
            world->entities[i]->current_sprite_sheet);
        bounds.top += COLLISION_OPACITY;
        object = calloc(1, sizeof(linked_objects_t));
        object->object = world->entities[i];
        object->bounds = bounds;
        object->fct = draw_entity;
        append_ptr((void ***)array, object, NULL);
    }
}

static void stack_player(linked_objects_t ***array, physical_entity_t *player)
{
    sfFloatRect bounds = {0};
    linked_objects_t *object = NULL;

    bounds = sfSprite_getGlobalBounds(player->current_sprite_sheet);
    bounds.top += COLLISION_OPACITY;
    object = calloc(1, sizeof(linked_objects_t));
    object->object = player;
    object->bounds = bounds;
    object->fct = draw_entity;
    append_ptr((void ***)array, object, NULL);
}

void draw_level(sfRenderWindow *window, world_t *world,
    physical_entity_t *player)
{
    linked_objects_t **stack = NULL;

    for (int i = 0; world->floor && world->floor[i]; i++) {
        sfRenderWindow_drawSprite(window, world->floor[i]->sprite, NULL);
        //sfRenderWindow_drawRectangleShape(window, world->floor[i]->rect, NULL);
    }
    stack_walls(&stack, world);
    stack_entities(&stack, world);
    stack_player(&stack, player);
    quicksort(stack, 0, my_arraylen((void **)stack) - 1);
    for (int i = 0; stack && stack[i]; i++)
        stack[i]->fct(stack[i]->object, window);
    free(stack);
}
