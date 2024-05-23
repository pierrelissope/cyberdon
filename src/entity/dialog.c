/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** entities
*/

#include "dict.h"
#include "string.h"
#include "entity.h"
#include "init_texture.h"
#include "inventory.h"
#include "dialog.h"
#include "myutils.h"

static sfEventType dialog_event(sfRenderWindow *window, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return sfEvtClosed;
        }
        if (event->type ==sfEvtKeyPressed)
            return sfEvtCount;
    }
    return sfEvtClosed;
}

void position_text_in_box(sfText *text, sfRectangleShape *box) 
{
    sfFloatRect text_rect = sfText_getLocalBounds(text);
    sfVector2f box_position = sfRectangleShape_getPosition(box);
    sfVector2f box_size = sfRectangleShape_getSize(box);

    sfText_setOrigin(text,
        (sfVector2f){text_rect.width / 2, text_rect.height / 2});
    sfText_setPosition(text, (sfVector2f){box_position.x + box_size.x / 2,
        box_position.y + box_size.y / 2});
}

sfText* create_dialogue_text(sfRenderWindow *window, char* dialog,
    sfRectangleShape *box, sfFont *font) 
{
    char *dialogue = strdup(dialog);
    sfText* text = sfText_create();
    sfClock* clock = sfClock_create();
    int i = 0;
    int dialog_length = strlen(dialogue);
    char save_char = 0;

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 50);
    sfText_setColor(text, sfBlack);
    while (sfRenderWindow_isOpen(window) && i <= dialog_length) {
        save_char = dialogue[i];
        dialogue[i] = '\0';
        sfText_setString(text, dialogue);
        position_text_in_box(text, box);
        while (sfTime_asMilliseconds(sfClock_getElapsedTime(clock)) < 5);
        sfClock_restart(clock);
        sfRenderWindow_drawRectangleShape(window, box, NULL);
        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_display(window);
        dialogue[i] = save_char;
        i++;
    }
    free(dialogue);
    sfClock_destroy(clock);
    return text;
}

sfRectangleShape *create_dialogue_box(sfVector2u window_size) 
{
    sfRectangleShape* box = sfRectangleShape_create();
    sfVector2f box_size = {window_size.x * 0.8f, window_size.y * 0.3f};
    sfVector2f box_position = {window_size.x * 0.1f, window_size.y * 0.65f};

    if (!box)
        exit(EXIT_FAILURE);
    sfRectangleShape_setSize(box, box_size);
    sfRectangleShape_setFillColor(box, sfColor_fromRGB(255, 255, 255));
    sfRectangleShape_setPosition(box, box_position);
    return box;
}

void displayDialogue(sfRenderWindow *window, char *dialog,
    sfFont *font, sfEvent *event) 
{
    sfRectangleShape *box = create_dialogue_box((sfVector2u){1920, 1080});
    sfText *text = create_dialogue_text(window, dialog, box, font);
    sfClock *clock = sfClock_create();

    while (sfRenderWindow_isOpen(window)) {
        if (dialog_event(window, event) == sfEvtCount &&
            sfTime_asMilliseconds(sfClock_getElapsedTime(clock)) > 200)
            break;
        sfRenderWindow_drawRectangleShape(window, box, NULL);
        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_display(window);
    }
    sfClock_destroy(clock);
    sfText_destroy(text);
    sfRectangleShape_destroy(box);
}
