/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** parsing
*/

#include "world.h"
#include "entity.h"
#include "init_texture.h"
#include "init_world.h"

static int build_floor_rect(block_t *block, float x, float y)
{
    block->rect = sfRectangleShape_create();
    if (!block->rect)
        return EXIT_FAILURE;
    sfRectangleShape_setPosition(block->rect, (sfVector2f){50 * x, 50 * y});
    sfRectangleShape_setSize(block->rect, (sfVector2f){50, 50});
    sfRectangleShape_setFillColor(block->rect, sfTransparent);
    sfRectangleShape_setOutlineColor(block->rect, sfWhite);
    sfRectangleShape_setOutlineThickness(block->rect, 2);
    return EXIT_SUCCESS;
}

static int build_floor(block_t *block, world_t *world,
    int type, dict_t *tiles)
{
    sfVector2f origin = {0};

    block->type = type;
    block->sprite = sfSprite_create();
    if (!block->sprite) {
        freef("%s%a", block->sprite, block);
        return EXIT_FAILURE;
    }
    sfSprite_setTexture(block->sprite, dict_get(tiles, type), sfTrue);
    origin = (sfVector2f){sfTexture_getSize(dict_get(tiles, type)).x / 2,
        sfTexture_getSize(dict_get(tiles, type)).y - 2};
    sfSprite_setOrigin(block->sprite, origin);
    sfSprite_setPosition(block->sprite, isom_pos_converter(block->pos));
    append_ptr((void ***)&(world->floor), block, NULL);
    if (!world->floor) {
        freef("%s%a", block->sprite, block);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int parse_floor_line(char **floor, world_t *world,
    int y, dict_t *tiles)
{
    block_t *block = NULL;
    int type = 0;

    for (int x = 0; floor[y][x]; x++) {
        if (floor[y][x] == '0')
            continue;
        block = malloc(sizeof(block_t));
        if (!block)
            return EXIT_FAILURE;
        block->pos = (sfVector2f){x, y};
        for (int i = 0; FLOOR_BLOCK_INIT[i].c != -1; i++) {
            type = (floor[y][x] == FLOOR_BLOCK_INIT[i].c ?
                FLOOR_BLOCK_INIT[i].texture_name : type);
        }
        if (build_floor_rect(block, x, y) == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (build_floor(block, world, type, tiles) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int build_walls_rect(block_t *block, float x, float y)
{
    block->rect = sfRectangleShape_create();
    if (!block->rect)
        return EXIT_FAILURE;
    sfRectangleShape_setPosition(block->rect, (sfVector2f){50 * x, 50 * y});
    sfRectangleShape_setSize(block->rect, (sfVector2f){50, 50});
    sfRectangleShape_setFillColor(block->rect, sfTransparent);
    sfRectangleShape_setOutlineColor(block->rect, sfWhite);
    sfRectangleShape_setOutlineThickness(block->rect, 2);
    return EXIT_SUCCESS;
}

static int build_wall(block_t *block, world_t *world,
    int type, dict_t *tiles)
{
    sfVector2f origin = {0};

    block->type = type;
    block->sprite = sfSprite_create();
    if (!block->sprite) {
        freef("%s%a", block->sprite, block);
        return EXIT_FAILURE;
    }
    sfSprite_setTexture(block->sprite, dict_get(tiles, type), sfTrue);
    origin = (sfVector2f){sfTexture_getSize(dict_get(tiles, type)).x / 2,
        sfTexture_getSize(dict_get(tiles, type)).y - 2};
    sfSprite_setOrigin(block->sprite, origin);
    sfSprite_setPosition(block->sprite, isom_pos_converter_z(block->pos));
    append_ptr((void ***)&(world->walls), block, NULL);
    if (!world->walls) {
        freef("%s%a", block->sprite, block);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int parse_walls_line(char **walls, world_t *world,
    int y, dict_t *tiles)
{
    block_t *block = NULL;
    int type = 0;

    for (int x = 0; walls[y][x]; x++) {
        if (walls[y][x] == '0')
            continue;
        block = malloc(sizeof(block_t));
        if (!block)
            free(block);
        block->pos = (sfVector2f){x, y};
        for (int i = 0; WALLS_BLOCK_INIT[i].c != -1; i++) {
            type = (walls[y][x] == WALLS_BLOCK_INIT[i].c ?
                WALLS_BLOCK_INIT[i].texture_name : type);
        }
        if (build_walls_rect(block, x, y) == EXIT_FAILURE ||
            build_wall(block, world, type, tiles) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    return 0;
}
