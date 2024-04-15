/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Window.h>

#define MAX_TYPE_SIZE 30

typedef struct dict_s {
    char *key;
    void *value;
    struct dict_s *next;
} dict_t;

typedef struct Physical_Entity_s {
    char type[MAX_TYPE_SIZE];
    sfSprite **sprite_sheets;

    sfRectangleShape *rect;

    int current_spritesheet;
    sfClock *clock;
    sfTime last_animation_update;
    int current_frame;
    int animation_cooldown;

    sfSprite *sprite;
} Physical_Entity_t;

typedef struct block_s {
    char type[MAX_TYPE_SIZE];
    sfSprite *sprite;
    sfFloatRect hitbox;
    sfRectangleShape *rect;
    sfVector2f pos;
} block_t;

typedef struct world_s {
    block_t **floor;
    block_t **walls;
    int current_level;
} world_t;

typedef struct game_s {

    sfRenderWindow *window;
    dict_t *sheets_dict;
    dict_t *tiles_dict;
    Physical_Entity_t player;
    world_t world;
} game_t;
