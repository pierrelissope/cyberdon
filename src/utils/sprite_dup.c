/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** sprite_dup
*/

#include "basics.h"
#include "entity.h"
#include "dict.h"

sfSprite **dup_sprites(sfTexture **array)
{
    sfSprite **new_array = NULL;
    sfSprite *new_sprite = NULL;

    for (int i = 0; array && array[i]; i++) {
        new_sprite = sfSprite_create();
        sfSprite_setTexture(new_sprite, array[i], sfTrue);
        append_ptr((void ***)&new_array, new_sprite, NULL);
    }
    return new_array;
}
