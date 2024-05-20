/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** init of ui
*/

#pragma once

#include <SFML/Graphics/Color.h>
#include <SFML/System/Vector2.h>
static const sfVector2f PLAYER_HEALTH_POS = {.x = 51, .y = 60};
static const sfVector2f NPC_HEALTH_POS = {.x = 1264, .y = 60};

static const sfVector2f HEALTH_SIZE = {.x = 600, .y = 110};

static const sfVector2f PLAYER_STAMINA_POS = {.x = 60, .y = 200};
static const sfVector2f NPC_STAMINA_POS = {.x = 1580, .y = 205};

static const sfVector2f STAMINA_SIZE = {.x = 282, .y = 50};

static const sfColor HIGH_HEALTH = {
    .r = 255,
    .g = 255,
    .b = 255,
    .a = 240
};
static const sfColor MID_HEALTH = {
    .r = 222,
    .g = 112,
    .b = 16,
    .a = 240
};

static const sfColor LOW_HEALTH = {
    .r = 102,
    .g = 8,
    .b = 4,
    .a = 240
};

static const sfColor HIGH_STAMINA = {
    .r = 117,
    .g = 2,
    .b = 110,
    .a = 240
};

static const sfColor LOW_STAMINA = {
    .r = 56,
    .g = 1,
    .b = 53,
    .a = 240
};
