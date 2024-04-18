/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** parsing
*/

#include "world.h"
#include "entity.h"

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
    char *type, dict_t *tiles)
{
    my_strcpy(block->type, type);
    block->sprite = sfSprite_create();
    if (!block->sprite) {
        freef("%s%a", block->sprite, block);
        return EXIT_FAILURE;
    }
    sfSprite_setTexture(block->sprite, dict_get(tiles, type), sfTrue);
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
    char *type = NULL;

    for (int x = 0; floor[y][x]; x++) {
        if (floor[y][x] == '0')
            continue;
        block = malloc(sizeof(block_t));
        if (!block)
            return EXIT_FAILURE;
        block->pos = (sfVector2f){x, y};
        type = (floor[y][x] == '1' ? "grass" : type);
        type = (floor[y][x] == '2' ? "stone" : type);
        if (build_floor_rect(block, x, y) == EXIT_FAILURE) {
            free(block);
            return EXIT_FAILURE;
        }
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
    char *type, dict_t *tiles)
{
    my_strcpy(block->type, type);
    block->sprite = sfSprite_create();
    if (!block->sprite) {
        freef("%s%a", block->sprite, block);
        return EXIT_FAILURE;
    }
    sfSprite_setTexture(block->sprite, dict_get(tiles, type), sfTrue);
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
    char *type = NULL;

    for (int x = 0; walls[y][x]; x++) {
        if (walls[y][x] == '0')
            continue;
        block = malloc(sizeof(block_t));
        if (!block)
            free(block);
        block->pos = (sfVector2f){x, y};
        type = (walls[y][x] == '3' ? "stone_wall" : type);
        type = (walls[y][x] == '4' ? "wood_wall" : type);
        if (build_walls_rect(block, x, y) == EXIT_FAILURE) {
            free(block);
            return EXIT_FAILURE;
        }
        if (build_wall(block, world, type, tiles) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    return 0;
}
