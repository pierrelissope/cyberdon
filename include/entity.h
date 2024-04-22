/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** entity
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <string.h>
#include "struct.h"
#include "world.h"
#include "dict.h"
#include "utils.h"

#define MAX_TYPE_SIZE 30

physical_entity_t *init_entity(sfVector2f pos, int type, char *name,
    dict_t *sheets_dict);
void update_entity(physical_entity_t *entity);
void draw_entity(void *entity, sfRenderWindow *window);
void move_entity(physical_entity_t *entity, sfEvent *event, world_t *world);
void destroy_entity(physical_entity_t *entity);

bool still_collide(sfFloatRect *rect, world_t *world);
bool dont_collide(sfFloatRect *rect, world_t *world);
