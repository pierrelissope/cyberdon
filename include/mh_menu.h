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
    #define BLACK {0, 0, 0, 255}
    #define WHITE {255, 255, 255, 255}
    #define RED {255, 0, 0, 255}
    #define GREEN {0, 255, 0, 255}
    #define BLUE {0, 0, 255, 255}
    #define PURPLE {32, 0, 64, 255}
    #define TRANSPARENT {0, 0, 0, 0}

typedef struct button_s {
    sfSprite *sprite;
    sfTexture *pictogramme_texture;
    sfRectangleShape *shape;
    sfText *text;
    sfText *desc;
} button_t;

typedef struct rect_s {
    sfVector2f position;
    sfVector2f size;
    sfSprite *image;
} rect_t;

typedef struct button_init_s {
    sfVector2f position;
    sfVector2f size;
    sfColor text_color;
    sfColor fill_color;
    sfColor desc_color;
    sfColor outline_color;
    char *text;
    char *desc;
} button_init_t;

typedef struct rect_init_s {
    sfVector2f position;
    sfVector2f size;
    sfVector2f image_size;
    sfSprite *image;
} rect_init_t;

typedef enum buttons_e {
    PLAY,
    NEW_GAME,
    LOAD,
    LEAVE,
    SETTINGS,
    VOLUME,
    CONTROLS,
    BACK,
    NUM_BUTTONS,
    HAUT,
    BAS,
    GAUCHE,
    DROIT
} buttons_t;

typedef struct param_button_s {
    sfRectangleShape *shape;
    sfText *text;
} param_button_t;

typedef struct param_init_s {
    sfVector2f position;
    sfVector2f size;
    sfColor text_color;
    sfColor fill_color;
    char *text;
} param_init_t;

static const rect_init_t RECT_INIT[] = {
    [PLAY] = {
        .position = {149, 252},
        .image = NULL
    },
    [NEW_GAME] = {
        .position = {472, 252},
        .image = NULL
    },
    [LOAD] = {
        .position = {795, 252},
        .image = NULL
    },
    [SETTINGS] = {
        .position = {1118, 252},
        .image = NULL
    },
    [LEAVE] = {
        .position = {1441, 252},
        .image = NULL
    },
};

static const button_init_t BUTTON_INIT[] = {
    [PLAY] = {
        .position = {149, 745},
        .size = {320, 82},
        .fill_color = WHITE,
        .text_color = BLACK,
        .desc_color = PURPLE,
        .outline_color = TRANSPARENT,
        .text = "PLAY",
        .desc = "Resume last game"
    },
    [NEW_GAME] = {
        .position = {472, 745},
        .size = {320, 82},
        .fill_color = WHITE,
        .text_color = BLACK,
        .desc_color = PURPLE,
        .outline_color = TRANSPARENT,
        .text = "NEW GAME",
        .desc = "Start a new game"
    },
    [LOAD] = {
        .position = {795, 745},
        .size = {320, 82},
        .fill_color = WHITE,
        .text_color = BLACK,
        .desc_color = PURPLE,
        .outline_color = TRANSPARENT,
        .text = "SAVE GAME",
        .desc = "Save your data"
    },
    [SETTINGS] = {
        .position = {1118, 745},
        .size = {320, 82},
        .fill_color = WHITE,
        .text_color = BLACK,
        .desc_color = PURPLE,
        .outline_color = TRANSPARENT,
        .text = "SETTINGS",
        .desc = "Personalize your experience"
    },
    [LEAVE] = {
        .position = {1441, 745},
        .size = {320, 82},
        .fill_color = WHITE,
        .text_color = BLACK,
        .desc_color = PURPLE,
        .outline_color = TRANSPARENT,
        .text = "LEAVE",
        .desc = "Exit Game"
    }
};

typedef struct menu_item_s {
    char *selected_item;
    void (*action)(sfRenderWindow *window,
        game_info_t *game_info, game_t *game);
} menu_item_t;

sfBool is_mouse_over_button(sfRenderWindow *window, button_t button);
void handle_button_click(game_t *game, button_t *buttons);
sfRectangleShape* create_button_shape(const button_init_t *button_init);
sfText* create_button_text(const sfFont *font,
    const button_init_t *button_init, const sfVector2f position);
sfSprite* create_button_sprite(const char *image_path,
    const sfVector2f position);
button_t create_button(sfFont *font, button_init_t *button_init,
    const char *image_path);
rect_t create_rect(const rect_init_t *rect_init, char *path);
void draw_button(sfRenderWindow *window, button_t button);
void destroy_button(button_t button);
sfRenderWindow *init_window();
sfSprite *load_background(const char *image_path);
sfText *create_hover_text(sfFont *font);
void init_buttons(button_t *buttons, sfFont *font);
void init_rects(rect_t *rects);

sfRectangleShape *create_rectangle(void);
void menu(game_t *game);
void parametres(sfRenderWindow *window, game_info_t *game_info, game_t *game);
void blink(sfClock *clock, sfRectangleShape *rect);
void draw_menu(sfRenderWindow *window,
    sfRectangleShape *rect, int *selected_item, menu_item_t *ptr_fct);
sfText *create_text_mh(char *string, sfVector2f position,
    sfFont *font, bool is_selected);
bool my_hover(sfRenderWindow *window, sfText *text);
void clear_menu(sfText *param_text, sfText *sound_text,
    sfText *keybind_text, sfText *resize_text);

void init_param_buttons(param_button_t *buttons, sfFont *font);
void draw_param_buttons(sfRenderWindow *window, param_button_t *buttons);
void handle_param_button_click(game_t *game, param_button_t *buttons);
void settings(game_t *game);
void draw_buttons(sfRenderWindow *window, sfSprite *background_sprite,
    button_t *buttons, int nbr_butt);

#endif /* !MENU_H_ */
