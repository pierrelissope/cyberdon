/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** ia strongness
*/

#pragma once

typedef struct ai_strenghts_s {
    int attack_success_rate;
    int movement_success_rate;
    int distance_to_hit;
    float low_stamina;
    float high_stamina;
} ai_strenghts_t;

typedef enum ai_levels_e {
    EASY,
    MEDIUM,
    TOUGH,
    HARD,
    VERY_HARD,
    IMPOSSIBLE
} ai_levels_t;

static const ai_strenghts_t AI_LEVELS[] = {
    [EASY] = {
        20,
        20,
        150,
        0.6,
        0.6
    },
    [MEDIUM] = {
        50,
        50,
        150,
        0.6,
        0.6
    },
    [TOUGH] = {
        60,
        60,
        150,
        0.6,
        0.6
    },
    [HARD] = {
        70,
        70,
        150,
        0.6,
        0.6
    },
    [VERY_HARD] = {
        80,
        80,
        150,
        0.6,
        0.6
    },
    [IMPOSSIBLE] = {
        100,
        100,
        100,
        0.6,
        0.6
    },
};
