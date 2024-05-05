/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** fighting_entity
*/

#pragma once

#include "struct.h"

void play_fight(dict_t *sheet_dict, sfRenderWindow *window);
fighting_entity_t *init_fighting_entity(sfVector2f pos, int type, char *name,
    dict_t *sheets_dict);
    