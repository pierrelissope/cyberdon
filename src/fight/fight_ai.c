/*
** EPITECH PROJECT, 2024
** rpg2
** File description:
** fight_ai
*/

#include "fight_entity.h"
#include "fight_macros.h"
#include "fight.h"
#include <SFML/Config.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int biggest_gap(int sprite_pos)
{
    int space_right = 1920 - sprite_pos;
    int space_left = sprite_pos;

    if (space_right > space_left)
        return 1;
    else if (space_right < space_left)
        return 0;
    else
        return -1;
}

void move_towards(float *position, int target, float move_speed)
{
    if (*position < target)
        *position += move_speed;
    else if (*position > target)
        *position -= move_speed;
}

void ai_movement_pick(fight_t *fight)
{
    float d = fight->npc->sprite_pos.x - fight->player->sprite_pos.x;
    int gap_direction = 0;
    float current_stamina = fight->npc->stats.stamina / fight->npc->base_stats.stamina;

    if (current_stamina < 0.6) {
        gap_direction = biggest_gap(fight->player->sprite_pos.x);
        if (d < 100 && gap_direction == 1)
            fight->npc->velocity.x += 10;
        if (d < 100 && gap_direction == 0)
            fight->npc->velocity.x -= 10;
    } else {
        move_towards(&fight->npc->velocity.x,
            fight->player->sprite_pos.x, 10);
    }
}

fighter_state_t ai_action_pick(fight_t *fight)
{
    int action_probability = rand() % 100;
    float d = fight->npc->sprite_pos.x - fight->player->sprite_pos.x;
    float current_stamina = fight->npc->stats.stamina / fight->npc->base_stats.stamina;

    if (current_stamina < 0.6) {
        if (action_probability > 50 && d <= 100) {
            return IDLE;
        }
    }
    if (current_stamina >= 0.6) {
        if (action_probability > 50 && d <= 100) {
            decrease_stamina(fight->npc, 5);
            return ATTACK;
        }
        if (action_probability < 50 && fight->npc->velocity.y == 0) {
            decrease_stamina(fight->npc, 5);
            return ATTACK;
        }
    }
    return IDLE;
}
