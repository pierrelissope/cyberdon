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
    STREET_LAMP,
    BEDROOM_WALL,
    BEDROOM_POSTER_WALL,
    WOOD_FLOOR,
};

enum Spritesheets {
    IDLE ,
    DOWN_LEFT,
    DOWN_RIGHT,
    UP_LEFT,
    UP_RIGHT,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

typedef struct init_texture_s {
    char *texture_path;
    int texture_name;
    sfIntRect rect;
    int frame_nb;
} init_texture_t;

static const init_texture_t PLAYER_TEXTURE_INIT[MAX_SPRITE_SHEETS] = {
    {
        .texture_path = "./assets/spritesheets/player/idle.png",
        .texture_name = IDLE
    },
    {
        .texture_path = "./assets/spritesheets/player/up.png",
        .texture_name = UP
    },
    {
        .texture_path = "./assets/spritesheets/player/down.png",
        .texture_name = DOWN
    },
    {
        .texture_path = "./assets/spritesheets/player/left.png",
        .texture_name = LEFT
    },
    {
        .texture_path = "./assets/spritesheets/player/right.png",
        .texture_name = RIGHT
    },
    {
        .texture_path = "./assets/spritesheets/player/up_left.png",
        .texture_name = UP_LEFT
    },
    {
        .texture_path = "./assets/spritesheets/player/up_right.png",
        .texture_name = UP_RIGHT
    },
    {
        .texture_path = "./assets/spritesheets/player/down_left.png",
        .texture_name = DOWN_LEFT
    },
    {
        .texture_path = "./assets/spritesheets/player/down_right.png",
        .texture_name = DOWN_RIGHT
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};

static const init_texture_t VILLAGER_TEXTURE_INIT[MAX_SPRITE_SHEETS] = {
    {
        .texture_path = "./assets/spritesheets/player/up.png",
        .texture_name = IDLE
    },
    {
        .texture_path = "./assets/spritesheets/player/up.png",
        .texture_name = UP
    },
    {
        .texture_path = "./assets/spritesheets/player/down.png",
        .texture_name = DOWN
    },
    {
        .texture_path = "./assets/spritesheets/player/left.png",
        .texture_name = LEFT
    },
    {
        .texture_path = "./assets/spritesheets/player/right.png",
        .texture_name = RIGHT
    },
    {
        .texture_path = "./assets/spritesheets/player/up_left.png",
        .texture_name = UP_LEFT
    },
    {
        .texture_path = "./assets/spritesheets/player/up_right.png",
        .texture_name = UP_RIGHT
    },
    {
        .texture_path = "./assets/spritesheets/player/down_left.png",
        .texture_name = DOWN_LEFT
    },
    {
        .texture_path = "./assets/spritesheets/player/down_right.png",
        .texture_name = DOWN_RIGHT
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};

static const init_texture_t TILES_TEXTURE_INIT[] = {
    {
        .texture_path = "./assets/blocks/collision_block.png",
        .texture_name = COLLISION_BLOCK,
        .rect = {0, 0, 128, 128},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/grass.png",
        .texture_name = GRASS_BLOCK,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/wood_floor.png",
        .texture_name = WOOD_FLOOR,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/stone.png",
        .texture_name = STONE_BLOCK,
        .rect = {0, 0, 128, 128},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/stone_wall.png",
        .texture_name = STONE_WALL,
        .rect = {0, 0, 128, 230},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/bedroom_wall.png",
        .texture_name = BEDROOM_WALL,
        .rect = {0, 0, 128, 230},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/bedroom_poster_wall.png",
        .texture_name = BEDROOM_POSTER_WALL,
        .rect = {0, 0, 128, 230},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/wood_wall.png",
        .texture_name = WOOD_WALL,
        .rect = {0, 0, 128, 128},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/building_1.png",
        .texture_name = BUILDING_1,
        .rect = {0, 0, 256, 527},
        .frame_nb = 7
    },
    {
        .texture_path = "./assets/blocks/streetlamp.png",
        .texture_name = STREET_LAMP,
        .rect = {0, 0, 128, 230},
        .frame_nb = 7
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};
