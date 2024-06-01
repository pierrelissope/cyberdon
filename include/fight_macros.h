/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** figth related macros
*/

#ifndef FIGHT_H
    #define FIGHT_H

typedef enum arenas_e {
    DEFAULT,
    STREET,
    BAR,
    SUS,
    ARENA_END
} arenas_t;

typedef enum fighter_state_e {
    IDLE,
    FORWARD,
    BACKWARD,
    CROUCH,
    JUMP,
    ATTACK,
    ATTACK_UP,
    ATTACK_DOWN,
    ATTACK_CROUCH,
    ATTACK_JUMP,
    HIT,
    STATES_END,
} fighter_state_t;

typedef enum fight_textures_e {
    PLAYER_IDLE_TEXT,
    PLAYER_FORWARD_TEXT,
    PLAYER_BACKWARD_TEXT,
    PLAYER_JUMP_TEXT,
    PLAYER_CROUCH,
    PLAYER_ATTACK,
    PLAYER_ATTACK_UP,
    PLAYER_ATTACK_DOWN,
    PLAYER_ATTACK_CROUCH,

    PLAYER_ATTACK_JUMP,
    PLAYER_HIT_TEXT,
    PLAYER_TEXTURES_END,

    NPC_IDLE_TEXT,
    NPC_FORWARD_TEXT,
    NPC_BACKWARD_TEXT,
    NPC_JUMP_TEXT,
    NPC_CROUCH_TEXT,
    NPC_ATTACK_TEXT,
    NPC_ATTACK_UP_TEXT,
    NPC_ATTACK_DOWN_TEXT,
    NPC_ATTACK_CROUCH_TEXT,
    NPC_ATTACK_JUMP_TEXT,
    NPC_HIT_TEXT,
    NPC_TEXTURES_END,

    BACKGROUND_TEXT,
    FORGROUND_TEXT,
    NPC_PORTRAIT_TEXT,
    PLAYER_PORTRAIT_TEXT,
    FIGHT_TEXTURES_END
} fight_textures_t;

static const int MAX_FRAMES = 255;
static const int FLOOR_Y = 900;
static const fighter_state_t STATE_LOCKS[] = {
    HIT,
    ATTACK,
    JUMP,
    ATTACK_JUMP,
    ATTACK_CROUCH,
    ATTACK_DOWN,
    ATTACK_UP,
};

static const fighter_state_t STATE_LOCKS_BYPASS[] = {
    ATTACK_JUMP,
    HIT,
};

static const fighter_state_t N_OF_LOCKS = 8;
static const fighter_state_t N_OF_BYPASS = 1;

static const float CROUCH_POS_OFFSET = 50;
static const float CROUCH_HEIGHT_OFFSET = 1.25;

static const int STAMINA_REGEN = 400;

static const int BASE_SPEED = 10;

static const int BASE_STAMINA_DECAY = 3;

static const int BASE_JUMP_POWER = 14;

#endif
