/*
** EPITECH PROJECT, 2023
** mini printf real
** File description:
** the REAL deal
*/

#include "freef.h"
#include "free_header.h"
#include <stdarg.h>

static void flag_checker(char c, va_list list)
{
    int counter = 0;

    while (flag_arr[counter].c != 0) {
        if (flag_arr[counter].c == c) {
            flag_arr[counter].func(list);
        }
        counter++;
    }
}

void freef(const char *format, ...)
{
    va_list list;
    int strcounter = 0;

    va_start(list, format);
    while (format[strcounter]) {
        if (format[strcounter] == '%') {
            strcounter++;
            flag_checker(format[strcounter], list);
        }
        strcounter++;
    }
    va_end(list);
}
