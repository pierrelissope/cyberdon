/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** menu
*/

#include <SFML/Graphics.h>
#include <stdbool.h>
#include "struct.h"


#ifndef MENU_H_
    #define MENU_H_
    #define ITM_COUNT 3

typedef struct menu_item_s {
    char *selected_item;
    void (*action)(sfRenderWindow *window, game_info_t *game_info);
} menu_item_t;

game_info_t *init_game_info(void);
sfRectangleShape *create_rectangle(void);
void menu(game_t *game, int specifier);
sfText *create_text(char *string, sfVector2f position,
    sfFont *font, bool is_selected);
void parametres(sfRenderWindow *window, game_info_t *game_info);
void blink(sfClock *clock, sfRectangleShape *rect);
void draw_menu(sfRenderWindow *window,
    sfRectangleShape *rect, int *selected_item, menu_item_t *ptr_fct);
#endif /* !MENU_H_ */
