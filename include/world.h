/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#pragma once

#include "dict.h"
#include "entity.h"

#define MAX_TYPE_SIZE 30

world_t init_world(void);
int load_level(world_t *world, int level, dict_t *tiles);
void draw_level(sfRenderWindow *window, world_t *world,
    physical_entity_t *player);
int parse_walls_line(char **walls, world_t *world,
    int y, dict_t *tiles);
int parse_floor_line(char **floor, world_t *world,
    int y, dict_t *tiles);
