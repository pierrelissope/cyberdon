/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** menu
*/

#pragma once

#include "struct.h"

loading_page_t init_loading_page(dict_t *tiles_dict);
void play_loading_screen(sfRenderWindow *window, loading_page_t *loading_page);
void destroy_loading_page(loading_page_t *loading_page);
