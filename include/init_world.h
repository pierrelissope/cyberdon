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
        .c = '2',
        .texture_name = STONE_BLOCK
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
        .c = -1,
        .texture_name = 0
    },
};
