/*
** EPITECH PROJECT, 2024
** rpg2
** File description:
** fight_ai
*/

#include "ai_values.h"
#include "fight_entity.h"
#include "fight_macros.h"
#include "fight.h"
#include "init_fighters.h"
#include <SFML/Config.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>
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

static float get_distance(fight_t *fight)
{
    float d = 0;

    if (fight->npc->looking_right)
        d = fight->player->sprite_pos.x - fight->npc->sprite_pos.x;
    if (fight->npc->looking_left)
        d = fight->npc->sprite_pos.x - fight->player->sprite_pos.x;
    return d;
}

static void low_stamina_movement(fight_t *fight, bool gap_direction)
{
    float d = get_distance(fight);

    if (d < AI_LEVELS[fight->level].distance_to_hit)
        return;
    if (gap_direction == true)
        fight->npc->velocity.x =
            BASE_SPEED * fight->npc->base_stats.speed;
    if (gap_direction == false)
        fight->npc->velocity.x =
            -1 * BASE_SPEED * fight->npc->base_stats.speed;
}

static void high_stamina_movement(fight_t *fight, bool gap_direction)
{
    float d = get_distance(fight);

    if (d < AI_LEVELS[fight->level].distance_to_hit)
        return;
    if (fight->npc->looking_left)
        fight->npc->velocity.x =
            -1 * (BASE_SPEED + fight->npc->base_stats.speed);
    if (fight->npc->looking_right)
        fight->npc->velocity.x =
            (BASE_SPEED + fight->npc->base_stats.speed);
}

static fighter_state_t permanent_checks(fight_t *fight)
{
    float d = get_distance(fight);
    fighter_state_t action = IDLE;

    if (d < AI_LEVELS[fight->level].distance_to_hit)
        return action;
    if (fight->player->state == ATTACK) {
        if (rand() % 2) {
            fight->npc->crouching = true;
            action = CROUCH;
        } else {
            decrease_stamina(fight->npc,
            BASE_STAMINA_DECAY + fight->npc->base_stats.strenght);
            action = JUMP;
        }
    }
    return action;
}

bool can_move(fight_t *fight)
{
    bool fail = rand() % 100 > AI_LEVELS[fight->level].movement_success_rate;
    bool last_success =
        sfTime_asMilliseconds(
        sfClock_getElapsedTime(fight->npc->success_cooldown)) < 150;

    if (sfTime_asMilliseconds(
        sfClock_getElapsedTime(fight->npc->fail_cooldown)) < 300)
        return true;
    if (!fail && last_success == false)
        sfClock_restart(fight->npc->success_cooldown);
    if (fail && last_success == false) {
        sfClock_restart(fight->npc->fail_cooldown);
        return true;
    }
    return false;
}

fighter_state_t ai_movement_pick(fight_t *fight)
{
    bool gap_direction = 0;
    float current_stamina =
        (float) fight->npc->stats.stamina / fight->npc->base_stats.stamina;

    gap_direction = biggest_gap(fight->npc->sprite_pos.x);
    if (can_move(fight))
        return IDLE;
    if (current_stamina < AI_LEVELS[fight->level].low_stamina)
        low_stamina_movement(fight, gap_direction);
    else if (current_stamina >= AI_LEVELS[fight->level].high_stamina)
        high_stamina_movement(fight, gap_direction);
    return permanent_checks(fight);
}

static fighter_state_t low_stamina_action(fight_t *fight)
{
    float d = get_distance(fight);

    return IDLE;
}

static fighter_state_t high_stamina_action(fight_t *fight)
{
    float d = get_distance(fight);

    if (d <= AI_LEVELS[fight->level].distance_to_hit) {
        decrease_stamina(fight->npc,
        BASE_STAMINA_DECAY + fight->npc->base_stats.strenght);
        if (fight->player->crouching)
            fight->npc->looking_down = true;
        if (fight->player->sprite_pos.y <=
            (fight->npc->sprite_pos.y - fight->npc->hitbox.height) + 40)
            fight->npc->looking_up = true;
        return ATTACK;
    }
    return IDLE;
}

fighter_state_t ai_action_pick(fight_t *fight)
{
    float current_stamina =
        (float) fight->npc->stats.stamina / fight->npc->base_stats.stamina;

    if (rand() % 100 > AI_LEVELS[fight->level].attack_success_rate)
        return IDLE;
    if (current_stamina < AI_LEVELS[fight->level].low_stamina) {
        return low_stamina_action(fight);
    }
    if (current_stamina >= AI_LEVELS[fight->level].high_stamina) {
        return high_stamina_action(fight);
    }
    return IDLE;
}
