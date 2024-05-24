/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** hit handling
*/

#include "fight.h"
#include "fight_entity.h"
#include "init_ui.h"

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <stdlib.h>

void hit(fighter_entity_t *entity)
{
    entity->annimation_lock = true;
    entity->velocity.x = 0;
    entity->hit = true;
}

static void update_color(float hp, sfRectangleShape *rec)
{
    if (hp <= 0.65)
        sfRectangleShape_setFillColor(rec, MID_HP);
    if (hp <= 0.30)
        sfRectangleShape_setFillColor(rec, LOW_HP);
}

static void uptdate_hp_rec_size(fight_t *fight)
{
    float player_size = hp_SIZE.x * ((float)fight->player->stats.hp /
        fight->player->base_stats.hp);
    float npc_size = hp_SIZE.x * ((float) fight->npc->stats.hp /
        fight->npc->base_stats.hp);

    sfRectangleShape_setSize(fight->ui.player_hp, (sfVector2f) {
            player_size,
            hp_SIZE.y,
        });
    sfRectangleShape_setSize(fight->ui.npc_hp, (sfVector2f) {
            npc_size,
            hp_SIZE.y,
        });
    sfRectangleShape_setPosition(fight->ui.npc_hp, (sfVector2f)
        {NPC_HP_POS.x + (hp_SIZE.x - npc_size), NPC_HP_POS.y});
    update_color((float) fight->npc->stats.hp /
        fight->npc->base_stats.hp, fight->ui.npc_hp);
    update_color((float) fight->player->stats.hp /
        fight->player->base_stats.hp, fight->ui.player_hp);
}

void on_hit(fighter_entity_t *hited, fighter_entity_t *hiter, fight_t *fight)
{
    if (!change_state(hited, HIT))
        return;
    hited->annimation_lock = true;
    sfClock_restart(hited->i_counter);
    if (rand() % 100 <= 1 + hited->base_stats.defense)
        return;
    if ((1 + hiter->base_stats.attack + hiter->base_stats.strenght)
        - hited->base_stats.defense > 0)
        hited->stats.hp -=
            (1 + hiter->base_stats.attack + hiter->base_stats.strenght);
    uptdate_hp_rec_size(fight);
}
