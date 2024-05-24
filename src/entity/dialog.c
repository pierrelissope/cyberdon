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

static int handle_dialog_events(
    sfRenderWindow *window, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return sfEvtClosed;
        }
        if (event->type == sfEvtKeyPressed)
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

static void setup_text(sfText *text, game_t *game)
{
    sfText_setFont(text, game->font);
    sfText_setCharacterSize(text, 50);
    sfText_setColor(text, sfBlack);
}

static void process_dialog_animation(game_t *game, sfSprite *sprite,
    sfText *text, sfRectangleShape *box)
{
    position_text_in_box(text, box);
    sfRenderWindow_drawRectangleShape(game->window, box, NULL);
    sfRenderWindow_drawText(game->window, text, NULL);
    sfRenderWindow_drawSprite(game->window, sprite, NULL);
    sfRenderWindow_display(game->window);
}

sfText* create_dialog_text(game_t *game, char *dialog,
    sfRectangleShape *box, sfSprite *sprite)
{
    char *dialogue = strdup(dialog);
    sfText* text = sfText_create();
    sfClock* clock = sfClock_create();
    int dialog_length = strlen(dialogue);
    char save_char = 0;

    setup_text(text, game);
    for (int i = 0; sfRenderWindow_isOpen(game->window) &&
        i <= dialog_length; ++i) {
        save_char = dialogue[i];
        dialogue[i] = '\0';
        sfText_setString(text, dialogue);
        while (sfTime_asMilliseconds(sfClock_getElapsedTime(clock)) < 5);
        sfClock_restart(clock);
        process_dialog_animation(game, sprite, text, box);
        dialogue[i] = save_char;
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

static sfSprite *draw_entity_portrait(physical_entity_t *entity)
{
    sfSprite *sprite = sfSprite_copy(entity->current_sprite_sheet);

    sfSprite_setScale(sprite, (sfVector2f){4, 4});
    sfSprite_setTextureRect(sprite, (sfIntRect){0, 0, 128, 86});
    sfSprite_setPosition(sprite, (sfVector2f){350, 1550});
    return sprite;
}

void display_dialogue(game_t *game, char *dialog,
    physical_entity_t *npc, sfEvent *event)
{
    sfSprite *sprite = draw_entity_portrait(npc);
    sfRectangleShape *box = create_dialogue_box((sfVector2u){1920, 1080});
    sfText *text = create_dialog_text(game, dialog, box, sprite);
    sfClock *clock = sfClock_create();

    while (sfRenderWindow_isOpen(game->window)) {
        if (handle_dialog_events(game->window, event) == sfEvtCount &&
            sfTime_asMilliseconds(sfClock_getElapsedTime(clock)) > 200)
            break;
        sfRenderWindow_drawRectangleShape(game->window, box, NULL);
        sfRenderWindow_drawText(game->window, text, NULL);
        sfRenderWindow_drawSprite(game->window, sprite, NULL);
        sfRenderWindow_display(game->window);
    }
    sfSprite_destroy(sprite);
    sfClock_destroy(clock);
    sfText_destroy(text);
    sfRectangleShape_destroy(box);
}
