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

    status.status_clock = sfClock_create();
    status.escape_clock = sfClock_create();
    status.is_valid = true;
    return status;
}

void destroy_status(status_t *status)
{
    sfClock_destroy(status->status_clock);
    sfClock_destroy(status->escape_clock);
}
