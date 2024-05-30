/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-tanvir-mahtab.miah
** File description:
** param
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Types.h>
#include <SFML/Window/Event.h>
#include <stdio.h>
#include "mh_menu.h"
#include "struct.h"
#include <stdbool.h>

static void anti_major_f4(sfRenderWindow *window, int ci_si[],
    game_info_t *game_info, char size_text[32])
{
    sfText *param_text = create_text_mh("Parametres",
        (sfVector2f){900, 400}, game_info->font, ci_si[0] == 0);
    sfText *resize_text = create_text_mh(size_text,
        (sfVector2f){900, 500}, game_info->font, ci_si[0] == 1);
    sfText *keybind_text = create_text_mh("Keybindings",
        (sfVector2f){900, 600}, game_info->font, ci_si[0] == 2);
    sfText *sound_text = NULL;
    char level[200] = {0};

    sprintf(level, "Sound: %d", game_info->sound_level);
    sound_text = create_text_mh(level,
        (sfVector2f){900, 700}, game_info->font, ci_si[0] == 3);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawText(window, param_text, NULL);
    sfRenderWindow_drawText(window, resize_text, NULL);
    sfRenderWindow_drawText(window, keybind_text, NULL);
    sfRenderWindow_drawText(window, sound_text, NULL);
    sfRenderWindow_display(window);
    clear_menu(param_text, sound_text, keybind_text, resize_text);
}

static void check_key_events(sfEvent *event,
    game_info_t *game_info, int ci_si[])
{
    if (event->type == sfEvtKeyPressed &&
        event->key.code == game_info->key[MOVE_DOWN])
        ci_si[0] = (ci_si[0] + 1) % 4;
    if (event->type == sfEvtKeyPressed &&
        event->key.code == game_info->key[MOVE_UP])
        ci_si[0] = (ci_si[0] - 1 + 4) % 4;
    if (event->type == sfEvtKeyPressed &&
        event->key.code == game_info->key[MOVE_RIGHT] && ci_si[0] == 1)
        ci_si[1] = (ci_si[1] + 1) % 3;
    if (event->type == sfEvtKeyPressed &&
        event->key.code == game_info->key[MOVE_LEFT] && ci_si[0] == 1)
        ci_si[1] = (ci_si[1] - 1 + 3) % 3;
    if (event->type == sfEvtKeyPressed &&
        event->key.code == game_info->key[MOVE_LEFT] && ci_si[0] == 3)
        game_info->sound_level = (game_info->sound_level - 1 + 100) % 100;
    if (event->type == sfEvtKeyPressed &&
        event->key.code == game_info->key[MOVE_RIGHT] && ci_si[0] == 3)
        game_info->sound_level = (game_info->sound_level + 1) % 100;
}

static int my_if(sfEvent *event, game_info_t *game_info, int ci_si[])
{
    if (event->type == sfEvtClosed ||
        (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape))
        return 1;
    check_key_events(event, game_info, ci_si);
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyReturn) {
        if (ci_si[0] < 0 || ci_si[0] > 3)
            return 84;
        return ci_si[0] + 1;
    }
    return 0;
}

static void my_keybinding_two(sfRenderWindow *window,
    game_info_t *game_info, char *action_name)
{
    char msg[100];
    sfText *msg_csfml = create_text_mh("Press a new key for ",
        (sfVector2f){900, 450}, game_info->font, false);

    snprintf(msg, 100, "Press a new key for %s", action_name);
    sfText_setString(msg_csfml, msg);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawText(window, msg_csfml, NULL);
    sfRenderWindow_display(window);
    sfText_destroy(msg_csfml);
}

static int get_new_key(sfRenderWindow *window)
{
    sfEvent event;

    while (sfRenderWindow_waitEvent(window, &event))
        if (event.type == sfEvtKeyPressed)
            return event.key.code;
    return 0;
}

static void my_keybinding(sfRenderWindow *window,
    game_info_t *game_info)
{
    char *mvt[NUM] = {"Move up", "Move down",
        "Move left", "Move right"};

    for (int i = 0; i < NUM; i++) {
        my_keybinding_two(window, game_info, mvt[i]);
        game_info->key[i] = get_new_key(window);
    }
}

static int my_call_if(sfEvent *event, int ci_si[],
    game_info_t *game_info, game_t *game)
{
    sfVector2u new_size;
    int result = my_if(event, game_info, ci_si);

    if (result == 1)
        return 1;
    if (result == 2) {
        new_size = game_info->sizes[ci_si[1]];
        game_info->screen_res.x = new_size.x;
        game_info->screen_res.y = new_size.y;
        sfRenderWindow_setSize(game->window, new_size);
    }
    if (result == 3)
        my_keybinding(game->window, game_info);
    if (result == 4)
        sfMusic_setVolume(game->sfx.ost, game_info->sound_level);
    return 0;
}

static void end_menu(sfText *param_text, sfClock *clock)
{
    sfText_destroy(param_text);
    sfClock_destroy(clock);
}

static void play_sfx(sfEvent *event, game_t *game)
{
    if (event->type == sfEvtKeyPressed &&
        (event->key.code == sfKeyLeft ||
        event->key.code == sfKeyRight || event->key.code == sfKeyUp ||
        event->key.code == sfKeyDown))
        sfMusic_play(game->sfx.effect);
}

void parametres(sfRenderWindow *window, game_info_t *game_info, game_t *game)
{
    sfText *param_text = create_text_mh("Parametres",
        (sfVector2f){900, 450}, game_info->font, false);
    sfClock *clock = sfClock_create();
    int ci_si[2] = {1, 0};
    sfEvent event;
    char size_text[32];
    int my_if = 0;

    while (sfRenderWindow_isOpen(window) && my_if == 0) {
        while (sfRenderWindow_pollEvent(window, &event) && my_if == 0) {
            my_if = my_call_if(&event, ci_si, game_info, game);
            play_sfx(&event, game);
        }
        snprintf(size_text, sizeof(size_text), "Resize: %ux%u",
            game_info->sizes[ci_si[1]].x,
            game_info->sizes[ci_si[1]].y);
        anti_major_f4(window, ci_si, game_info, size_text);
    }
    end_menu(param_text, clock);
}
