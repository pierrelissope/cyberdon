/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** dialogs
*/

#include "entity.h"
#include "init_entity.h"

static const sfVector2f dialog_box_size = {1920, 350};
static const sfVector2f dialog_box_pos = {0, 750};
static const float interaction_reach = 15.0;

dialog_box_t init_dialog_box(void)
{
    dialog_box_t dialog_box = {0};

    dialog_box.rect = sfRectangleShape_create();
    if (!dialog_box.rect)
        return dialog_box;
    sfRectangleShape_setSize(dialog_box.rect, dialog_box_size);
    sfRectangleShape_setPosition(dialog_box.rect, dialog_box_pos);
    sfRectangleShape_setFillColor(dialog_box.rect, sfWhite);
    dialog_box.is_valid = true;
    return dialog_box;
}

static void load_dialog(dialog_box_t *dialog_box, char **dialog_array)
{
    sfText *text = sfText_create();

}

void update_dialog_box(dialog_box_t *dialog_box, game_t *game)
{
    sfFloatRect interaction_hitbox =
        sfRectangleShape_getGlobalBounds(game->player->rect);
    physical_entity_t *npc = NULL;

    interaction_hitbox.top -= interaction_reach;
    interaction_hitbox.left -= interaction_reach;
    interaction_hitbox.height += 2 * interaction_reach;
    interaction_hitbox.width += 2 * interaction_reach;
    npc = collide_npc(game->player->name, &interaction_hitbox, &(game->world));
    if (npc) {
        //INTERACTION POSSIBLE
        if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
            game->game_state = IN_DIALOG;

        }
    }
    return;
}

void display_dialog_box(sfRenderWindow *window, dialog_box_t *dialog_box,
    game_state_t game_state)
{
    if (game_state == IN_DIALOG) {
        sfRenderWindow_drawRectangleShape(window, dialog_box->rect, NULL);
        //sfRenderWindow_drawText(window,
        //    dialog_box->dialog_array[dialog_box->current_dialog], NULL);
    }
}
