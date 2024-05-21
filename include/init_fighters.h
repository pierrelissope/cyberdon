/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** init_fight
*/

#ifndef INIT_FIGHTERS_H
    #define INIT_FIGHTERS_H

    #include "fight_macros.h"
    #include <SFML/Graphics/Rect.h>
    #include <SFML/System/Vector2.h>

typedef struct movement_init_s {
    fighter_state_t state;
    char *text_file;
    int animation_cooldown;
    sfIntRect frame_rec;
    int frame_number;
} movement_init_t;

static const movement_init_t MOVES_INIT[] = {
    {
        IDLE,
        "idle.png",
        200,
        {0, 0, 60, 100},
        3
    },
    {
        FORWARD,
        "forward.png",
        200,
        {0, 0, 55, 100},
        2
    },
    {
        BACKWARD,
        "backward.png",
        200,
        {0, 0, 55, 100},
        2
    },
    {
        CROUCH,
        "crouch.png",
        150,
        {0, 0, 55, 100},
        2
    },
    {
        JUMP,
        "jump.png",
        125,
        {0, 0, 70, 100},
        6
    },
    {
        ATTACK,
        "attack.png",
        100,
        {0, 0, 80, 100},
        3
    },
    {
        ATTACK_UP,
        "attack_up.png",
        150,
        {0, 0, 80, 130},
        3
    },
    {
        ATTACK_DOWN,
        "attack_down.png",
        100,
        {0, 0, 80, 100},
        3
    },
    {
        ATTACK_CROUCH,
        "attack_crouch.png",
        100,
        {0, 0, 80, 110},
        3
    },
    {
        ATTACK_JUMP,
        "attack_jump.png",
        100,
        {0, 0, 80, 100},
        3
    },
    {
        HIT,
        "hit.png",
        100,
        {0, 0, 55, 112},
        1
    },
    {
        STATES_END, 0, 0, {0}, 0
    },
};

static const sfVector2f PLAYER_SPAWN = {200, 200};
static const sfVector2f NPC_SPAWN = {800, 200};
static const sfVector2f BASE_FIGHTER_VELOCITY = {0, 0};
static const int COOLDOWN = 25;

typedef struct fighter_init_s {
    char *fighter_folder;
    fight_textures_t text_beg;
    fight_textures_t text_end;
    int iframes;
} fighter_init_t;

static const fighter_init_t FIGHTER_INIT[] = {
    [PLAYER_FIGHTER] = {
        "assets/fighters/black_guy/",
        PLAYER_IDLE_TEXT,
        PLAYER_TEXTURES_END,
        300
    },
    [NPC1] = {
        "assets/fighters/black_guy/",
        NPC_IDLE_TEXT,
        NPC_TEXTURES_END,
        300,
    },
};

#endif
