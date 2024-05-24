/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** entity
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "struct.h"

#define MAX_TYPE_SIZE 30
#define LEVELS_MAP_PATHS "./levels/"

static const int TILE_SIZE = 50;
static const sfVector2f PLAYER_START_POS = {300, 350};

physical_entity_t *init_entity(sfVector2f pos, int type, char *name,
    dict_t *sheets_dict);
void update_entity(physical_entity_t *entity);
void draw_entity(void *entity, sfRenderWindow *window);
void move_entity(physical_entity_t *entity, sfEvent *event,
    world_t *world, game_t *game);
void destroy_entity(physical_entity_t *entity);
bool still_collide(sfFloatRect *rect, world_t *world);
bool dont_collide(sfFloatRect *rect, world_t *world);
