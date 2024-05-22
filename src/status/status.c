/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** status
*/

#include "entity.h"
#include "status.h"

status_t init_status(void)
{
    status_t status = {0};

    status.teleportation_clock = sfClock_create();
    status.is_valid = true;
    return status;
}

void destroy_status(status_t *status)
{
    sfClock_destroy(status->teleportation_clock);
}
