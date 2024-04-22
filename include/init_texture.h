/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** init_sprite
*/

#pragma once

#include "entity.h"
#include "init_entity.h"

#define MAX_SPRITE_SHEETS 100

enum Tiles {
    GRASS_BLOCK = 0,
    STONE_BLOCK = 1,
    STONE_WALL = 2,
    WOOD_WALL = 3
};

enum Spritesheets {
    IDLE = 0,
    RUNNING = 1
};

typedef struct init_texture_s {
    char *texture_path;
    int texture_name;
} init_texture_t;

static const init_texture_t PLAYER_TEXTURE_INIT[MAX_SPRITE_SHEETS] = {
    {
        .texture_path = "./assets/spritesheets/player/idle.png",
        .texture_name = IDLE
    },
    {
        .texture_path = "./assets/spritesheets/player/running.png",
        .texture_name = RUNNING
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};

static const init_texture_t VILLAGER_TEXTURE_INIT[MAX_SPRITE_SHEETS] = {
    {
        .texture_path = "./assets/spritesheets/player/idle.png",
        .texture_name = IDLE
    },
    {
        .texture_path = "./assets/spritesheets/player/running.png",
        .texture_name = RUNNING
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
