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
        .c = 'd',
        .texture_name = SIDE_WALK_CHUNK1
    },
    {
        .c = 'c',
        .texture_name = SIDE_WALK_CHUNK1B
    },
    {
        .c = 'H',
        .texture_name = HERB
    },
    {
        .c = -1,
        .texture_name = 0
    }
};

static const init_world_t WALLS_BLOCK_INIT[] =
{
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
        .c = '1',
        .texture_name = POUBELLE1F3
    },
    {
        .c = '2',
        .texture_name = POUBELLE1F4
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
        .c = '5',
        .texture_name = BUILDING_1
    },
    {
        .c = '6',
        .texture_name = BUILDING_3V1
    },
    {
        .c = '7',
        .texture_name = BUILDING_3V2
    },
    {
        .c = '8',
        .texture_name = BUILDING_4V2
    },
    {
        .c = '9',
        .texture_name = BUILDING_4V1
    },
    {
        .c = 'A',
        .texture_name = TREE
    },
    {
        .c = 'B',
        .texture_name = CAR2
    },
    {
        .c = 'C',
        .texture_name = CITY
    },
    {
        .c = 'D',
        .texture_name = BUILDING_2
    },
    {
        .c = 'P',
        .texture_name = CAR
    },
    {
        .c = 'T',
        .texture_name = LONGBUILDING
    },
    {
        .c = 'a',
        .texture_name = CLOSET
    },
    {
        .c = 'b',
        .texture_name = BATIMENT2X2
    },
    {
        .c = 'c',
        .texture_name = COLLISION_BLOCK
    },
    {
        .c = 'd',
        .texture_name = BEDROOM_POSTER_WALL
    },
    {
        .c = 'e',
        .texture_name = BATIMENT2X1
    },
    {
        .c = 'g',
        .texture_name = GRADIANT_WALL
    },
    {
        .c = 'l',
        .texture_name = STREET_LAMP
    },
    {
        .c = 'm',
        .texture_name = LIBRARY
    },
    {
        .c = 'n',
        .texture_name = SKINNY_BATIMENT2X1
    },
    {
        .c = 'p',
        .texture_name = POOR_BED
    },
    {
        .c = 'q',
        .texture_name = LITTLE_BATIMENT2X1
    },
    {
        .c = 'r',
        .texture_name = ARROW_WALL
    },
    {
        .c = 's',
        .texture_name = WHITE_PAINTED_WALL
    },
    {
        .c = 't',
        .texture_name = WHITE_WALL
    },
    {
        .c = 't',
        .texture_name = TABLE9
    },
    {
        .c = 'v',
        .texture_name = BEDROOM_WALL
    },
    {
        .c = 'v',
        .texture_name = POOR_TABLE
    },
    {
        .c = 'w',
        .texture_name = CARTON2
    },
    {
        .c = 'x',
        .texture_name = POUBELLE1F1
    },
    {
        .c = 'y',
        .texture_name = TABLE12
    },
    {
        .c = 'z',
        .texture_name = CARTON
    },
    {
        .c = '~',
        .texture_name = POUBELLE1F2
    },
    {
        .c = -1,
        .texture_name = 0
    },
};
