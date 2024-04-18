/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** basics
*/

#pragma once

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void freef(const char *format, ...);
char *open_file(char *filepath);
void *smalloc(size_t size);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
int my_putstr(char const *str);
int my_put_nbr(long n);
int display_var2(va_list args, char *str, int i);
int isntvar(char *str, int i);
int my_putchar(char c);
int my_atoi(char const *str, int i);
char *my_strdup(char const *str);
void *my_memcpy(void *dest, const void *source, size_t n);
void *my_realloc(void *ptr, size_t old_size, size_t new_size);
char **my_str_to_all_array(char *str, char *separators);
int str_begin_with(char *str, char *find);
void free_str_array(char **array);
char *concat_mem(char *str1, char *str2, char *str3);
int my_strcmp(char const *s1, char const *s2);
int mini_printf(char *str, ...);
int my_putstr_array(char **array);
char **my_strdup_array(char **array);
int my_arraylen(void **array);
void my_fputstr(char const *str, int fd);
char *my_strndup(char const *str, int n);
char *my_strchr(char *str, int c);
char *encadred_by(char *str, int c);
void **append_ptr(void ***ptr, void *entity, int *len);
void **remove_ptr(void ***ptr, int index, int *len);
int my_strncmp(char const *s1, char const *s2, int n);
char *cleanstr(char *str);
int my_strlen_array(char **array);
int char_in_str(char c, char *str);
int my_isdigit(const char *str);
char *my_strstr(char *fullstring, char *substring);
void **remove_from_array(void ***ptr, int index, int *len);
char *my_itoa(int nb);
