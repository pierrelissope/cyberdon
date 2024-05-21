/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** parsing
*/

#include <string.h>

#include "entity.h"
#include "myutils.h"
#include "init_texture.h"
#include "teleporter.h"

static teleporter_t *build_teleporter_rect(teleporter_t *teleporter,
    sfVector2f pos, dict_t *tiles)
{
    sfVector2f origin = {0};

    teleporter->rect = sfRectangleShape_create();
    if (!teleporter->rect)
        return NULL;
    sfRectangleShape_setPosition(teleporter->rect,
        (sfVector2f){TILE_SIZE * pos.x, TILE_SIZE * pos.y});
    sfRectangleShape_setSize(teleporter->rect, (sfVector2f){50, 50});
    origin =
        (sfVector2f){sfTexture_getSize(dict_get(tiles, TELEPORTER)).x / 2,
        sfTexture_getSize(dict_get(tiles, TELEPORTER)).y - 2};
    sfSprite_setOrigin(teleporter->sprite, origin);
    sfSprite_setPosition(teleporter->sprite, isom_pos_converter(pos));
    return teleporter;
}

static teleporter_t *create_teleporter(char *coords, dict_t *tiles)
{
    teleporter_t *teleporter = calloc(1, sizeof(teleporter_t));
    sfVector2f pos = {0};
    char **tokens = NULL;

    if (!teleporter)
        return NULL;
    tokens = my_str_to_all_array(coords, ":");
    teleporter->sprite = sfSprite_create();
    pos = (sfVector2f){atof(tokens[0]), atof(tokens[1])};
    sfSprite_setTexture(teleporter->sprite,
        dict_get(tiles, TELEPORTER), sfTrue);
    return build_teleporter_rect(teleporter, pos, tiles);
}

sfVector2f get_destination_coords(char *coords)
{
    sfVector2f pos = {0};
    char **tokens = my_str_to_all_array(coords, ":");

    if (my_strlen_array(tokens) != 2)
        return (sfVector2f){0, 0};
    pos = (sfVector2f)
        {atof(tokens[0]) * TILE_SIZE, atof(tokens[1]) * TILE_SIZE};
    free_str_array(tokens);
    return pos;
}

static int parse_level_teleporters(char **lines,
    teleporter_t ***teleporters, dict_t *tiles)
{
    teleporter_t *teleporter = NULL;
    char **tokens = NULL;

    for (int i = 0; lines[i]; i++) {
        tokens = my_str_to_all_array(lines[i], ";");
        if (my_strlen_array(tokens) != 3)
            return EXIT_FAILURE;
        teleporter = create_teleporter(tokens[0], tiles);
        teleporter->destination_level = strdup(tokens[1]);
        teleporter->destination_coord = get_destination_coords(tokens[2]);
        append_ptr((void ***)teleporters, teleporter, NULL);
    }
    free_str_array(lines);
    return EXIT_SUCCESS;
}

teleporter_t **load_level_teleporters(char *level, dict_t *tiles)
{
    char *path = concat_mem((char *)LEVELS_MAP_PATHS, level,
        "/teleporters.conf");
    char *buffer = NULL;
    char **lines = NULL;
    teleporter_t **teleporters = NULL;

    if (!path) {
        freef("%a%a", path, buffer);
        return NULL;
    }
    buffer = open_file(path);
    if (!buffer) {
        freef("%a%a", path, buffer);
        return NULL;
    }
    lines = my_str_to_all_array(buffer, "\n");
    if (!lines)
        return NULL;
    return (parse_level_teleporters(lines, &teleporters,
        tiles) == EXIT_FAILURE ? NULL : teleporters);
}
