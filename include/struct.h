/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#pragma once

#include "fight_transfer.h"
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

typedef enum item_type_e {
    EMPTY_ITEM = 0,
    SPEED_ORB,
    STRENGTH_ORB,
    STAMINA_ORB,
    STAMINA_REGEN_ORB,
    VITALITY_ORB,
} item_type_t;

typedef struct dict_s {
    bool is_valid;
    int key;
    void *value;
    struct dict_s *next;
} dict_t;

typedef struct item_s {
    item_type_t type;
    sfSprite *sprite;
} item_t;

typedef struct slot_s {
    sfRectangleShape *box;
    item_t *item;
} slot_t;

typedef struct inventory_s {
    char *name;
    sfRectangleShape *box;
    sfText *text;
    slot_t **slots;
} inventory_t;

typedef struct linked_objects_s {
    bool priority;
    void *object;
    sfFloatRect bounds;
    void (*fct) (void *, sfRenderWindow *window);
} linked_objects_t;

typedef struct stats_s {
    char name[100];
    sfRectangleShape *box;
    sfSprite *sprite;

    int current_level;
    int current_xp;
    int attack;
    int speed;
    int stamina;
    int strength;
    int stamina_regeneration;
    int xp_to_levelup;

    int hp_bonus;
    int defense_bonus;
    int attack_bonus;
    int speed_bonus;
    int stamina_bonus;
    int strength_bonus;
    int stamina_regeneration_bonus;

    sfRectangleShape *sprite_rect;

    sfText *level_text;
    sfText *xp_text;
    sfText *hp_text;
    sfText *defense_text;
    sfText *attack_text;
    sfText *speed_text;
    sfText *strength_text;
    sfText *stamina_text;
    sfText *stamina_regeneration_text;

    sfText *hp_bonus_text;
    sfText *defense_bonus_text;
    sfText *attack_bonus_text;
    sfText *speed_bonus_text;
    sfText *strength_bonus_text;
    sfText *stamina_bonus_text;
    sfText *stamina_regeneration_bonus_text;
} stats_t;

typedef struct Physical_Entity_s {
    bool is_valid;
    int type;
    char name[100];
    sfFont *font;
    inventory_t *inventory;
    stats_t stats;
    dict_t *sprite_sheets;
    sfSprite *current_sprite_sheet;
    sfRectangleShape *rect;
    sfClock *clock;
    sfTime last_animation_update;
    float velocity;
    int current_frame;
    int animation_cooldown;
    fighters_t fighter_skin;
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

typedef struct chest_s {
    char *name;
    sfRectangleShape *rect;
    sfSprite *sprite;
    inventory_t *inventory;
} chest_t;

typedef struct world_s {
    block_t **floor;
    block_t **walls;
    teleporter_t **teleporters;
    physical_entity_t **entities;
    chest_t **chests;
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

typedef struct game_s {
    bool is_valid;
    game_state_t game_state;
    loading_page_t loading_page;
    status_t status;
    sfRenderWindow *window;
    sfClock *clock;
    sfVector2f view_pos;
    sfView *player_view;
    inventory_t **inventories;
    dict_t *sheets_dict;
    dict_t *tiles_dict;
    dict_t *items_dict;
    physical_entity_t *player;
    world_t world;
    sfFont *font;
    char **visited_levels;
} game_t;

typedef struct annimation_s {
    int id;
    sfIntRect text_rec;
    sfSprite *sprite_sheet;
    int cooldown_mili;
    int n_of_frames;
    int current_frame;
} annimation_t;
