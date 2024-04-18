/*
** EPITECH PROJECT, 2024
** mini prinf
** File description:
** fucntions for printing arrays
*/

#include "free_header.h"
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <stdlib.h>

void flagtabf(va_list arg)
{
    void **tab = va_arg(arg, void **);

    for (int i = 0; tab && tab[i] != NULL; i++) {
        if (tab[i] != NULL)
            free(tab[i]);
    }
    if (tab != NULL)
        free(tab);
}

void freesprite(va_list arg)
{
    sfSprite *sprite = va_arg(arg, sfSprite *);

    if (sprite)
        sfSprite_destroy(sprite);
}
