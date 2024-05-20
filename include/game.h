/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** game
*/

#pragma once

#include "entity.h"
#include "menu.h"


#define FONT    sfFont_createFromFile("assets/font/default.ttf")

game_t init_game(void);
int handle_event(game_t *game, sfEvent *event);
void run_game(game_t *game, game_info_t *_info);
void draw_game(game_t *game);
void destroy_game(game_t *game);
