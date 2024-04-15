/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** dict
*/

#pragma once

#include "basics.h"
#include <stdbool.h>
#include "struct.h"

void dict_insert(dict_t **dict, char *key, void *value);
bool dict_include(dict_t *dict, char *key);
void *dict_get(dict_t *dict, char *key);
void dict_destroy(dict_t *dict, void (*custom_free)(void *));