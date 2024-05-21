/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** attack hitbox
*/

#pragma once

#include "fight_macros.h"
#include "fight_transfer.h"
#include <SFML/Graphics/Rect.h>

static const sfFloatRect ATTACKS[][10] = {
    [BIG_DUDE] = {
        [ATTACK_JUMP] = {80, -60, 50, 50},
        [ATTACK] = {90, -130, 50, 50},
        [ATTACK_CROUCH] = {90, -70, 50, 50},
        [ATTACK_DOWN] = {50, -70, 50, 50},
        [ATTACK_UP] = {85, -230, 50, 50}
    },
    [EAGLE] = {
        [ATTACK_JUMP] = {80, -60, 50, 50},
        [ATTACK] = {90, -130, 50, 50},
        [ATTACK_CROUCH] = {70, -40, 50, 50},
        [ATTACK_DOWN] = {80, -10, 50, 50},
        [ATTACK_UP] = {30, -200, 50, 50}
    },
    [BLACK_GUY] = {
        [ATTACK_JUMP] = {80, 10, 50, 50},
        [ATTACK] = {90, -130, 50, 50},
        [ATTACK_CROUCH] = {100, -40, 50, 50},
        [ATTACK_DOWN] = {80, -10, 50, 50},
        [ATTACK_UP] = {75, -230, 50, 50}
    },
};
