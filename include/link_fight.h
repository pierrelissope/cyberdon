/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** linking
*/

#pragma once

#include <stddef.h>

#include "init_fighters.h"
#include "ai_values.h"
#include "fight_macros.h"
#include "fight_transfer.h"

struct link_arena_s {
    char *str;
    arenas_t arena;
};

struct link_difficulty_s {
    char *str;
    ai_levels_t level;
};

struct link_fighter_s {
    char *str;
    fighters_t fighter;
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
        .str = "bar",
        .arena = BAR
    },
    {
        .str = "sus",
        .arena = SUS
    },
    {
        NULL,
        ARENA_END,
    }
};

static const struct link_fighter_s LINK_FIGHTER[] = {
    {
        .str = "big_dude",
        .fighter = BIG_DUDE
    },
    {
        .str = "eagle",
        .fighter = EAGLE
    },
    {
        .str = "blue_girl",
        .fighter = BLUE_GIRL
    },
    {
        .str = "black_guy",
        .fighter = BLACK_GUY
    },
    {
        NULL,
        FIGHTER_END,
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
