/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** parsing
*/

#include "entity.h"
#include "utils.h"
#include "init_texture.h"
#include "teleporter.h"

static const char *LEVELS_MAP_PATHS = "./levels/";
static const sfVector2f TILE_SIZE = {50, 50};

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
    teleporter->rect = sfRectangleShape_create();
    if (!teleporter->rect)
        return NULL;
    sfRectangleShape_setPosition(teleporter->rect, (sfVector2f){50 * pos.x, 50 * pos.y});
    sfRectangleShape_setSize(teleporter->rect, (sfVector2f){50, 50});
    sfRectangleShape_setFillColor(teleporter->rect, sfTransparent);
    sfRectangleShape_setOutlineColor(teleporter->rect, sfWhite);
    sfRectangleShape_setOutlineThickness(teleporter->rect, 2);
    sfVector2f origin = (sfVector2f){sfTexture_getSize(dict_get(tiles, TELEPORTER)).x / 2,
        sfTexture_getSize(dict_get(tiles, TELEPORTER)).y - 2};
    sfSprite_setOrigin(teleporter->sprite, origin);
    sfSprite_setPosition(teleporter->sprite, isom_pos_converter(pos));
    return teleporter;
}

static sfVector2f get_destination_coords(char *coords)
{
    char **tokens = my_str_to_all_array(coords, ":");
    sfVector2f pos = 
        {atof(tokens[0]) * TILE_SIZE.x, atof(tokens[1]) * TILE_SIZE.x};

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
    char *path = concat_mem((char *)LEVELS_MAP_PATHS, level, "/teleporters.conf");
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
