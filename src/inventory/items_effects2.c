/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** items_functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "entity.h"
#include "struct.h"
#include "inventory.h"

#define ORB_MULTIPLIER 1

void vitality_orb_effect(stats_t *stats)
{
    stats->hp_bonus += ORB_MULTIPLIER * 2;
}

void defense_orb_effect(stats_t *stats)
{
    stats->defense_bonus += ORB_MULTIPLIER;
}

void speed_orb_effect(stats_t *stats)
{
    stats->speed_bonus += ORB_MULTIPLIER;
}

void strength_orb_effect(stats_t *stats)
{
    stats->strength_bonus += ORB_MULTIPLIER;
}

void stamina_orb_effect(stats_t *stats)
{
    stats->stamina_bonus += ORB_MULTIPLIER;
}
