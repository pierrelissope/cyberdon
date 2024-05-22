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
    CITY,
    POUBELLE1F1,
    POUBELLE1F2,
    POUBELLE1F3,
    POUBELLE1F4,
    CARTON,
    CARTON2,
    TABLE1,
    TABLE2,
    TABLE3,
    TABLE4,
    TABLE6,
    TABLE9,
    TABLE12,
    TABLE13,
    TABLE56,
    TABLE57,
    MANHOLE,
    LOADING_PAGE_SHEET,
    BATIMENT2X2,
    BATIMENT2X1,
    LITTLE_BATIMENT2X1,
    SKINNY_BATIMENT2X1,
    CHEST,
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
    WOOD_FLOOR2,
    WHITE_WALL,
    TELEPORTER,
    BLACK_FLOOR,
    WHITE_FLOOR,
    WHITE_PAINTED_WALL,
    POOR_BED,
    LIBRARY,
    CLOSET,
    POOR_TABLE,
    ARROW_WALL,
    ROAD_CHUNK,
    ROAD_CHUNKR,
    ROAD_CHUNKE,
    ROAD_CHUNK1,
    ROAD_CHUNK2,
    ROAD_CHUNK3,
    ROAD_CHUNK4,
    ROAD_CHUNK5,
    ROAD_CHUNK6,
    SIDE_WALK_CHUNK,
    SIDE_WALK_CHUNK1,
    SIDE_WALK_CHUNK2,
    SIDE_WALK_CHUNK3,
    SIDE_WALK_CHUNK4,
    SIDE_WALK_TILE,
    SIDE_WALK_TILE1,
};

enum Spritesheets {
    IDLE,
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
        .texture_path = "./assets/spritesheets/loading_page/element.png",
        .texture_name = LOADING_PAGE_SHEET,
        .rect = {0, 0, 1134 / 5, 168},
        .frame_nb = 5,
    },
    {
        .texture_path = "./assets/spritesheets/props/poubelle/POUBELLE.png",
        .texture_name = POUBELLE1F1,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/poubelle/POUBELLE2.png",
        .texture_name = POUBELLE1F2,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/poubelle/POUBELLE3.png",
        .texture_name = POUBELLE1F3,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/poubelle/POUBELLE4.png",
        .texture_name = POUBELLE1F4,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/carton/CARTON1.png",
        .texture_name = CARTON,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/carton/CARTON2.png",
        .texture_name = CARTON2,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/manhole/manhole.png",
        .texture_name = MANHOLE,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/table/TABLE1.png",
        .texture_name = TABLE1,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/table/TABLE2.png",
        .texture_name = TABLE2,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/table/TABLE3.png",
        .texture_name = TABLE3,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/table/TABLE4.png",
        .texture_name = TABLE4,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/table/TABLE6.png",
        .texture_name = TABLE6,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/table/TABLE9.png",
        .texture_name = TABLE9,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/table/TABLE12.png",
        .texture_name = TABLE12,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/table/TABLE13.png",
        .texture_name = TABLE13,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/blocks/chest.png",
        .texture_name = CHEST,
        .rect = {0, 0, 256, 94},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/table/TABLE56.png",
        .texture_name = TABLE56,
        .rect = {0, 0, 128, 127},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/spritesheets/props/table/TABLE57.png",
        .texture_name = TABLE57,
        .rect = {0, 0, 128, 128},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/blocks/batiment2x2.png",
        .texture_name = BATIMENT2X2,
        .rect = {0, 0, 256, 500},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/little_batiment2x1.png",
        .texture_name = LITTLE_BATIMENT2X1,
        .rect = {0, 0, 256, 294},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/city.png",
        .texture_name = CITY,
        .rect = {0, 0, 128, 454},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/skinny_batiment2x1.png",
        .texture_name = SKINNY_BATIMENT2X1,
        .rect = {0, 0, 256, 227},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/batiment2x1.png",
        .texture_name = BATIMENT2X1,
        .rect = {0, 0, 256, 416},
        .frame_nb = 1
    },
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
        .texture_path = "./assets/blocks/tp_floor.png",
        .texture_name = TELEPORTER,
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
        .texture_path = "./assets/blocks/black_floor.png",
        .texture_name = BLACK_FLOOR,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/white_floor.png",
        .texture_name = WHITE_FLOOR,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/wood_floor2.png",
        .texture_name = WOOD_FLOOR2,
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
        .texture_path = "./assets/blocks/white_wall.png",
        .texture_name = WHITE_WALL,
        .rect = {0, 0, 128, 327},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/arrow_wall.png",
        .texture_name = ARROW_WALL,
        .rect = {0, 0, 256, 327},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/painted_white_wall.png",
        .texture_name = WHITE_PAINTED_WALL,
        .rect = {0, 0, 128, 327},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/poor_bed.png",
        .texture_name = POOR_BED,
        .rect = {0, 0, 256, 270},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/poor_table.png",
        .texture_name = POOR_TABLE,
        .rect = {0, 0, 256, 270},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/closet.png",
        .texture_name = CLOSET,
        .rect = {0, 0, 128, 380},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/library.png",
        .texture_name = LIBRARY,
        .rect = {0, 0, 256, 380},
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
        .texture_path = "./assets/blocks/floors/Road_Chunk.png",
        .texture_name = ROAD_CHUNK,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Road_Chunk.png",
        .texture_name = ROAD_CHUNKR,
        .rect = {256, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Road_Chunk6.png",
        .texture_name = ROAD_CHUNKE,
        .rect = {256, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Road_Chunk1.png",
        .texture_name = ROAD_CHUNK1,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Road_Chunk2.png",
        .texture_name = ROAD_CHUNK2,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Road_Chunk3.png",
        .texture_name = ROAD_CHUNK3,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Road_Chunk4.png",
        .texture_name = ROAD_CHUNK4,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Road_Chunk5.png",
        .texture_name = ROAD_CHUNK5,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Road_Chunk6.png",
        .texture_name = ROAD_CHUNK6,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Sidewalk_Chunk.png",
        .texture_name = SIDE_WALK_CHUNK,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Sidewalk_Chunk1.png",
        .texture_name = SIDE_WALK_CHUNK1,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Sidewalk_Chunk2.png",
        .texture_name = SIDE_WALK_CHUNK2,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Sidewalk_Chunk3.png",
        .texture_name = SIDE_WALK_CHUNK3,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Sidewalk_Chunk4.png",
        .texture_name = SIDE_WALK_CHUNK4,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Sidewalk_Tile.png",
        .texture_name = SIDE_WALK_TILE,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = "./assets/blocks/floors/Sidewalk_Tile1.png",
        .texture_name = SIDE_WALK_TILE1,
        .rect = {0, 0, 128, 105},
        .frame_nb = 1
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};

static const init_texture_t ITEMS_TEXTURE_INIT[] = {
    {
        .texture_path = "./assets/items/speed_orb.png",
        .texture_name = SPEED_ORB,
        .rect = {0, 0, 80, 80},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/items/strength_orb.png",
        .texture_name = STRENGTH_ORB,
        .rect = {0, 0, 80, 80},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/items/strength_orb.png",
        .texture_name = STAMINA_ORB,
        .rect = {0, 0, 80, 80},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/items/strength_orb.png",
        .texture_name = STAMINA_REGEN_ORB,
        .rect = {0, 0, 80, 80},
        .frame_nb = 1,
    },
    {
        .texture_path = "./assets/items/strength_orb.png",
        .texture_name = VITALITY_ORB,
        .rect = {0, 0, 80, 80},
        .frame_nb = 1,
    },
    {
        .texture_path = NULL,
        .texture_name = 0
    },
};
