/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** game
*/

#pragma once

#include "entity.h"
#include "mh_menu.h"

#define FONT    sfFont_createFromFile("assets/font/font.ttf")

sound_t init_sound(void);
void destroy_sound(sound_t *sounds);
void draw_menu_image(sfRenderWindow *window, int specifier);
game_t init_game(void);
int handle_event(game_t *game, sfEvent *event);
int handle_inventory_event(sfRenderWindow *window,
    sfEvent *event, game_t *game);
void run_game(game_t *game);
void draw_game(game_t *game);
void destroy_game(game_t *game);
game_info_t *init_game_info(void);
