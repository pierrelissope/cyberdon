/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** header for fights
*/

#pragma once

#include "fight_entity.h"
#include "fight_transfer.h"

void destroy_fight(fight_t *fight);
int handle_fight_event(game_t *game, fight_t *fight, sfEvent *event);
fight_t *load_fight(game_t *game, physical_entity_t *player,
    physical_entity_t *npc, arenas_t arena);
void draw_fight(fight_t *fight, sfRenderWindow *win);
void update_fight(fight_t *fight);
void annimate_fighter(fighter_entity_t *entity);
bool change_state(fighter_entity_t *entity, fighter_state_t new_state);
fighter_state_t ai_action_pick(fight_t *fight);
fighter_state_t ai_movement_pick(fight_t *fight);
void test(game_t *game);
int run_fight(game_t *game, physical_entity_t *player,
    physical_entity_t *npc, arenas_t arena);
void on_hit(fighter_entity_t *hiter, fighter_entity_t *hited, fight_t *fight);
bool load_ui(fight_t *fight);
void uptdate_stamina_rec_size(fight_t *fight);
void stamina_regen(fighter_entity_t *entity);
bool decrease_stamina(fighter_entity_t *entity, int ammount);
