/*
** EPITECH PROJECT, 2023
** array
** File description:
** array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basics.h"

int char_in_str(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (c == str[i])
            return 1;
    return 0;
}

static int get_word_len(char *str, char *separators)
{
    int word_len = 0;

    for (char *ptr = str; *ptr != '\0' &&
        !char_in_str(*ptr, separators); ptr++)
        word_len++;
    return word_len;
}

char **my_str_to_all_array(char *str, char *separators)
{
    int word_len = 0;
    char **array = NULL;

    if (!str || !separators)
        return NULL;
    for (char *ptr = str; *ptr != '\0'; ptr++) {
        word_len = get_word_len(ptr, separators);
        if (word_len == 0)
            continue;
        if (!append_ptr((void ***)&array, my_strndup(ptr, word_len), NULL))
            return NULL;
        ptr += word_len - 1;
    }
    if (!append_ptr((void ***)&array, NULL, NULL))
        return NULL;
    return array;
}
