/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdbool.h>

#define MAX_TYPE_SIZE 30

typedef struct dict_s {
    bool is_valid;
    int key;
    void *value;
    struct dict_s *next;
} dict_t;

typedef struct linked_objects_s {
    void *object;
    sfFloatRect bounds;
    void (*fct) (void *, sfRenderWindow *window);
} linked_objects_t;

typedef struct Physical_Entity_s {
    bool is_valid;
    int type;
    char name[100];
    sfSprite **sprite_sheets;
    sfRectangleShape *rect;
    int current_spritesheet;
    sfClock *clock;
    sfTime last_animation_update;
    float velocity;
    int current_frame;
    int animation_cooldown;
} physical_entity_t;

typedef struct block_s {
    bool is_valid;
    int type;
    sfSprite *sprite;
    sfFloatRect hitbox;
    sfRectangleShape *rect;
    sfVector2f pos;
} block_t;

typedef struct world_s {
    block_t **floor;
    block_t **walls;
    physical_entity_t **entities;
    int current_level;
} world_t;

typedef struct game_s {
    bool is_valid;
    sfRenderWindow *window;
    dict_t *sheets_dict;
    dict_t *tiles_dict;
    physical_entity_t *player;
    world_t world;
} game_t;
