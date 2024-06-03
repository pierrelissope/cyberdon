/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** init of ui
*/

#pragma once

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/System/Vector2.h>
static const sfVector2f PLAYER_HP_POS = {.x = 51, .y = 60};
static const sfVector2f NPC_HP_POS = {.x = 1264, .y = 60};

static const sfVector2f hp_SIZE = {.x = 600, .y = 110};

static const sfVector2f PLAYER_STAMINA_POS = {.x = 60, .y = 200};
static const sfVector2f NPC_STAMINA_POS = {.x = 1580, .y = 205};

static const sfVector2f STAMINA_SIZE = {.x = 282, .y = 50};

static const sfColor HIGH_HP = {
    .r = 255,
    .g = 255,
    .b = 255,
    .a = 240
};
static const sfColor MID_HP = {
    .r = 222,
    .g = 112,
    .b = 16,
    .a = 240
};

static const sfColor LOW_HP = {
    .r = 102,
    .g = 8,
    .b = 4,
    .a = 240
};

static const sfColor LOW_STAMINA = {
    .r = 117,
    .g = 2,
    .b = 110,
    .a = 240
};

static const sfColor HIGH_STAMINA = {
    .r = 235,
    .g = 108,
    .b = 232,
    .a = 240
};

static const sfIntRect NPC_PORTRAIT = {
    .height = 100,
    .width = 72,
    .left = 0,
    .top = 0
};

static const sfIntRect PLAYER_PORTRAIT = {
    .height = 100,
    .width = 72,
    .left = 0,
    .top = 0
};

static const sfIntRect END_TEXT_TEXT = {
    .height = 230,
    .width = 530,
    .left = 0,
    .top = 0
};

static const sfVector2f PLAYER_PORTRAIT_POS = {.x = 680, .y = 70};
static const sfVector2f NPC_PORTRAIT_POS = {.x = 1170, .y = 70};

static const sfVector2f PORTRAIT_SIZE = {.x = 70, .y = 100};

static const sfVector2f END_POS = {.x = 651, .y = 338};
static const sfVector2f END_SIZE = {.x = 510, .y = 230};
