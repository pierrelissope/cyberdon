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

dict_t *dup_sprites(dict_t *dict);
char **load_floor(int level);
char **load_walls(int level);
sfVector2f isom_pos_converter(sfVector2f pos);
sfVector2f isom_pos_converter_z(sfVector2f pos);
sfVector2f normalize(sfVector2f vector);
void quicksort(linked_objects_t **array, int low, int high);
