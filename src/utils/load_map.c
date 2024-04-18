/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** load_map
*/

#include "basics.h"

const char *LEVELS_MAP_PATHS = "./levels/";

char **load_floor(int level)
{
    char *level_str = my_itoa(level);
    char *buffer = NULL;
    char **array = NULL;
    char *map_path = concat_mem((char *)LEVELS_MAP_PATHS, level_str, "/floor");

    if (!map_path) {
        freef("%a%a%a", map_path, level_str, buffer);
        return NULL;
    }
    buffer = open_file(map_path);
    if (!buffer) {
        freef("%a%a%a", map_path, level_str, buffer);
        return NULL;
    }
    array = my_str_to_all_array(buffer, "\n");
    freef("%a%a%a", map_path, level_str, buffer);
    return array;
}

char **load_walls(int level)
{
    char *level_str = my_itoa(level);
    char *buffer = NULL;
    char **array = NULL;
    char *map_path = concat_mem((char *)LEVELS_MAP_PATHS, level_str, "/walls");

    if (!map_path) {
        freef("%a%a%a", map_path, level_str, buffer);
        return NULL;
    }
    buffer = open_file(map_path);
    if (!buffer) {
        freef("%a%a%a", map_path, level_str, buffer);
        return NULL;
    }
    array = my_str_to_all_array(buffer, "\n");
    freef("%a%a%a", map_path, level_str, buffer);
    return array;
}
