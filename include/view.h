/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** view
*/

#pragma once

#include "entity.h"

sfView *init_player_view(void);
sfView *init_fight_view(void);
void center_view(sfView *view, sfRectangleShape *player_rect, game_t *game);
