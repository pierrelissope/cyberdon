/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** attack hitbox
*/

#pragma once

#include "fight_macros.h"
#include <SFML/Graphics/Rect.h>
#include <stddef.h>

static const sfFloatRect ATTACKS[][10] = {
    [PLAYER_FIGHTER] = {
        [ATTACK_JUMP] = {80, -60, 50, 50},
        [ATTACK] = {90, -130, 50, 50},
        [ATTACK_CROUCH] = {90, -70, 50, 50},
        [ATTACK_DOWN] = {50, -70, 50, 50},
        [ATTACK_UP] = {85, -230, 50, 50}
    },
    [NPC1] = {
        [ATTACK_JUMP] = {80, 60, 50, 50},
        [ATTACK] = {80, 60, 50, 50},
        [ATTACK_CROUCH] = {80, 110, 50, 50},
        [ATTACK_DOWN] = {80, 60, 50, 50},
        [ATTACK_UP] = {80, 60, 50, 50}
    },
};
