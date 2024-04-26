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
    GRASS_BLOCK,
    STONE_BLOCK,
    STONE_WALL,
    WOOD_WALL,
    BUILDING_1,
    COLLISION_BLOCK,
};

enum Spritesheets {
    IDLE ,
    DOWN_LEFT,
    UP_LEFT,
    LEFT,
    UP,
    DOWN,
};

typedef struct init_texture_s {
    char *texture_path;
    int texture_name;
} init_texture_t;

static const init_texture_t PLAYER_TEXTURE_INIT[MAX_SPRITE_SHEETS] = {
    {
        .texture_path = "./assets/spritesheets/player/player_up.png",
        .texture_name = IDLE
    },
    {
        .texture_path = "./assets/spritesheets/player/player_up.png",
        .texture_name = UP
    },
    {
        .texture_path = "./assets/spritesheets/player/player_down.png",
        .texture_name = DOWN
    },
    {
        .texture_path = "./assets/spritesheets/player/player_left.png",
        .texture_name = LEFT
    },
    {
        .texture_path = "./assets/spritesheets/player/player_up_left.png",
        .texture_name = UP_LEFT
    },
    {
        .texture_path = "./assets/spritesheets/player/player_down_left.png",
        .texture_name = DOWN_LEFT
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};

static const init_texture_t VILLAGER_TEXTURE_INIT[MAX_SPRITE_SHEETS] = {
    {
        .texture_path = "./assets/spritesheets/player/player_up.png",
        .texture_name = IDLE
    },
    {
        .texture_path = "./assets/spritesheets/player/player_up.png",
        .texture_name = UP
    },
    {
        .texture_path = "./assets/spritesheets/player/player_down.png",
        .texture_name = DOWN
    },
    {
        .texture_path = "./assets/spritesheets/player/player_left.png",
        .texture_name = LEFT
    },
    {
        .texture_path = "./assets/spritesheets/player/player_up_left.png",
        .texture_name = UP_LEFT
    },
    {
        .texture_path = "./assets/spritesheets/player/player_down_left.png",
        .texture_name = DOWN_LEFT
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};

static const init_texture_t TILES_TEXTURE_INIT[] = {
    {
        .texture_path = "./assets/blocks/collision_block.png",
        .texture_name = COLLISION_BLOCK
    },
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
        .texture_path = "./assets/blocks/building_1.png",
        .texture_name = BUILDING_1
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};
