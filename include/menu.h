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
    #define ITM_COUNT 3

typedef struct game_info {
    char *save_file;
    sfVector2u screen_res;
    sfVector2u sizes[3];
    sfFont *font;
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
void draw_menu(sfRenderWindow *window,
    sfRectangleShape *rect, int *selected_item);
#endif /* !MENU_H_ */
