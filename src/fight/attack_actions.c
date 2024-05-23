/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** movement actions func
*/

#include "fight_attacks.h"
#include "fight_entity.h"
#include <SFML/Graphics/Rect.h>

static void pre_attack(fighter_entity_t *entity)
{
    entity->velocity.x = 0;
    entity->annimation_lock = true;
}

static sfFloatRect apply_offset(fighter_entity_t *entity)
{
    sfFloatRect pre_dmgbox = ATTACKS[entity->name][entity->state];

    if (entity->looking_right) {
        pre_dmgbox.top += entity->sprite_pos.y;
        pre_dmgbox.left += entity->sprite_pos.x + 5;
    }
    if (entity->looking_left) {
        pre_dmgbox.top = entity->sprite_pos.y + pre_dmgbox.top;
        pre_dmgbox.left = entity->sprite_pos.x - pre_dmgbox.left - 5;
    }
    return pre_dmgbox;
}

void attack_up(fighter_entity_t *entity)
{
    pre_attack(entity);
    entity->dmgbox = apply_offset(entity);
}

void attack_down(fighter_entity_t *entity)
{
    pre_attack(entity);
    entity->dmgbox = apply_offset(entity);
}

void attack(fighter_entity_t *entity)
{
    pre_attack(entity);
    entity->dmgbox = apply_offset(entity);
}

void attack_crouch(fighter_entity_t *entity)
{
    int current_frame =
        entity->annimation_sheets[entity->state]->current_frame + 1;

    pre_attack(entity);
    entity->hitbox.top += (CROUCH_POS_OFFSET - 10) * current_frame;
    entity->hitbox.height = (entity->hitbox.height / CROUCH_HEIGHT_OFFSET);
    entity->dmgbox = apply_offset(entity);
}

void attack_jump(fighter_entity_t *entity)
{
    pre_attack(entity);
    entity->velocity.y = 0;
    entity->dmgbox = apply_offset(entity);
}
