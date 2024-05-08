/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** load_level
*/

#include <string.h>

#include "myutils.h"
#include "world.h"

static void init_level(world_t *world, char *level,
    dict_t *tiles, dict_t *sheets_dict)
{
    char *destination_level = strdup(level);

    destroy_world(world);
    *world = (world_t){0};
    world->current_level = destination_level;
    world->teleporters = load_level_teleporters(destination_level, tiles);
    world->entities = load_level_entities(destination_level, sheets_dict);
}

int load_level(game_t *game, char *level, dict_t *tiles, dict_t *sheets_dict)
{
    char **floor = load_floor(level);
    char **walls = load_walls(level);

    if (floor == NULL || walls == NULL)
        return EXIT_FAILURE;
    append_ptr((void ***)&game->visited_levels, strdup(level), NULL);
    init_level(&game->world, level, tiles, sheets_dict);
    for (int y = 0; floor[y]; ++y)
        if (parse_floor_line(floor, &game->world, y, tiles) == EXIT_FAILURE)
            return EXIT_FAILURE;
    for (int y = 0; walls[y]; ++y)
        if (parse_walls_line(walls, &game->world, y, tiles) == EXIT_FAILURE)
            return EXIT_FAILURE;
    free_str_array(floor);
    return EXIT_SUCCESS;
}
