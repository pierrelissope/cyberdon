/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** parsing
*/

#include "world.h"
#include "entity.h"

void parse_floor_line(char **floor, world_t *world,
    int y, dict_t *tiles)
{
    block_t *block = NULL;
    char *type = NULL;

    for (int x = 0; floor[y][x]; x++) {
        if (floor[y][x] == '0')
            continue;
        block = malloc(sizeof(block_t));
        block->pos = (sfVector2f){x, y};
        type = (floor[y][x] == '1' ? "grass" : type);
        type = (floor[y][x] == '2' ? "stone" : type);

        block->rect = sfRectangleShape_create();

        sfRectangleShape_setPosition(block->rect,(sfVector2f){50 * x, 50 * y});
        sfRectangleShape_setSize(block->rect,(sfVector2f){50, 50});
        sfRectangleShape_setFillColor(block->rect, sfTransparent);
        sfRectangleShape_setOutlineColor(block->rect, sfWhite);
        sfRectangleShape_setOutlineThickness(block->rect, 2);
    
        my_strcpy(block->type, type);
        block->sprite = sfSprite_create();
        sfSprite_setTexture(block->sprite, dict_get(tiles, type), sfTrue);
        sfSprite_setPosition(block->sprite, isom_pos_converter(block->pos));
        append_ptr((void ***)&(world->floor), block, NULL);
    }
}

void parse_walls_line(char **walls, world_t *world,
    int y, dict_t *tiles)
{
    block_t *block = NULL;
    char *type = NULL;

    for (int x = 0; walls[y][x]; x++) {
        if (walls[y][x] == '0')
            continue;
        block = malloc(sizeof(block_t));
        block->pos = (sfVector2f){x, y};
        type = (walls[y][x] == '3' ? "stone_wall" : type);
        type = (walls[y][x] == '4' ? "wood_wall" : type);

        block->rect = sfRectangleShape_create();

        sfRectangleShape_setPosition(block->rect,(sfVector2f){50 * x, 50 * y});
        sfRectangleShape_setSize(block->rect,(sfVector2f){50, 50});
        sfRectangleShape_setFillColor(block->rect, sfTransparent);
        sfRectangleShape_setOutlineColor(block->rect, sfWhite);
        sfRectangleShape_setOutlineThickness(block->rect, 2);

        my_strcpy(block->type, type);        
        block->sprite = sfSprite_create();
        sfSprite_setTexture(block->sprite, dict_get(tiles, type), sfTrue);
        sfSprite_setPosition(block->sprite, isom_pos_converter_z(block->pos));
        append_ptr((void ***)&(world->walls), block, NULL);
    }
}