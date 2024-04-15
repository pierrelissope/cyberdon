/*
** EPITECH PROJECT, 2024
** RobotFactory
** File description:
** my_strchr
*/

#include "basics.h"

char *my_strchr(char *str, int c)
{
    if (str == NULL) {
        my_fputstr("Error: str is NULL", 2);
        return NULL;
    }
    while (*str != c && *str != '\0')
        str++;
    return str;
}

char *encadred_by(char *str, int c)
{
    char *ptr = my_strchr(str, c) + 1;
    int len = 0;

    if (ptr == NULL) {
        my_fputstr("Error: str is NULL", 2);
        return NULL;
    }
    for (char *ctr = ptr; *ctr != c && *ctr != '\0'; ctr++)
        len++;
    return my_strndup(ptr, len);
}
