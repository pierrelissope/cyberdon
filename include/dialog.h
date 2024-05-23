/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** dialog
*/

#pragma once

#include "struct.h"

void displayDialogue(sfRenderWindow *window, char *dialog,
    sfFont *font, sfEvent *event);
void handle_npc_interactions(physical_entity_t *entity,
    game_t *game, sfEvent *event);
