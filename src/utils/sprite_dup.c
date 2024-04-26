/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** sprite_dup
*/

#include "basics.h"
#include "entity.h"
#include "dict.h"

dict_t *dup_sprites(dict_t *dict)
{
    dict_t *new_dict = NULL;
    dict_t *node = dict;
    sfSprite *new_sprite = NULL;

    while (node) {
        new_sprite = sfSprite_create();
        if (!new_sprite)
            return NULL;
        sfSprite_setTexture(new_sprite, node->value, sfTrue);
        dict_insert(&new_dict, node->key, new_sprite);
        node = node->next;
    }
    return new_dict;
}
