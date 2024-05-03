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
#include <SFML/System/Vector2.h>
#include <SFML/Window.h>
#include <stdbool.h>
#include "fight_macros.h"
#include "struct.h"

typedef struct Fighter_Entity_s {
    fighters_t name;
    bool looking_up;
    bool looking_down;
    bool looking_right;
    bool looking_left;

    annimation_t **annimation_sheets;
    bool annimation_lock;
    fighter_state_t state;
    int ability_cooldown;

    sfClock *ability_clock;
    sfClock *clock;
    sfVector2f sprite_pos;
    sfVector2f velocity;
    sfFloatRect hitbox;
    sfFloatRect dmgbox;
} fighter_entity_t;

typedef struct fight_s {
    arenas_t arena;
    bool debug_mode;
    dict_t *text_dict;
    sfView *view;
    physical_entity_t *player_stats;
    fighter_entity_t *player;
    physical_entity_t *npc_stats;
    fighter_entity_t *npc;
    sfRectangleShape *background;
    sfRectangleShape *foreground;
} fight_t;

fighter_entity_t *init_fighter_entity(physical_entity_t *entity_stats,
    fight_t *fight);
