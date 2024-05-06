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
    }
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
    entity->hitbox.left += 30;
}

static void apply_gravity(fighter_entity_t *entity)
{
    sfVector2f basepos = {entity->sprite_pos.x, FLOOR_Y};

    if (entity->sprite_pos.y < FLOOR_Y)
        entity->velocity.y += 1;
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
    float npc_left_point = fight->npc->hitbox.left - (fight->npc->hitbox.width / 2);
    float player_left_point = fight->player->hitbox.left - (fight->player->hitbox.width / 2);

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
    fight->player->dmgbox = (sfFloatRect) {0, 0, 0, 0};
    fight->player->dmgbox = (sfFloatRect) {0, 0, 0, 0};
}

void update_fight(fight_t *fight)
{
    update_fighter_dir(fight);

    apply_gravity(fight->player);
    apply_gravity(fight->npc);

    reverse_side(fight->player);
    reverse_side(fight->npc);

    apply_movement(fight->player);
    apply_movement(fight->npc);

    annimate_fighter(fight->player);
    annimate_fighter(fight->npc);

    check_colisions(fight);
}
