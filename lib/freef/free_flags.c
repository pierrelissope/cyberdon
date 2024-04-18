/*
** EPITECH PROJECT, 2023
** mini flags
** File description:
** contains the flags for mini_printf
*/

#include "free_header.h"
#include <stdlib.h>

void flaga(va_list arg)
{
    char *to_free = va_arg(arg, void *);

    if (to_free != NULL)
        free(to_free);
}
