/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#pragma once

#include "dict.h"
#include "entity.h"
#include "teleporter.h"

#define MAX_TYPE_SIZE 30
#define BLOCK_ANIMATION_COOLDOWN 100

world_t init_world(void);
int load_level(game_t *game, char *level, dict_t *tiles, dict_t *sheets_dict);
void draw_level(sfRenderWindow *window, world_t *world,
    physical_entity_t *player);
int parse_walls_line(char **walls, world_t *world,
    int y, dict_t *tiles);
int parse_floor_line(char **floor, world_t *world,
    int y, dict_t *tiles);
physical_entity_t **load_level_entities(char *level, dict_t *sheets_dict);
void animate_world(world_t *world);
world_t destroy_world(world_t *world);
