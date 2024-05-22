/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** load_level
*/

#include <string.h>

#include "myutils.h"
#include "world.h"
#include "inventory.h"

static void init_level(world_t *world, char *level,
    game_t *game)
{
    char *destination_level = strdup(level);

    destroy_world(world);
    *world = (world_t){0};
    world->current_level = destination_level;
    world->teleporters = load_level_teleporters(
        destination_level, game->tiles_dict);
    world->entities = load_level_entities(
        destination_level, game->sheets_dict);
    world->chests = load_level_chests(destination_level,
        &game->inventories, game);
}

int load_level(game_t *game, char *level, dict_t *tiles)
{
    char **floor = load_floor(level);
    char **walls = load_walls(level);

    if (floor == NULL || walls == NULL)
        return EXIT_FAILURE;
    append_ptr((void ***)&game->visited_levels, strdup(level), NULL);
    init_level(&game->world, level, game);
    for (int y = 0; floor[y]; ++y)
        if (parse_floor_line(floor, &game->world, y, tiles) == EXIT_FAILURE)
            return EXIT_FAILURE;
    for (int y = 0; walls[y]; ++y)
        if (parse_walls_line(walls, &game->world, y, tiles) == EXIT_FAILURE)
            return EXIT_FAILURE;
    free_str_array(floor);
    free_str_array(walls);
    return EXIT_SUCCESS;
}
