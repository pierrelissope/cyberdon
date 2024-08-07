/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** load_map
*/

#include <string.h>

#include "myutils.h"
#include "basics.h"
#include "entity.h"
#include "world.h"
#include "init_entity.h"
#include "init_texture.h"

sfIntRect get_tile_rect(int name)
{
    for (int i = 0; TILES_TEXTURE_INIT[i].texture_path; i++) {
        if (name == TILES_TEXTURE_INIT[i].texture_name)
            return TILES_TEXTURE_INIT[i].rect;
    }
    return (sfIntRect){0, 0, 128, 128};
}

int get_tile_frames(int name)
{
    for (int i = 0; TILES_TEXTURE_INIT[i].texture_path; i++) {
        if (name == TILES_TEXTURE_INIT[i].texture_name)
            return TILES_TEXTURE_INIT[i].frame_nb;
    }
    return 1;
}

char **load_floor(char *level)
{
    char *buffer = NULL;
    char **array = NULL;
    char *map_path = concat_mem((char *)LEVELS_MAP_PATHS,
        level, "/floor.conf");

    if (!map_path) {
        freef("%a%a", map_path, buffer);
        return NULL;
    }
    buffer = open_file(map_path);
    if (!buffer) {
        freef("%a%a", map_path, buffer);
        return NULL;
    }
    array = my_str_to_all_array(buffer, "\n");
    freef("%a%a", map_path, buffer);
    return array;
}

char **load_walls(char *level)
{
    char *buffer = NULL;
    char **array = NULL;
    char *map_path = concat_mem((char *)LEVELS_MAP_PATHS,
        level, "/walls.conf");

    if (!map_path) {
        freef("%a%a", map_path, buffer);
        return NULL;
    }
    buffer = open_file(map_path);
    if (!buffer) {
        freef("%a%a", map_path, buffer);
        return NULL;
    }
    array = my_str_to_all_array(buffer, "\n");
    freef("%a%a", map_path, buffer);
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

static void set_entity_components(physical_entity_t *entity, char **tokens)
{
    entity->difficulty = strdup(tokens[3]);
    entity->arena = strdup(tokens[4]);
    entity->fighter_skin_str = strdup(tokens[5]);
}

static sfVector2f get_token_coords(char *coords)
{
    sfVector2f pos = {0};
    char **tokens = my_str_to_all_array(coords, ",:");

    if (my_strlen_array(tokens) != 2)
        return (sfVector2f){0, 0};
    pos = (sfVector2f)
        {atof(tokens[0]), atof(tokens[1])};
    free_str_array(tokens);
    return pos;
}

static int parse_level_entities(char **lines,
    physical_entity_t ***entities, dict_t *sheets_dict)
{
    physical_entity_t *entity = NULL;
    char **tokens = NULL;

    for (int i = 1; lines[i]; i++) {
        tokens = my_str_to_all_array(lines[i], ";");
        if (my_strlen_array(tokens) != 6)
            return EXIT_FAILURE;
        entity = init_entity(get_token_coords(tokens[2]),
            get_entity_type(tokens[1]), tokens[0], sheets_dict);
        if (!entity->is_valid)
            return EXIT_FAILURE;
        set_entity_components(entity, tokens);
        append_ptr((void ***)entities, entity, NULL);
        freef("%t", (void **)tokens);
    }
    free_str_array(lines);
    return EXIT_SUCCESS;
}

physical_entity_t **load_level_entities(char *level, dict_t *sheets_dict)
{
    char *path = concat_mem((char *)LEVELS_MAP_PATHS, level, "/entities.conf");
    char *buffer = NULL;
    char **lines = NULL;
    physical_entity_t **entities = NULL;

    if (!path)
        return NULL;
    buffer = open_file(path);
    if (!buffer)
        return NULL;
    lines = my_str_to_all_array(buffer, "\n");
    if (!lines)
        return NULL;
    if (parse_level_entities(lines, &entities, sheets_dict) == EXIT_FAILURE)
        return NULL;
    freef("%a%a", path, buffer);
    return entities;
}
