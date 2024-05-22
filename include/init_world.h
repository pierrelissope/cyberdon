/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** init_sprite
*/

#pragma once

#include "entity.h"
#include "init_texture.h"

typedef struct init_world_s {
    int c;
    int texture_name;
} init_world_t;

static const init_world_t FLOOR_BLOCK_INIT[] =
{
    {
        .c = '1',
        .texture_name = GRASS_BLOCK
    },
    {
        .c = 'b',
        .texture_name = BLACK_FLOOR
    },
    {
        .c = 'w',
        .texture_name = WHITE_FLOOR
    },
    {
        .c = 'x',
        .texture_name = WOOD_FLOOR
    },
    {
        .c = 'p',
        .texture_name = ROAD_CHUNK
    },
    {
        .c = 's',
        .texture_name = SIDE_WALK_CHUNK
    },
    {
        .c = 'u',
        .texture_name = SIDE_WALK_TILE1
    },
    {
        .c = 'i',
        .texture_name = ROAD_CHUNK6
    },
    {
        .c = '*',
        .texture_name = MANHOLE
    },
    {
        .c = 'r',
        .texture_name = ROAD_CHUNKR
    },
    {
        .c = 'e',
        .texture_name = ROAD_CHUNKE
    },
    {
        .c = -1,
        .texture_name = 0
    }
};

static const init_world_t WALLS_BLOCK_INIT[] =
{
    {
        .c = 'x',
        .texture_name = POUBELLE1F1
    },
    {
        .c = '~',
        .texture_name = POUBELLE1F2
    },
    {
        .c = '}',
        .texture_name = POUBELLE1F3
    }
    ,{
        .c = '{',
        .texture_name = POUBELLE1F4
    },
    {
        .c = 'z',
        .texture_name = CARTON
    },
    {
        .c = 'w',
        .texture_name = CARTON2
    },
    {
        .c = '#',
        .texture_name = TABLE1
    },
    {
        .c = '$',
        .texture_name = TABLE2
    },
    {
        .c = '%',
        .texture_name = TABLE3
    },
    {
        .c = '&',
        .texture_name = TABLE4
    },
    {
        .c = '(',
        .texture_name = TABLE9
    },
    {
        .c = ')',
        .texture_name = TABLE12
    },
    {
        .c = '+',
        .texture_name = TABLE13
    },
    {
        .c = '-',
        .texture_name = TABLE56
    },
    {
        .c = '/',
        .texture_name = TABLE57
    },
    {
        .c = 'c',
        .texture_name = COLLISION_BLOCK
    },
    {
        .c = 'n',
        .texture_name = SKINNY_BATIMENT2X1
    },
    {
        .c = 'b',
        .texture_name = BATIMENT2X2,
    },
    {
        .c = 'e',
        .texture_name = BATIMENT2X1,
    },
    {
        .c = 'q',
        .texture_name = LITTLE_BATIMENT2X1,
    },
    {
        .c = 't',
        .texture_name = WHITE_WALL
    },
    {
        .c = 's',
        .texture_name = WHITE_PAINTED_WALL
    },
    {
        .c = 'p',
        .texture_name = POOR_BED
    },
    {
        .c = 'v',
        .texture_name = POOR_TABLE
    },
    {
        .c = 'r',
        .texture_name = ARROW_WALL
    },
    {
        .c = 'm',
        .texture_name = LIBRARY
    },
    {
        .c = 'a',
        .texture_name = CLOSET
    },
    {
        .c = '5',
        .texture_name = BUILDING_1
    },
    {
        .c = '3',
        .texture_name = STONE_WALL
    },
    {
        .c = '4',
        .texture_name = WOOD_WALL
    },
    {
        .c = 'l',
        .texture_name = STREET_LAMP
    },
    {
        .c = 'v',
        .texture_name = BEDROOM_WALL
    },
    {
        .c = 'd',
        .texture_name = BEDROOM_POSTER_WALL
    },
    {
        .c = -1,
        .texture_name = 0
    },
};
