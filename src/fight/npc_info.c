/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** fight loading
*/

#include <string.h>

#include "ai_values.h"
#include "fight_macros.h"
#include "fight.h"
#include "fight_transfer.h"
#include "struct.h"
#include "link_fight.h"

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

fighters_t get_npc_skin(physical_entity_t *npc)
{
    for (size_t i = 0; LINK_FIGHTER[i].str != NULL; ++i)
        if (strcmp(LINK_FIGHTER[i].str, npc->fighter_skin_str) == 0)
            return LINK_FIGHTER[i].fighter;
    return BIG_DUDE;
}
