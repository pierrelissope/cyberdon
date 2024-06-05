/*
** EPITECH PROJECT, 2024
** RPG22
** File description:
** menu2
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

sfBool is_mouse_over_button(sfRenderWindow *window, button_t button)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfVector2f button_pos = sfRectangleShape_getPosition(button.shape);
    sfVector2f button_size = sfRectangleShape_getSize(button.shape);

    if (mouse_pos.x >= button_pos.x &&
        mouse_pos.x <= button_pos.x + button_size.x &&
        mouse_pos.y >= button_pos.y &&
        mouse_pos.y <= button_pos.y + button_size.y)
        return sfTrue;
    return sfFalse;
}

void handle_button_click(game_t *game, button_t *buttons)
{
    if (is_mouse_over_button(game->window, buttons[PLAY])){
        load_save(game);
        game->game_state = IN_GAME;
    }
    if (is_mouse_over_button(game->window, buttons[NEW_GAME])) {
        system("rm .save");
        game->game_state = IN_GAME;
    }
    if (is_mouse_over_button(game->window, buttons[LOAD]))
        create_save(game);
    if (is_mouse_over_button(game->window, buttons[LEAVE]))
        sfRenderWindow_close(game->window);
    if (is_mouse_over_button(game->window, buttons[SETTINGS]))
        parametres(game->window, game->game_info, game);
}

sfRectangleShape* create_button_shape(const button_init_t *button_init)
{
    sfRectangleShape* shape = sfRectangleShape_create();

    sfRectangleShape_setSize(shape, button_init->size);
    sfRectangleShape_setPosition(shape, button_init->position);
    sfRectangleShape_setFillColor(shape, button_init->fill_color);
    sfRectangleShape_setOutlineColor(shape, button_init->outline_color);
    sfRectangleShape_setOutlineThickness(shape, 2);
    return shape;
}

sfText* create_button_desc(const sfFont *font,
    const button_init_t *button_init, const sfVector2f position)
{
    sfText* text = sfText_create();

    sfText_setString(text, button_init->desc);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 15);
    sfText_setPosition(text, position);
    sfText_setFillColor(text, button_init->desc_color);
    return text;
}

sfText* create_button_text(const sfFont *font,
    const button_init_t *button_init, const sfVector2f position)
{
    sfText* text = sfText_create();

    sfText_setString(text, button_init->text);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 30);
    sfText_setPosition(text, position);
    sfText_setFillColor(text, button_init->text_color);
    return text;
}

sfSprite* create_button_sprite(const char *image_path,
    const sfVector2f position)
{
    if (image_path != NULL) {
        sfTexture* texture = sfTexture_createFromFile(image_path, NULL);
        sfSprite* sprite = sfSprite_create();
        sfSprite_setTexture(sprite, texture, sfTrue);
        sfSprite_setPosition(sprite, position);
        return sprite;
    } else {
        return NULL;
    }
}

button_t create_button(sfFont *font, button_init_t *button_init,
    const char *image_path)
{
    button_t button;
    sfVector2f desc_position;
    sfVector2f text_position;
    sfVector2f sprite_position;

    button.shape = create_button_shape(button_init);
    if (image_path != NULL) {
        sprite_position = (sfVector2f){button_init->position.x + 20, button_init->position.y + 20};
        button.sprite = create_button_sprite(image_path, sprite_position);
        text_position = (sfVector2f){button_init->position.x + 80, button_init->position.y + 30};
        desc_position = (sfVector2f){button_init->position.x + 80, button_init->position.y + 15};
        button.text = create_button_text(font, button_init, text_position);
        button.desc = create_button_desc(font, button_init, desc_position);
    } else {
        button.sprite = NULL;
        text_position = (sfVector2f){button_init->position.x + 20, button_init->position.y + 30};
        desc_position = (sfVector2f){button_init->position.x + 20, button_init->position.y + 15};
        button.text = create_button_text(font, button_init, text_position);
        button.desc = create_button_desc(font, button_init, desc_position);
    }
    return button;
}

rect_t create_rect(const rect_init_t *rect_init, char *path)
{
    rect_t rect;
    sfTexture *texture = sfTexture_createFromFile(path, NULL);

    rect.position = rect_init->position;
    rect.image = sfSprite_create();
    sfSprite_setTexture(rect.image, texture, sfTrue);
    sfSprite_setPosition(rect.image, rect.position);
    return rect;
}
