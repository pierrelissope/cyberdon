/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** init_sprite
*/

#pragma once

#include "entity.h"

typedef struct init_texture_s {
    char *texture_path;
    int texture_name;
} init_texture_t;

enum Entity {
    PLAYER = 0,
};

enum Tiles {
    GRASS_BLOCK = 0,
    STONE_BLOCK = 1,
    STONE_WALL = 2,
    WOOD_WALL = 3
};

enum Spritesheets {
    PLAYER_IDLE = 0,
    PLAYER_RUNNING = 1
};

static const init_texture_t SHEETS_TEXTURE_INIT[] = {
    {
        .texture_path = "./assets/spritesheets/player/idle.png",
        .texture_name = PLAYER_IDLE
    },
    {
        .texture_path = "./assets/spritesheets/player/running.png",
        .texture_name = PLAYER_RUNNING
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};

static const init_texture_t TILES_TEXTURE_INIT[] = {
    {
        .texture_path = "./assets/blocks/grass.png",
        .texture_name = GRASS_BLOCK
    },
    {
        .texture_path = "./assets/blocks/stone.png",
        .texture_name = STONE_BLOCK
    },
    {
        .texture_path = "./assets/blocks/stone_wall.png",
        .texture_name = STONE_WALL
    },
    {
        .texture_path = "./assets/blocks/wood_wall.png",
        .texture_name = WOOD_WALL
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};
