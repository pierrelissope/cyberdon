/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** dict
*/

#include "dict.h"

void dict_insert(dict_t **dict, char *key, void *value)
{
    dict_t *new_head = malloc(sizeof(dict_t));

    new_head->key = my_strdup(key);
    new_head->value = value;
    new_head->next = *dict;
    *dict = new_head;
}

bool dict_include(dict_t *dict, char *key)
{
    dict_t *current_dict = dict;

    while (current_dict) {
        if (my_strcmp(current_dict->key, key) == 0)
            return true;
        current_dict = current_dict->next;
    }
    return false;
}

void *dict_get(dict_t *dict, char *key)
{
    dict_t *current_dict = dict;

    while (current_dict) {
        if (my_strcmp(current_dict->key, key) == 0)
            return current_dict->value;
        current_dict = current_dict->next;
    }
    mini_printf("Key '%s' not found\n", key);
    return NULL;
}

void dict_destroy(dict_t *dict, void (*custom_free)(void *))
{
    dict_t *current_dict = dict;
    dict_t *temp = NULL;

    while (current_dict) {
        temp = current_dict;
        current_dict = current_dict->next;
        free(current_dict->key);
        custom_free(current_dict->value);
        free(current_dict);
    }
}
