/*
** EPITECH PROJECT, 2023
** array
** File description:
** array
*/

#include "basics.h"
#include <string.h>

char *concat_mem(char *str1, char *str2, char *str3)
{
    int size = 0;
    char *new_str = NULL;

    if (str1 != NULL)
        size += my_strlen(str1);
    if (str2 != NULL)
        size += my_strlen(str2);
    if (str3 != NULL)
        size += my_strlen(str3);
    new_str = calloc(size + 1, sizeof(char));
    if (new_str == NULL)
        return NULL;
    if (str1 != NULL)
        strcat(new_str, str1);
    if (str2 != NULL)
        strcat(new_str, str2);
    if (str3 != NULL)
        strcat(new_str, str3);
    return new_str;
}
