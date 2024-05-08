/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** vector
*/

#include "entity.h"
#include <math.h>

static float get_norm(sfVector2f vector)
{
    return (sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
}

sfVector2f normalize(sfVector2f vector)
{
    float norm = get_norm(vector);

    if (vector.x == 0 && vector.y == 0)
        return vector;
    return (sfVector2f){vector.x / norm, vector.y / norm};
}
