/*
** EPITECH PROJECT, 2024
** clean str
** File description:
** lib
*/
#include "basics.h"

int cond(char c)
{
    return c == ' ' || c == '\t';
}

char *cleanstr(char *str)
{
    int start_index = 0;
    int end_index = my_strlen(str) - 1;
    int i;

    while (cond(str[start_index]))
        start_index++;
    while (end_index >= 0 && cond(str[end_index]))
        end_index--;
    for (i = 0; i <= end_index - start_index; i++)
        str[i] = str[i + start_index];
    str[i] = '\0';
    return str;
}
