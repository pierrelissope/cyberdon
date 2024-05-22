/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** stamina handling
*/

#include "fight_entity.h"
#include "init_ui.h"
#include <stdbool.h>

static void update_color(float stamina, sfRectangleShape *rec)
{
    if (stamina > 0.50)
        sfRectangleShape_setFillColor(rec, HIGH_STAMINA);
    if (stamina <= 0.50)
        sfRectangleShape_setFillColor(rec, LOW_STAMINA);
}

void uptdate_stamina_rec_size(fight_t *fight)
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

bool decrease_stamina(fighter_entity_t *entity, int ammount)
{
    if (entity->stats.stamina - ammount *
        ((float) entity->base_stats.attack / 2) <= 0) {
        return false;
    } else {
        entity->stats.stamina -= ammount *
        ((float) entity->base_stats.attack / 2);
        return true;
    }
}

bool stamina_regen(fighter_entity_t *entity)
{
    if (entity->stats.stamina >= entity->base_stats.stamina)
        return false;
    if (entity->stats.stamina + (1 * entity->base_stats.stamina_regen)
        >= entity->base_stats.stamina) {
        entity->stats.stamina = entity->base_stats.stamina;
    } else {
        entity->stats.stamina += 1 * entity->base_stats.stamina_regen;
    }
    return false;
}
