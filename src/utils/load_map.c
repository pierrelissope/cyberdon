/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** load_map
*/

#include "basics.h"
#include "entity.h"
#include "init_entity.h"

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

static int get_entity_type(char *type_str)
{
    for (int i = 0; INIT_ENITY_TYPE[i].type_str; i++) {
        if (strcmp(type_str, INIT_ENITY_TYPE[i].type_str) == 0)
            return INIT_ENITY_TYPE[i].type_enum;
    }
    return -1;
}

static int parse_level_entities(char **lines,
    physical_entity_t ***entities, dict_t *sheets_dict)
{
    physical_entity_t *entity = NULL;
    sfVector2f pos = {0};
    char **pos_array = NULL;
    char **tokens = NULL;
    int type = 0;

    for (int i = 0; lines[i]; i++) {
        tokens = my_str_to_all_array(lines[i], ";");
        pos_array = my_str_to_all_array(tokens[2], ",");
        pos = (sfVector2f){atof(pos_array[0]), atof(pos_array[1])};
        type = get_entity_type(tokens[1]);
        entity = init_entity(pos, type, strdup(tokens[0]), sheets_dict);
        if (!entity->is_valid)
            return EXIT_FAILURE;
        append_ptr((void ***)entities, entity, NULL);
    }
    return EXIT_SUCCESS;
}

physical_entity_t **load_level_entities(int level, dict_t *sheets_dict)
{
    char *level_str = my_itoa(level);
    char *path = concat_mem((char *)LEVELS_MAP_PATHS, level_str, "/entities");
    char *buffer = NULL;
    char **lines = NULL;
    physical_entity_t **entities = NULL;

    if (!path) {
        freef("%a%a%a", path, level_str, buffer);
        return NULL;
    }
    buffer = open_file(path);
    if (!buffer) {
        freef("%a%a%a", path, level_str, buffer);
        return NULL;
    }
    lines = my_str_to_all_array(buffer, "\n");
    if (!lines)
        return NULL;
    return (parse_level_entities(lines, &entities,
        sheets_dict) == EXIT_FAILURE ? NULL : entities);
}
