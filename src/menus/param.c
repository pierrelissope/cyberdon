/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-tanvir-mahtab.miah
** File description:
** param
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include "menu.h"
#include "game.h"
#include <stdbool.h>

void anti_major_f4(sfRenderWindow *window, int ci_si[],
    game_info_t *game_info, char size_text[])
{
    sfText *param_text = create_text("Parametres",
        (sfVector2f){850, 500}, game_info->font, ci_si[0] == 0);
    sfText *resize_text = create_text(size_text,
        (sfVector2f){850, 560}, game_info->font, ci_si[0] == 1);

    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawText(window, param_text, NULL);
    sfRenderWindow_drawText(window, resize_text, NULL);
    sfRenderWindow_display(window);
    sfText_destroy(resize_text);
}

int my_if(sfEvent event, int ci_si[])
{
    if (event.type == sfEvtClosed ||
        (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape))
        return 1;
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown)
        ci_si[0] = (ci_si[0] + 1) % 2;
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp)
        ci_si[0] = (ci_si[0] - 1 + 2) % 2;
    if (event.type == sfEvtKeyPressed &&
        event.key.code == sfKeyRight && ci_si[0] == 1)
        ci_si[1] = (ci_si[1] + 1) % 3;
    if (event.type == sfEvtKeyPressed &&
        event.key.code == sfKeyLeft && ci_si[0] == 1)
        ci_si[1] = (ci_si[1] - 1 + 3) % 3;
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn) {
        if (ci_si[0] == 0)
            return 1;
        if (ci_si[0] == 1)
            return 2;
    }
    return 0;
}

int my_call_if(sfEvent event, int ci_si[],
    game_info_t *game_info, sfRenderWindow *window)
{
    sfVector2u new_size;

    if (my_if(event, ci_si) == 1) {
        return 1;
    } else if (my_if(event, ci_si) == 2) {
        new_size = game_info->sizes[ci_si[1]];
        game_info->screen_res.x = new_size.x;
        game_info->screen_res.y = new_size.y;
        sfRenderWindow_setSize(window, new_size);
    }
    return 0;
}

void parametres(sfRenderWindow *window, game_info_t *game_info)
{
    sfText *param_text = create_text("Parametres",
        (sfVector2f){850, 500}, game_info->font, false);
    sfClock *clock = sfClock_create();
    int ci_si[2] = {1, 0};
    sfEvent event;
    char size_text[32];
    int my_if = 0;

    while (sfRenderWindow_isOpen(window) && my_if == 0) {
        while (sfRenderWindow_pollEvent(window, &event) && my_if == 0)
            my_if = my_call_if(event, ci_si, game_info, window);
        snprintf(size_text, sizeof(size_text), "Resize: %ux%u",
            game_info->sizes[ci_si[1]].x,
            game_info->sizes[ci_si[1]].y);
        anti_major_f4(window, ci_si, game_info, size_text);
    }
    sfText_destroy(param_text);
    sfClock_destroy(clock);
}
