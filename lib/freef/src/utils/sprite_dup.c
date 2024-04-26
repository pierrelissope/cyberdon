/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** sprite_dup
*/

#include "basics.h"
#include "entity.h"
#include "dict.h"

sfSprite **dup_sprites(dict_t *dict)
{
    sfSprite **new_array = NULL;
    dict_t *node = dict;
    sfSprite *new_sprite = NULL;

    while (node) {
        new_sprite = sfSprite_create();
        if (!new_sprite)
            return NULL;
        sfSprite_setTexture(new_sprite, node->value, sfTrue);
        append_ptr((void ***)&new_array, new_sprite, NULL);
        if (!new_array)
            return NULL;
        node = node->next;
    }
    return new_array;
}
