/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** dict
*/

#include "dict.h"

void *dict_insert(dict_t **dict, int key, void *value)
{
    dict_t *new_head = malloc(sizeof(dict_t));

    if (!new_head || !value) {
        freef("%a%a", new_head, value);
        return NULL;
    }
    new_head->key = key;
    new_head->value = value;
    new_head->next = *dict;
    *dict = new_head;
    return *dict;
}

bool dict_include(dict_t *dict, int key)
{
    dict_t *current_dict = dict;

    while (current_dict) {
        if (current_dict->key == key)
            return true;
        current_dict = current_dict->next;
    }
    return false;
}

void *dict_get(dict_t *dict, int key)
{
    dict_t *current_dict = dict;

    while (current_dict) {
        if (current_dict->key == key)
            return current_dict->value;
        current_dict = current_dict->next;
    }
    mini_printf("Key '%d' not found\n", key);
    return NULL;
}

void dict_destroy(dict_t *dict, void (*custom_free)(void *))
{
    dict_t *current_dict = dict;
    dict_t *temp = NULL;

    while (current_dict) {
        temp = current_dict;
        current_dict = current_dict->next;
        custom_free(current_dict->value);
        free(temp);
    }
}
