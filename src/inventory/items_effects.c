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
