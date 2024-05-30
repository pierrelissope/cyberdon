/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** save
*/

#include <fcntl.h>
#include <string.h>

#include "world.h"
#include "xp.h"
#include "basics.h"
#include "struct.h"

static void load_saved_stats(save_t *save, stats_t *stats)
{
    stats->current_level = save->stats.current_level;
    stats->xp_to_levelup = save->stats.xp_to_levelup;
    stats->hp = save->stats.hp;
    stats->defense = save->stats.defense;
    stats->speed = save->stats.speed;
    stats->strength = save->stats.strength;
    stats->attack = save->stats.attack;
    stats->stamina = save->stats.stamina;
    stats->stamina_regen = save->stats.stamina_regen;
    stats->attack_bonus = save->stats.attack_bonus;
    stats->defense_bonus = save->stats.defense_bonus;
    stats->speed_bonus = save->stats.speed_bonus;
    stats->strength_bonus = save->stats.strength_bonus;
    stats->hp_bonus = save->stats.hp_bonus;
    stats->stamina_bonus = save->stats.stamina_bonus;
    stats->stamina_regen_bonus = save->stats.stamina_regen_bonus;
}

void create_save(game_t *game)
{
    int fd = open(".save", O_CREAT | O_TRUNC | O_RDWR, 0667);
    int len = my_strlen_array(game->visited_levels);
    save_t save = {.pos = sfRectangleShape_getPosition(game->player->rect),
        .stats = game->player->stats};

    strcpy(save.current_map, game->visited_levels[len - 1]);
    if (fd == -1)
        return;
    write(fd, &save, sizeof(save_t));
    close(fd);
}

void load_save(game_t *game)
{
    int fd = open(".save", O_RDONLY);
    save_t save = {0};
    char map[100] = {0};

    if (fd == -1)
        return;
    read(fd, &save, sizeof(save_t));
    memcpy(map, save.current_map, 100);
    load_level(game, map, game->tiles_dict);
    sfRectangleShape_setPosition(game->player->rect, save.pos);
    load_saved_stats(&save, &(game->player->stats));
    update_stats_texts(&(game->player->stats));
}
