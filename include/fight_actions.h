/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** fighting actions
*/

#pragma once

#include "fight_entity.h"
#include "fight_macros.h"

void attack_up(fighter_entity_t *entity);
void attack_down(fighter_entity_t *entity);
void attack(fighter_entity_t *entity);
void attack_crouch(fighter_entity_t *entity);
void attack_jump(fighter_entity_t *entity);

void jump(fighter_entity_t *entity);
void idle(fighter_entity_t *entity);
void crouch(fighter_entity_t *entity);
void forward(fighter_entity_t *entity);
void backward(fighter_entity_t *entity);

static void (*FIGHT_ACTIONS[])(fighter_entity_t *) = {
    [ATTACK] = attack,
    [ATTACK_CROUCH] = attack_crouch,
    [ATTACK_UP] = attack_up,
    [ATTACK_DOWN] = attack_down,
    [ATTACK_JUMP] = attack_jump,
    [JUMP] = jump,
    [FORWARD] = forward,
    [CROUCH] = crouch,
    [BACKWARD] = backward,
    [IDLE] = idle,
};
