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

static bool biggest_gap(float sprite_pos)
{
    float space_right = 1920 - sprite_pos;
    float space_left = sprite_pos;

    if (space_right > space_left)
        return 1;
    if (space_right < space_left)
        return 0;
    return 0;
}

static void low_stamina_movement(fight_t *fight, bool gap_direction)
{
    float d = fight->npc->sprite_pos.x - fight->player->sprite_pos.x;

    if (d < 100 && gap_direction == true)
        fight->npc->velocity.x = 10;
    if (d < 100 && gap_direction == false)
        fight->npc->velocity.x = -10;
}

static void high_stamina_movement(fight_t *fight, bool gap_direction)
{
    float d = fight->npc->sprite_pos.x - fight->player->sprite_pos.x;

    if (d < 100)
        return;
    if (fight->npc->looking_left)
        fight->npc->velocity.x = -10;
    if (fight->npc->looking_right)
        fight->npc->velocity.x = 10;
}

void ai_movement_pick(fight_t *fight)
{
    bool gap_direction = 0;
    float current_stamina =
        (float) fight->npc->stats.stamina / fight->npc->base_stats.stamina;

    gap_direction = biggest_gap(fight->npc->sprite_pos.x);
    if (current_stamina < 0.6) {
        low_stamina_movement(fight, gap_direction);
    }
    if (current_stamina >= 0.6) {
        high_stamina_movement(fight, gap_direction);
    }
}

static fighter_state_t low_stamina_action(fight_t *fight)
{
    float d = fight->npc->sprite_pos.x - fight->player->sprite_pos.x;

    return IDLE;
}

static fighter_state_t high_stamina_action(fight_t *fight)
{
    float d = fight->npc->sprite_pos.x - fight->player->sprite_pos.x;

    if (d <= 150) {
        decrease_stamina(fight->npc, 5);
        return ATTACK;
    }
    return IDLE;
}

fighter_state_t ai_action_pick(fight_t *fight)
{
    float current_stamina =
        (float) fight->npc->stats.stamina / fight->npc->base_stats.stamina;

    srand(time(0));
    if (rand() % 100 >= 50)
        return IDLE;
    if (current_stamina < 0.7) {
        return low_stamina_action(fight);
    }
    if (current_stamina >= 0.7) {
        return high_stamina_action(fight);
    }
    return IDLE;
}
