/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** teleporter
*/

#pragma once

#include "struct.h"

teleporter_t **load_level_teleporters(char *level, dict_t *tiles);
void teleport_player(game_t *game, teleporter_t **teleporters);
