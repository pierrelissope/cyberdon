/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** loading_screen
*/

#include "struct.h"
#include "init_texture.h"
#include "entity.h"
#include "dict.h"

static const int ANNIMATION_COOLDOWN = 90;
static const float LOADING_TIME = 0.6;

loading_page_t init_loading_page(dict_t *tiles_dict)
{
    loading_page_t loading_page = {0};

    loading_page.clock = sfClock_create();
    loading_page.animation_clock = sfClock_create();
    loading_page.element_sprite = sfSprite_create();
    sfSprite_setTexture(loading_page.element_sprite,
        dict_get(tiles_dict, LOADING_PAGE_SHEET), sfTrue);
    sfSprite_setScale(loading_page.element_sprite, (sfVector2f){2, 2});
    sfSprite_setPosition(loading_page.element_sprite, (sfVector2f){1390, 800});
    for (int i = 0; TILES_TEXTURE_INIT[i].texture_path; ++i)
        if (TILES_TEXTURE_INIT[i].texture_name == LOADING_PAGE_SHEET) {
            loading_page.element_rect = TILES_TEXTURE_INIT[i].rect;
            loading_page.frame_nb = TILES_TEXTURE_INIT[i].frame_nb;
        }
    sfSprite_setTextureRect(loading_page.element_sprite,
        loading_page.element_rect);
    loading_page.is_valid = false;
    return loading_page;
}

static void annimate_loading_screen(loading_page_t *loading_page)
{
    int now = sfTime_asMilliseconds(
        sfClock_getElapsedTime(loading_page->animation_clock));

    if (now < ANNIMATION_COOLDOWN)
        return;
    loading_page->current_frame %= loading_page->frame_nb;
    loading_page->element_rect = (sfIntRect){
        (int)(loading_page->current_frame * loading_page->element_rect.width),
        0, loading_page->element_rect.width, loading_page->element_rect.height
    };
    sfClock_restart(loading_page->animation_clock);
    loading_page->current_frame += 1;
    sfSprite_setTextureRect(loading_page->element_sprite,
        loading_page->element_rect);
}

void play_loading_screen(sfRenderWindow *window, loading_page_t *loading_page)
{
    sfClock_restart(loading_page->clock);
    sfClock_restart(loading_page->animation_clock);
    loading_page->current_frame = 0;
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
    while (sfTime_asSeconds(
        sfClock_getElapsedTime(loading_page->clock)) < LOADING_TIME) {
        annimate_loading_screen(loading_page);
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, loading_page->element_sprite, NULL);
        sfRenderWindow_display(window);
    }
}
