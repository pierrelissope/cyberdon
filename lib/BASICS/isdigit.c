/*
** EPITECH PROJECT, 2024
** RobotFactory
** File description:
** my_isdigit
*/

#include "basics.h"

int my_isdigit(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}
