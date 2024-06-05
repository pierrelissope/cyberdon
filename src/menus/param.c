#include "mh_menu.h"
#include "game.h"
#include <stdio.h>
#include <SFML/Graphics.h>
#include <SFML/Window/Event.h>


sfText *create_text_mh(char *string, sfVector2f position,
    sfFont *font, bool is_selected)
{
    sfText *text = sfText_create();

    sfText_setString(text, string);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, is_selected ? 80 : 50);
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, position);
    return text;
}

void draw_param_elements(sfRenderWindow *window, sfText **texts, int selected)
{
    sfRenderWindow_clear(window, sfBlack);
    for (int i = 0; i < 4; i++) {
        sfText_setColor(texts[i], (i == selected) ? sfRed : sfWhite);
        sfRenderWindow_drawText(window, texts[i], NULL);
    }
    sfRenderWindow_display(window);
}

void update_param_texts(sfText **texts, game_info_t *game_info, int *ci_si)
{
    char size_text[32];
    char sound_text[32];

    snprintf(size_text, sizeof(size_text), "Resize: %ux%u",
        game_info->sizes[ci_si[1]].x, game_info->sizes[ci_si[1]].y);
    snprintf(sound_text, sizeof(sound_text),
        "Sound: %d", game_info->sound_level);
    sfText_setString(texts[0], "Parametres");
    sfText_setString(texts[1], size_text);
    sfText_setString(texts[2], "Keybindings");
    sfText_setString(texts[3], sound_text);
}

void handle_key_events(sfEvent *event, game_info_t *game_info, int *ci_si)
{
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == game_info->key[MOVE_DOWN])
            ci_si[0] = (ci_si[0] + 1) % 4;
        else if (event->key.code == game_info->key[MOVE_UP])
            ci_si[0] = (ci_si[0] - 1 + 4) % 4;
        else if (event->key.code == game_info->key[MOVE_RIGHT] && ci_si[0] == 1)
            ci_si[1] = (ci_si[1] + 1) % 3;
        else if (event->key.code == game_info->key[MOVE_LEFT] && ci_si[0] == 1)
            ci_si[1] = (ci_si[1] - 1 + 3) % 3;
        else if (event->key.code == game_info->key[MOVE_LEFT] && ci_si[0] == 3)
            game_info->sound_level = (game_info->sound_level - 1 + 100) % 100;
        else if (event->key.code == game_info->key[MOVE_RIGHT] && ci_si[0] == 3)
            game_info->sound_level = (game_info->sound_level + 1) % 100;
    }
}

void keybinding_menu(sfRenderWindow *window, game_info_t *game_info)
{
    char *actions[] = {"Move up", "Move down", "Move left", "Move right"};
    char message[100];
    sfEvent event;
    sfText *prompt = create_text_mh("Press a new key for",
        (sfVector2f){900, 450}, game_info->font, false);

    for (int i = 0; i < 4; i++) {
        snprintf(message, 100, "Press a new key for %s", actions[i]);
        sfText_setString(prompt, message);
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawText(window, prompt, NULL);
        sfRenderWindow_display(window);
        sfText_destroy(prompt);
        while (sfRenderWindow_waitEvent(window, &event)) {
            if (event.type == sfEvtKeyPressed) {
                game_info->key[i] = event.key.code;
                break;
            }
        }
    }
}

void parametres(sfRenderWindow *window, game_info_t *game_info, game_t *game)
{
    sfText *texts[4];
    int ci_si[2] = {0, 0};
    sfEvent event;
    sfVector2u new_size;

    texts[0] = create_text_mh("Parametres",
        (sfVector2f){900, 400}, game_info->font, false);
    texts[1] = create_text_mh("",
        (sfVector2f){900, 500}, game_info->font, false);
    texts[2] = create_text_mh("Keybindings",
        (sfVector2f){900, 600}, game_info->font, false);
    texts[3] = create_text_mh("",
        (sfVector2f){900, 700}, game_info->font, false);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed ||
                (event.type == sfEvtKeyPressed &&
                event.key.code == sfKeyEscape))
                return;
            handle_key_events(&event, game_info, ci_si);
            if (event.type == sfEvtKeyPressed &&
                event.key.code == sfKeyReturn) {
                if (ci_si[0] == 2)
                    keybinding_menu(window, game_info);
                if (ci_si[0] == 1) {
                    new_size = game_info->sizes[ci_si[1]];
                    game_info->screen_res = new_size;
                    sfRenderWindow_setSize(window, new_size);
                }
                if (ci_si[0] == 3)
                    sfMusic_setVolume(game->sfx.ost, game_info->sound_level);
            }
        }
        update_param_texts(texts, game_info, ci_si);
        draw_param_elements(window, texts, ci_si[0]);
    }
    for (int i = 0; i < 4; i++)
        sfText_destroy(texts[i]);
}
