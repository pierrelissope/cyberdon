/*
** EPITECH PROJECT, 2023
** header for mini printf
** File description:
** stores my structs
*/

#pragma once
#include <stdarg.h>
#include <unistd.h>

void flaga(va_list arg);
void flagtabf(va_list arg);

typedef struct flags {
    char c;
    void (*func)(va_list);
} flagos_t;

static const flagos_t flag_arr[] = {
    {'a', flaga},
    {'t', flagtabf},
    {0, NULL}
};
