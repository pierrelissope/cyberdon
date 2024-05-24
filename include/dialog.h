/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** dialog
*/

#pragma once

#include "struct.h"

void display_dialogue(game_t *game, char *dialog,
    physical_entity_t *npc, sfEvent *event);
void handle_npc_interactions(physical_entity_t *entity,
    game_t *game, sfEvent *event);
