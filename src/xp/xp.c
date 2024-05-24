/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** entities
*/

#include "dict.h"
#include "string.h"
#include "entity.h"
#include "inventory.h"
#include "dialog.h"
#include "myutils.h"
#include "fight.h"
#include "mymenu.h"

void reset_string(char string[100])
{
    for (int i = 0; i < 100; ++i)
        string[i] = '\0';
}

static void level_buff(stats_t *stats)
{
    stats->xp_to_levelup = stats->current_level * 10;
    stats->hp += 10;
    stats->defense++;
    stats->attack++;
    stats->speed++;
    stats->strength++;
    stats->stamina++;
    stats->stamina_regen += 3;
}

static void update_next(stats_t *stats, char *text)
{
    sprintf(text, "Attack %d", stats->attack);
    sfText_setString(stats->attack_text, text);
    reset_string(text);
    sprintf(text, "Speed %d", stats->speed);
    sfText_setString(stats->speed_text, text);
    reset_string(text);
    sprintf(text, "Strength %d", stats->strength);
    sfText_setString(stats->strength_text, text);
    reset_string(text);
    sprintf(text, "Stamina %d", stats->stamina);
    sfText_setString(stats->stamina_text, text);
    reset_string(text);
    sprintf(text, "Stamina Regen %d", stats->stamina_regen);
    sfText_setString(stats->stamina_regen_text, text);
    reset_string(text);
}

void update_stats_texts(stats_t *stats)
{
    char text[100];

    sprintf(text, "Xp %d/%d", stats->current_xp, stats->xp_to_levelup);
    sfText_setString(stats->xp_text, text);
    reset_string(text);
    sprintf(text, "Level %d", stats->current_level);
    sfText_setString(stats->level_text, text);
    reset_string(text);
    sprintf(text, "HP %d", stats->hp);
    sfText_setString(stats->hp_text, text);
    reset_string(text);
    sprintf(text, "Defense %d", stats->defense);
    sfText_setString(stats->defense_text, text);
    reset_string(text);
    update_next(stats, text);
}

void give_xp(physical_entity_t *player, int xp)
{
    for (int i = 0; i < xp; ++i) {
        player->stats.current_xp++;
        if (player->stats.current_xp >= player->stats.xp_to_levelup) {
            player->stats.current_level++;
            player->stats.current_xp = 0;
            level_buff(&player->stats);
        }
        update_stats_texts(&player->stats);
    }
}
