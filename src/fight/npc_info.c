/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** fight loading
*/

#include <string.h>

#include "ai_values.h"
#include "dict.h"
#include "fight_entity.h"
#include "fight_macros.h"
#include "fight.h"
#include "struct.h"
#include "init_fight_arena.h"
#include "init_fighters.h"
#include "view.h"

struct link_arena_s {
    char *str;
    arenas_t arena;
};

struct link_difficulty_s {
    char *str;
    ai_levels_t level;
};

static const struct link_arena_s LINK_ARENA[] = {
    {
        .str = "default",
        .arena = DEFAULT
    },
    {
        .str = "street",
        .arena = STREET
    },
    {
        NULL,
        ARENA_END,
    }
};

static const struct link_difficulty_s LINK_DIFFICULTY[] = {
    {
        .str = "easy",
        .level = EASY
    },
    {
        .str = "medium",
        .level = MEDIUM
    },
    {
        .str = "tough",
        .level = TOUGH
    },
    {
        .str = "hard",
        .level = HARD
    },
    {
        .str = "very_hard",
        .level = VERY_HARD
    },
    {
        .str = "impossible",
        .level = IMPOSSIBLE
    },
    {
        NULL,
        END_LEVEL,
    }
};

arenas_t get_npc_arena(physical_entity_t *npc)
{
    for (size_t i = 0; LINK_ARENA[i].str != NULL; ++i)
        if (strcmp(LINK_ARENA[i].str, npc->arena) == 0)
            return LINK_ARENA[i].arena;
    return DEFAULT;
}

ai_levels_t get_npc_level(physical_entity_t *npc)
{
    for (size_t i = 0; LINK_DIFFICULTY[i].str != NULL; ++i)
        if (strcmp(LINK_DIFFICULTY[i].str, npc->difficulty) == 0)
            return LINK_DIFFICULTY[i].level;
    return EASY;
}
