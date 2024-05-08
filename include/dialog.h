/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** dialog
*/

#pragma once

#include "struct.h"

dialog_box_t init_dialog_box(void);
void update_dialog_box(dialog_box_t *dialog_box, game_t *game);
void display_dialog_box(sfRenderWindow *window, dialog_box_t *dialog_box,
    game_state_t game_state);
