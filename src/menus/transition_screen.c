/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** loading_screen
*/

#include "struct.h"
#include "init_texture.h"
#include "entity.h"
#include "mymenu.h"
#include "dict.h"

loading_page_t init_transition_page(dict_t *tiles_dict)
{
    loading_page_t loading_page = {0};

    loading_page.clock = sfClock_create();
    loading_page.animation_clock = sfClock_create();
    loading_page.element_sprite = sfSprite_create();
    sfSprite_setTexture(loading_page.element_sprite,
        dict_get(tiles_dict, TRANSITION), sfTrue);
    for (int i = 0; TILES_TEXTURE_INIT[i].texture_path; ++i)
        if (TILES_TEXTURE_INIT[i].texture_name == TRANSITION) {
            loading_page.element_rect = TILES_TEXTURE_INIT[i].rect;
            loading_page.frame_nb = TILES_TEXTURE_INIT[i].frame_nb;
        }
    sfSprite_setTextureRect(loading_page.element_sprite,
        loading_page.element_rect);
    loading_page.is_valid = false;
    return loading_page;
}

void annimate_transition_screen(loading_page_t *loading_page,
    sfRectangleShape *rectangle)
{
    int now = sfTime_asMilliseconds(
        sfClock_getElapsedTime(loading_page->animation_clock));

    if (now < 15)
        return;
    sfClock_restart(loading_page->animation_clock);
    sfRectangleShape_move(rectangle, (sfVector2f){27, 0});
}

void play_transition_screen(sfRenderWindow *window, dict_t *tiles_dict,
    game_t *game)
{
    loading_page_t page = init_transition_page(tiles_dict);
    sfRectangleShape *rectangle = sfRectangleShape_create();

    sfRectangleShape_setPosition(rectangle, (sfVector2f){-1920, 0});
    sfRectangleShape_setFillColor(rectangle, sfBlack);
    sfRectangleShape_setSize(rectangle, (sfVector2f){1920, 1080});
    sfClock_restart(page.clock);
    sfClock_restart(page.animation_clock);
    page.current_frame = 0;
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
    sfMusic_play(game->sfx.fight);
    while (sfRectangleShape_getPosition(rectangle).x <= 0) {
        annimate_transition_screen(&page, rectangle);
        sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
        sfRenderWindow_display(window);
    }
    sfRectangleShape_destroy(rectangle);
    destroy_loading_page(&page);
}
