/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** movement
*/

#include "fight.h"
#include "fight_entity.h"
#include "fight_macros.h"
#include "struct.h"
#include "init_ui.h"

#include <SFML/System/Time.h>
#include <stdio.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>
#include <stdbool.h>

static void apply_movement(fighter_entity_t *entity)
{
    sfSprite *entity_sprite = NULL;
    sfFloatRect bounds;

    for (int i = 0; entity->annimation_sheets[i] != NULL; i++) {
        entity_sprite = entity->annimation_sheets[i]->sprite_sheet;
        sfSprite_move(entity_sprite, entity->velocity);
    }
    bounds = sfSprite_getGlobalBounds(
        entity->annimation_sheets[entity->state]->sprite_sheet);
    entity->sprite_pos = sfSprite_getPosition(
        entity->annimation_sheets[entity->state]->sprite_sheet);
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
        sfSprite_setPosition(
        entity->annimation_sheets[entity->state]->sprite_sheet, basepos);
    }
}

static void reverse_side(fighter_entity_t *entity)
{
    if (entity->looking_left) {
        sfSprite_setScale(
        entity->annimation_sheets[entity->state]->sprite_sheet,
            (sfVector2f) {-3, 3});
    }
    if (entity->looking_right) {
        sfSprite_setScale(
        entity->annimation_sheets[entity->state]->sprite_sheet,
            (sfVector2f) {3, 3});
    }
}

static void update_fighter_dir(fight_t *fight)
{
    float npc_left_point = fight->npc->hitbox.left -
        (fight->npc->hitbox.width / 2);
    float player_left_point = fight->player->hitbox.left -
        (fight->player->hitbox.width / 2);

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

static void check_colisions(fight_t *fight)
{
    if (!fight->player->hit && sfFloatRect_intersects(&(fight->player->hitbox),
        &(fight->npc->dmgbox), NULL)) {
        on_hit(fight->player, fight);
    }
    if (!fight->npc->hit && sfFloatRect_intersects(&(fight->npc->hitbox),
        &(fight->player->dmgbox), NULL)) {
        on_hit(fight->npc, fight);
    }
    fight->player->dmgbox = (sfFloatRect) {0, 0, 0, 0};
    fight->player->dmgbox = (sfFloatRect) {0, 0, 0, 0};
}

static void update_fighters_hits(fighter_entity_t *entity)
{
    if (!entity->hit)
        return;
    if (sfTime_asMilliseconds(sfClock_getElapsedTime(entity->i_counter)) >=
        entity->iframes)
        entity->hit = false;
}

static void update_color(float stamina, sfRectangleShape *rec)
{
    if (stamina <= 0.50)
        sfRectangleShape_setFillColor(rec, LOW_STAMINA);
}

static void uptdate_stamina_rec_size(fight_t *fight)
{
    float player_size = STAMINA_SIZE.x * ((float)fight->player->stats.stamina /
        fight->player->base_stats.stamina);
    float npc_size = STAMINA_SIZE.x * ((float) fight->npc->stats.stamina /
        fight->npc->base_stats.stamina);

    sfRectangleShape_setSize(fight->ui.player_stamina, (sfVector2f) {
            player_size,
            STAMINA_SIZE.y,
        });
    sfRectangleShape_setSize(fight->ui.npc_stamina, (sfVector2f) {
            npc_size,
            STAMINA_SIZE.y,
        });
    sfRectangleShape_setPosition(fight->ui.npc_stamina, (sfVector2f)
        {NPC_STAMINA_POS.x + (STAMINA_SIZE.x - npc_size), NPC_STAMINA_POS.y});
    update_color((float) fight->npc->stats.stamina /
        fight->npc->base_stats.stamina, fight->ui.npc_stamina);
    update_color((float) fight->player->stats.stamina /
        fight->player->base_stats.stamina, fight->ui.player_stamina);
}

void update_fight(fight_t *fight)
{
    update_fighter_dir(fight);
    update_fighters_hits(fight->player);
    update_fighters_hits(fight->player);
    check_colisions(fight);
    apply_gravity(fight->player);
    apply_gravity(fight->npc);
    reverse_side(fight->player);
    reverse_side(fight->npc);
    apply_movement(fight->player);
    apply_movement(fight->npc);
    annimate_fighter(fight->npc);
    annimate_fighter(fight->player);
    uptdate_stamina_rec_size(fight);
}
