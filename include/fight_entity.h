/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window.h>
#include <stdbool.h>

#include "fight_macros.h"
#include "fight_transfer.h"
#include "struct.h"

typedef struct stats_s {
    int speed;
    int health;
    int attack;
    int defense;
    int stamina;
    int stamina_regen;
} stats_t;

typedef struct stats_c_s {
    int health;
    int stamina;
} stats_c_t;

typedef struct Fighter_Entity_s {
    fighters_t name;
    bool player;
    bool looking_up;
    bool looking_down;
    bool looking_right;
    bool looking_left;
    bool crouching;

    annimation_t **annimation_sheets;
    bool annimation_lock;
    fighter_state_t state;

    sfClock *i_counter;
    int iframes;
    bool hit;

    sfClock *clock;
    sfVector2f sprite_pos;
    sfVector2f velocity;
    sfFloatRect hitbox;
    sfFloatRect dmgbox;
    stats_c_t stats;
    stats_t base_stats;
} fighter_entity_t;

typedef struct ui_s {
    sfRectangleShape *player_health;
    sfRectangleShape *npc_health;
    sfRectangleShape *player_stamina;
    sfRectangleShape *npc_stamina;
    sfRectangleShape *npc_portrait;
    sfRectangleShape *player_portrait;
} ui_t;

typedef struct fight_s {
    arenas_t arena;
    bool debug_mode;
    dict_t *text_dict;
    sfView *view;
    physical_entity_t *player_stats;
    fighter_entity_t *player;
    physical_entity_t *npc_stats;
    fighter_entity_t *npc;
    ui_t ui;
    sfRectangleShape *background;
    sfRectangleShape *foreground;
    sfClock *fps_clock;
    sfClock *stamina_clock;
} fight_t;

fighter_entity_t *init_fighter_entity(physical_entity_t *entity_stats,
    fight_t *fight, bool fighter);
