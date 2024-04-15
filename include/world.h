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
void load_level(world_t *world, int level, dict_t *tiles);
void draw_level(sfRenderWindow *window, world_t *world, Physical_Entity_t *player);
void parse_walls_line(char **walls, world_t *world,
    int y, dict_t *tiles);
void parse_floor_line(char **floor, world_t *world,
    int y, dict_t *tiles);