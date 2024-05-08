/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** header for fights
*/

#pragma once

#include "fight_entity.h"

void destroy_fight(fight_t *fight);
int handle_fight_event(game_t *game, fight_t *fight, sfEvent *event);
fight_t *load_fight(game_t *game, physical_entity_t *player,
    physical_entity_t *npc, arenas_t arena);
void draw_fight(fight_t *fight, sfRenderWindow *win);
void update_fight(fight_t *fight);
void annimate_fighter(fighter_entity_t *entity);
void change_state(fighter_entity_t *entity, fighter_state_t new_state);
fighter_state_t ai_action_pick(fight_t *fight);
void ai_movement_pick(fight_t *fight);
