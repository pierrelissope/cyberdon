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
    #define SR_X game->game_info->screen_res.x
    #define SR_Y game->game_info->screen_res.y
    #define RPG "MyRPG"
    #define O1 sfClose
    #define O2 sfResize
    #define WIN_CFG { SR_X, SR_Y, 32 }
    #define VID (sfVideoMode)WIN_CFG
    #define WIN_CREATE sfRenderWindow_create(VID, RPG, O1 | O2, NULL)

typedef struct menu_item_s {
    char *selected_item;
    void (*action)(sfRenderWindow *window,
        game_info_t *game_info, game_t *game);
} menu_item_t;

game_info_t *init_game_info(void);
sfRectangleShape *create_rectangle(void);
void menu(game_t *game);
sfText *create_text(char *string, sfVector2f position,
    sfFont *font, bool is_selected);
void parametres(sfRenderWindow *window, game_info_t *game_info);
void blink(sfClock *clock, sfRectangleShape *rect);
void draw_menu(sfRenderWindow *window,
    sfRectangleShape *rect, int *selected_item, menu_item_t *ptr_fct);
#endif /* !MENU_H_ */
