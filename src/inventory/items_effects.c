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

void stamina_regen_orb_effect(stats_t *stats)
{
    stats->stamina_regen_bonus += ORB_MULTIPLIER;
}

void golden_apainyaye_effect(stats_t *stats)
{
    stats->hp_bonus += ORB_MULTIPLIER * 2;
    stats->stamina_bonus += ORB_MULTIPLIER;
    stats->defense_bonus += ORB_MULTIPLIER;
    stats->speed_bonus += ORB_MULTIPLIER;
    stats->strength_bonus += ORB_MULTIPLIER;
}

void tete_de_neuille_effect(stats_t *stats)
{
    stats->hp_bonus += ORB_MULTIPLIER * 0.1;
    stats->stamina_bonus += ORB_MULTIPLIER * 0.1;
    stats->defense_bonus += ORB_MULTIPLIER * 0.1;
    stats->speed_bonus += ORB_MULTIPLIER * 0.1;
    stats->strength_bonus += ORB_MULTIPLIER * 0.1;
}
