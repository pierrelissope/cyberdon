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

void hit(fighter_entity_t *entity)
{
    entity->annimation_lock = true;
    entity->velocity.x = 0;
    entity->hit = true;
}

static void update_color(float health, sfRectangleShape *rec)
{
    if (health <= 0.65)
        sfRectangleShape_setFillColor(rec, MID_HEALTH);
    if (health <= 0.30)
        sfRectangleShape_setFillColor(rec, LOW_HEALTH);
}

static void uptdate_health_rec_size(fight_t *fight)
{
    float player_size = HEALTH_SIZE.x * ((float)fight->player->stats.health /
        fight->player->base_stats.health);
    float npc_size = HEALTH_SIZE.x * ((float) fight->npc->stats.health /
        fight->npc->base_stats.health);

    sfRectangleShape_setSize(fight->ui.player_health, (sfVector2f) {
            player_size,
            HEALTH_SIZE.y,
        });
    sfRectangleShape_setSize(fight->ui.npc_health, (sfVector2f) {
            npc_size,
            HEALTH_SIZE.y,
        });
    sfRectangleShape_setPosition(fight->ui.npc_health, (sfVector2f)
        {NPC_HEALTH_POS.x + (HEALTH_SIZE.x - npc_size), NPC_HEALTH_POS.y});
    update_color((float) fight->npc->stats.health /
        fight->npc->base_stats.health, fight->ui.npc_health);
    update_color((float) fight->player->stats.health /
        fight->player->base_stats.health, fight->ui.player_health);
}

void on_hit(fighter_entity_t *hited, fighter_entity_t *hiter, fight_t *fight)
{
    if (!change_state(hited, HIT))
        return;
    hited->annimation_lock = true;
    sfClock_restart(hited->i_counter);
    hited->stats.health -= 1 * hiter->base_stats.attack;
    uptdate_health_rec_size(fight);
}
