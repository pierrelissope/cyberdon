/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** movement
*/

#include "fight.h"
#include "fight_actions.h"
#include "fight_entity.h"
#include "fight_macros.h"
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>

bool state_lock(fighter_entity_t *entity)
{
    for (fighter_state_t i = 0; i < N_OF_LOCKS; i++) {
        if (entity->state == i &&
            entity->annimation_sheets[entity->state]->current_frame != 0 &&
            entity->annimation_sheets[entity->state]->current_frame <=
            entity->annimation_sheets[entity->state]->n_of_frames - 1)
            return true;
    }
    return false;
}

void change_state(fighter_entity_t *entity, fighter_state_t new_state)
{
    /* if ((new_state != IDLE || new_state != FORWARD || new_state != BACKWARD) && */
    /*     sfTime_asMilliseconds(sfClock_getElapsedTime(entity->ability_clock)) */
    /*     <= entity->ability_cooldown) */
    /*     return; */
    sfClock_restart(entity->ability_clock);
    if (entity->state != new_state) {
        entity->annimation_sheets[entity->state]->current_frame = 0;
        entity->annimation_sheets[entity->state]->text_rec.left = 0;
        sfClock_restart(entity->clock);
        entity->state = new_state;
    }
}

static void from_movement(fighter_entity_t *entity)
{
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        change_state(entity, FORWARD);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        change_state(entity, BACKWARD);
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        change_state(entity, CROUCH);
    }
}

static void update_player_state(fighter_entity_t *entity)
{
    if (!sfKeyboard_isKeyPressed(sfKeyDown) &&
        !sfKeyboard_isKeyPressed(sfKeyLeft) &&
        !sfKeyboard_isKeyPressed(sfKeyRight)) {
        change_state(entity, IDLE);
    } else
        from_movement(entity);
}

static void apply_movement(fighter_entity_t *entity)
{
    sfSprite *entity_sprite = entity->annimation_sheets[entity->state]->sprite_sheet;
    sfFloatRect bounds;

    sfSprite_move(entity_sprite, entity->velocity);
    bounds = sfSprite_getGlobalBounds(entity_sprite);
    entity->sprite_pos = (sfVector2f) {bounds.left, bounds.top};
    for (int i = 0; entity->annimation_sheets[i] != NULL; i++) {
        sfSprite_setPosition(entity->annimation_sheets[i]->sprite_sheet, entity->sprite_pos);
    }
}

static void apply_gravity(fighter_entity_t *entity)
{
    if (entity->sprite_pos.y < FLOOR_Y)
        entity->velocity.y += 2;
    else
        entity->velocity.y = 0;
}

void update_fight(fight_t *fight)
{
    apply_gravity(fight->player);
    apply_gravity(fight->npc);
    update_player_state(fight->player);
    apply_movement(fight->player);
    annimate_fighter(fight->player);
    annimate_fighter(fight->npc);
}
