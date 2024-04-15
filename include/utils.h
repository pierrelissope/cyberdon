/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** utils
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "dict.h"

sfSprite **dup_sprites(sfTexture **array);
char **load_floor(int level);
char **load_walls(int level);
sfVector2f isom_pos_converter(sfVector2f pos);
sfVector2f isom_pos_converter_z(sfVector2f pos);
