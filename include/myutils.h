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
char **load_floor(char *level);
char **load_walls(char *level);
sfVector2f isom_pos_converter(sfVector2f pos);
sfVector2f isom_pos_converter_z(sfVector2f pos);
sfVector2f normalize(sfVector2f vector);
void quicksort(linked_objects_t **array, int low, int high);
sfIntRect get_tile_rect(int name);
int get_tile_frames(int name);
sfVector2f get_destination_coords(char *coords);
