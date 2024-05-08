/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** init_entity
*/

#pragma once

#include <stddef.h>

enum Entity {
    PLAYER = 0,
    VILLAGER = 1,
};

typedef struct entity_type_s {
    char *type_str;
    int type_enum;
} entity_type_t;

static const entity_type_t INIT_ENITY_TYPE[] = {
    {
        .type_str = "villager",
        .type_enum = VILLAGER
    },
    {
        .type_str = NULL,
        .type_enum = 0
    }
};
