/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Window.h>
#include <stdbool.h>

#define MAX_TYPE_SIZE 30

typedef enum game_state_e {
    IN_GAME,
    IN_DIALOG,
    IN_MENU,
    IN_CINEMATIC,
} game_state_t;

typedef struct dict_s {
    bool is_valid;
    int key;
    void *value;
    struct dict_s *next;
} dict_t;

typedef struct linked_objects_s {
    bool priority;
    void *object;
    sfFloatRect bounds;
    void (*fct) (void *, sfRenderWindow *window);
} linked_objects_t;

typedef struct Physical_Entity_s {
    bool is_valid;
    int type;
    char name[100];
    dict_t *sprite_sheets;
    sfSprite *current_sprite_sheet;
    sfRectangleShape *rect;
    sfClock *clock;
    sfTime last_animation_update;
    float velocity;
    int current_frame;
    int animation_cooldown;
} physical_entity_t;

typedef struct block_s {
    bool is_valid;
    int type;
    int frame_nb;
    int current_frame;
    sfIntRect sprite_rect;
    sfSprite *sprite;
    sfFloatRect hitbox;
    sfRectangleShape *rect;
    sfVector2f pos;
    sfClock *clock;
    sfTime last_animation_update;
} block_t;

typedef struct teleporter_s {
    bool is_valid;
    sfSprite *sprite;
    sfRectangleShape *rect;
    char *destination_level;
    sfVector2f destination_coord;
} teleporter_t;

typedef struct world_s {
    block_t **floor;
    block_t **walls;
    teleporter_t **teleporters;
    physical_entity_t **entities;
    char *current_level;
} world_t;

typedef struct dialog_box_s {
    bool is_valid;
    int current_dialog;
    sfRectangleShape *rect;
    sfText **dialog_array;
} dialog_box_t;

typedef struct loading_page_s {
    bool is_valid;
    int current_frame;
    int frame_nb;
    sfSprite *element_sprite;
    sfIntRect element_rect;
    sfClock *animation_clock;
    sfClock *clock;
} loading_page_t;

typedef struct status_s {
    bool is_valid;
    sfClock *teleportation_clock;
} status_t;

typedef struct game_info {
    char *save_file;
    sfVector2u screen_res;
    sfVector2u sizes[3];
    sfFont *font;
    sfRenderWindow *window;
} game_info_t;

typedef struct game_s {
    bool is_valid;
    game_state_t game_state;
    loading_page_t loading_page;
    status_t status;
    sfRenderWindow *window;
    dialog_box_t dialog_box;
    sfClock *clock;
    sfVector2f view_pos;
    sfView *player_view;
    dict_t *sheets_dict;
    dict_t *tiles_dict;
    physical_entity_t *player;
    world_t world;
    char **visited_levels;
    game_info_t *game_info;
} game_t;

typedef struct annimation_s {
    int id;
    sfIntRect text_rec;
    sfSprite *sprite_sheet;
    int cooldown_mili;
    int n_of_frames;
    int current_frame;
} annimation_t;
