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
#include "world.h"
#include "dict.h"
#include "utils.h"

#define MAX_TYPE_SIZE 30

Physical_Entity_t init_entity(sfVector2f pos, char *type, dict_t *sheets_dict);
void update_entity(Physical_Entity_t *entity);
void draw_entity(Physical_Entity_t *entity, sfRenderWindow *window);
void move_entity(Physical_Entity_t *entity, sfEvent *event, world_t *world);