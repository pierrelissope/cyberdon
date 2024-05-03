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
#include "struct.h"
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>
#include <stdbool.h>

bool annimation_bypass(fighter_entity_t *entity, fighter_state_t new_state)
{
    for (fighter_state_t i = 0; i < N_OF_BYPASS; i++) {
        if (new_state == STATE_LOCKS_BYPASS[i]) {
            return true;
        }
    }
    return false;
}

void change_state(fighter_entity_t *entity, fighter_state_t new_state)
{
    if (entity->annimation_lock && !annimation_bypass(entity, new_state))
        return;
    if (entity->state != new_state) {
        entity->annimation_sheets[entity->state]->current_frame = 0;
        entity->annimation_sheets[entity->state]->text_rec.left = 0;
        sfClock_restart(entity->clock);
        entity->state = new_state;
        if (FIGHT_ACTIONS[entity->state] != NULL)
            FIGHT_ACTIONS[entity->state](entity);
    }
}

static void from_movement(fighter_entity_t *entity)
{
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        change_state(entity, FORWARD);
        entity->velocity.x = -4;
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        change_state(entity, BACKWARD);
        entity->velocity.x = 4;
    }
    if (sfKeyboard_isKeyPressed(sfKeyC)) {
        change_state(entity, CROUCH);
    }
}

static bool back_to_idle(void)
{
    if (!sfKeyboard_isKeyPressed(sfKeyC) &&
        !sfKeyboard_isKeyPressed(sfKeyLeft) &&
        !sfKeyboard_isKeyPressed(sfKeyRight))
        return true;
    return false;
}

static void update_player_state(fighter_entity_t *entity)
{
    if (back_to_idle()) {
        change_state(entity, IDLE);
    } else
        from_movement(entity);
    if (entity->state == JUMP)
        if (FIGHT_ACTIONS[entity->state] != NULL)
            FIGHT_ACTIONS[entity->state](entity);
}

static void apply_movement(fighter_entity_t *entity)
{
    sfSprite *entity_sprite = NULL;
    sfFloatRect bounds;

    for (int i = 0; entity->annimation_sheets[i] != NULL; i++) {
        entity_sprite = entity->annimation_sheets[i]->sprite_sheet;
        sfSprite_move(entity_sprite, entity->velocity);
    }
    bounds = sfSprite_getGlobalBounds(entity->annimation_sheets[entity->state]->sprite_sheet);
    entity->sprite_pos = sfSprite_getPosition(entity->annimation_sheets[entity->state]->sprite_sheet);
    entity->hitbox = bounds;
}

static void apply_gravity(fighter_entity_t *entity)
{
    sfVector2f basepos = {entity->sprite_pos.x, FLOOR_Y};

    if (entity->sprite_pos.y < FLOOR_Y)
        entity->velocity.y += 1;
    if (entity->sprite_pos.y == FLOOR_Y)
        entity->velocity.y = 0;
    if (entity->sprite_pos.y > FLOOR_Y) {
        entity->velocity.y = 0;
        entity->sprite_pos.y = FLOOR_Y;
        sfSprite_setPosition(entity->annimation_sheets[entity->state]->sprite_sheet, basepos);
    }
}

static void reverse_side(fighter_entity_t *entity)
{
    annimation_t *current = entity->annimation_sheets[entity->state];

    if (entity->looking_left) {
        sfSprite_setScale(entity->annimation_sheets[entity->state]->sprite_sheet,
                          (sfVector2f) {-3 , 3});
    }
    if (entity->looking_right) {
        sfSprite_setScale(entity->annimation_sheets[entity->state]->sprite_sheet,
                          (sfVector2f) {3 , 3});
    }
}

static void update_fighter_dir(fight_t *fight)
{
    float npc_left_point = fight->npc->hitbox.left - fight->npc->hitbox.width;
    float player_left_point = fight->player->hitbox.left - fight->player->hitbox.width;
    sfFloatRect intersection;

    printf("npc : %f, player : %f\n", npc_left_point, player_left_point);
    sfFloatRect_intersects(&(fight->player->hitbox), &(fight->npc->hitbox), &intersection);
    printf("rec: top :%f, left :%f, h :%f, w :%f\n", intersection.top, intersection.left, intersection.height, intersection.width);

    if (player_left_point > fight->npc->hitbox.left) {
        fight->player->looking_left = true;
        fight->player->looking_right = false;
        fight->npc->looking_right = true;
        fight->npc->looking_left = false;
    } else if (fight->player->hitbox.left < npc_left_point) {
        fight->player->looking_right = true;
        fight->player->looking_left = false;
        fight->npc->looking_right = false;
        fight->npc->looking_left = true;
    }
}

static bool check_colisions(fight_t *fight)
{
    if (sfFloatRect_intersects(&(fight->player->hitbox), &(fight->npc->dmgbox), NULL)) {
        printf("PLAYER HIT !\n");
    }
    if (sfFloatRect_intersects(&(fight->npc->hitbox), &(fight->player->dmgbox), NULL)) {
        printf("npc HIT !\n");
    }
}

void update_fight(fight_t *fight)
{
    update_fighter_dir(fight);

    apply_gravity(fight->player);
    apply_gravity(fight->npc);

    update_player_state(fight->player);

    reverse_side(fight->player);
    reverse_side(fight->npc);

    apply_movement(fight->player);
    apply_movement(fight->npc);

    annimate_fighter(fight->player);
    annimate_fighter(fight->npc);

    check_colisions(fight);
}
