/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** game
*/

#pragma once

#include "entity.h"

game_t init_game(void);
int handle_event(game_t *game, sfEvent *event);
void run_game(game_t *game);
void draw_game(game_t *game);
void destroy_game(game_t *game);
