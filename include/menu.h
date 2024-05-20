/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** menu
*/

#include <SFML/Graphics.h>
#include <stdbool.h>


#ifndef MENU_H_
    #define MENU_H_

typedef struct game_info {
    char *save_file;
    sfVector2u screen_res;
} game_info_t;

typedef struct menu_item_s {
    char *selected_item;
    void (*action)(sfRenderWindow *window, game_info_t *game_info);
} menu_item_t;

sfRectangleShape *create_rectangle(void);
void menu(game_info_t *game_info);
sfText *create_text(char *string, sfVector2f position,
    sfFont *font, bool is_selected);
void parametres(sfRenderWindow *window, game_info_t *game_info);
void blink(sfClock *clock, sfRectangleShape *rect);
#endif /* !MENU_H_ */
