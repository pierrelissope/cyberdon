/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** pos_converter
*/

#include "entity.h"

const int X_OFFSET = 65;
const int Y_OFFSET = 33;
const int Z_OFFSET = 40;
const int CORNER_PADDING = 450;

sfVector2f isom_pos_converter(sfVector2f pos)
{
    sfVector2f newpos = {
        CORNER_PADDING + pos.x * X_OFFSET - pos.y * X_OFFSET,
        CORNER_PADDING + pos.x * Y_OFFSET + pos.y * Y_OFFSET
    };

    return newpos;
}

sfVector2f isom_pos_converter_z(sfVector2f pos)
{
    sfVector2f newpos = {
        CORNER_PADDING + pos.x * X_OFFSET - pos.y * X_OFFSET,
        CORNER_PADDING + pos.x * Y_OFFSET + pos.y * Y_OFFSET - Z_OFFSET
    };

    return newpos;
}
