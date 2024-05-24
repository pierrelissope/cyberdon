/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** xp
*/

#pragma once

#include "basics.h"
#include <stdbool.h>
#include "entity.h"
#include "struct.h"
#include "xp.h"

void load_save(game_t *game);
void create_save(game_t *game);

void update_stats_texts(stats_t *stats);
void give_xp(physical_entity_t *player, int xp);
