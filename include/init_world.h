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
        .c = -1,
        .texture_name = 0
    },
};

static const init_world_t WALLS_BLOCK_INIT[] =
{
    {
        .c = 'c',
        .texture_name = COLLISION_BLOCK
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
        .c = 'b',
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
