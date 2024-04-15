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

    buffer = open_file(map_path);
    free(map_path);
    free(level_str);
    array = my_str_to_all_array(buffer, "\n");
    free(buffer);
    return array;
}

char **load_walls(int level)
{
    char *level_str = my_itoa(level);
    char *buffer = NULL;
    char **array = NULL;
    char *map_path = concat_mem((char *)LEVELS_MAP_PATHS, level_str, "/walls");

    buffer = open_file(map_path);
    free(map_path);
    free(level_str);
    array = my_str_to_all_array(buffer, "\n");
    free(buffer);
    return array;
}