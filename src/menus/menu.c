/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** menu
*/

#include <SFML/Graphics.h>
#include <SFML/Window/Event.h>
#include <stdio.h>
#include <stdbool.h>
#include "struct.h"
#include "mh_menu.h"
#include "game.h"
#include "xp.h"
#include "basics.h"


void init_rects(rect_t *rects)
{
    rects[0] = create_rect(&RECT_INIT[PLAY], "assets/menu/test.png");
    rects[1] = create_rect(&RECT_INIT[NEW_GAME], "assets/menu/test2.png");
    rects[2] = create_rect(&RECT_INIT[LOAD], "assets/menu/test3.png");
    rects[3] = create_rect(&RECT_INIT[LEAVE], "assets/menu/test5.png");
    rects[4] = create_rect(&RECT_INIT[SETTINGS], "assets/menu/test4.png");
}

void draw_buttons(sfRenderWindow *window, sfSprite *background_sprite,
    button_t *buttons, int nbr_butt)
{
    sfRenderWindow_drawSprite(window, background_sprite, NULL);
    for (int i = 0; i < nbr_butt; i++)
        draw_button(window, buttons[i]);
}

void draw_rects(sfRenderWindow *window, rect_t *rects)
{
    for (int i = 0; i < 5; i++)
        sfRenderWindow_drawSprite(window, rects[i].image, NULL);
}

void update_hover_text(sfRenderWindow *window, sfText *hover_text,
    button_t *buttons, int nbr_butt)
{
    const char *texts[] = {
        BUTTON_INIT[PLAY].text,
        BUTTON_INIT[NEW_GAME].text,
        BUTTON_INIT[LOAD].text,
        BUTTON_INIT[LEAVE].text,
        BUTTON_INIT[SETTINGS].text
    };

    sfText_setString(hover_text, "");
    for (int i = 0; i < nbr_butt; i++) {
        if (is_mouse_over_button(window, buttons[i])) {
            sfText_setString(hover_text, texts[i]);
            break;
        }
    }
}

void destroyer(sfText *txt, button_t buttons[], int nbr_butt)
{
    for (int i = 0; i < nbr_butt; i++)
        destroy_button(buttons[i]);
    sfText_destroy(txt);
}

void menu(game_t *game)
{
    sfSprite *background_sprite = load_background("assets/background.png");
    sfText *hover_text = create_hover_text(game->font);
    button_t buttons[5];
    rect_t rects[5];
    sfEvent event;

    init_rects(rects);
    init_buttons(buttons, game->font);
    while (sfRenderWindow_isOpen(game->window) &&
        game->game_state == IN_MENU) {
        while (sfRenderWindow_pollEvent(game->window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(game->window);
            else if (event.type == sfEvtMouseButtonPressed &&
                event.mouseButton.button == sfMouseLeft)
                handle_button_click(game, buttons);
        }
        sfRenderWindow_clear(game->window, sfBlack);
        draw_buttons(game->window, background_sprite, buttons, 5);
        draw_rects(game->window, rects);
        update_hover_text(game->window, hover_text, buttons, 5);
        sfRenderWindow_drawText(game->window, hover_text, NULL);
        sfRenderWindow_display(game->window);
    }
    destroyer(hover_text, buttons, 5);
}
