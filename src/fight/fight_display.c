/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** displayers for fighting
*/

#include "basics.h"
#include "fight_entity.h"
#include "fight_macros.h"
#include "struct.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>

static bool annimation_lock(fighter_entity_t *entity)
{
    for (fighter_state_t i = 0; i < N_OF_LOCKS; i++) {
        if (entity->state == STATE_LOCKS[i] &&
            entity->annimation_sheets[entity->state]->current_frame != 0 &&
            entity->annimation_sheets[entity->state]->current_frame <=
            entity->annimation_sheets[entity->state]->n_of_frames - 1) {
            return true;
        }
    }
    return false;
}

void annimate_fighter(fighter_entity_t *entity)
{
    annimation_t *current = entity->annimation_sheets[entity->state];

    if (sfTime_asMilliseconds(sfClock_getElapsedTime(entity->clock))
        <= current->cooldown_mili)
        return;
    if (current->current_frame == current->n_of_frames / 2 &&
        entity->state == CROUCH)
        return;
    current->current_frame += 1 % MAX_FRAMES;
    if (current->current_frame >= current->n_of_frames) {
        entity->annimation_lock = annimation_lock(entity);
        current->current_frame = 0;
    }
    current->text_rec.left = current->current_frame * current->text_rec.width;
    sfSprite_setTextureRect(current->sprite_sheet, current->text_rec);
    sfClock_restart(entity->clock);
}

static void draw_fighter(fighter_entity_t *fighter, sfRenderWindow *win)
{
    annimation_t *current = fighter->annimation_sheets[fighter->state];

    sfSprite_setTextureRect(
        fighter->annimation_sheets[fighter->state]->sprite_sheet,
        fighter->annimation_sheets[fighter->state]->text_rec);
    sfRenderWindow_drawSprite(win,
        fighter->annimation_sheets[fighter->state]->sprite_sheet, NULL);
}

static void draw_rec(sfFloatRect *rec,
    sfVector2f *origin, sfRenderWindow *window)
{
    sfRectangleShape *temp = sfRectangleShape_create();
    sfVector2f temp_vec;

    if (temp == NULL)
        return;
    temp_vec.x = rec->width;
    temp_vec.y = rec->height;
    sfRectangleShape_setOrigin(temp, *origin);
    sfRectangleShape_setPosition(temp,
        (sfVector2f) {rec->left, rec->top});
    sfRectangleShape_setSize(temp, temp_vec);
    sfRectangleShape_setFillColor(temp, sfTransparent);
    sfRectangleShape_setOutlineThickness(temp, 2);
    sfRenderWindow_drawRectangleShape(window, temp, NULL);
    sfRectangleShape_destroy(temp);
}

static void draw_debug(fight_t *fight, sfRenderWindow *win)
{
    sfVector2f npc_origin = sfSprite_getOrigin(
        fight->npc->annimation_sheets[fight->npc->state]->sprite_sheet);
    sfVector2f player_origin = sfSprite_getOrigin(
        fight->player->annimation_sheets[fight->player->state]->sprite_sheet);

    draw_rec(&(fight->player->hitbox), &player_origin, win);
    draw_rec(&(fight->npc->hitbox), &npc_origin, win);
    draw_rec(&(fight->player->dmgbox), &player_origin, win);
    draw_rec(&(fight->npc->dmgbox), &npc_origin, win);
}

static void draw_ui(fight_t *fight, sfRenderWindow *win)
{
    sfRenderWindow_drawRectangleShape(win, fight->ui.npc_hp, NULL);
    sfRenderWindow_drawRectangleShape(win, fight->ui.npc_stamina, NULL);
    sfRenderWindow_drawRectangleShape(win, fight->ui.player_stamina, NULL);
    sfRenderWindow_drawRectangleShape(win, fight->ui.player_hp, NULL);
    sfRenderWindow_drawRectangleShape(win, fight->ui.player_portrait, NULL);
    sfRenderWindow_drawRectangleShape(win, fight->ui.npc_portrait, NULL);
}

void draw_fight(fight_t *fight, sfRenderWindow *win)
{
    sfRenderWindow_clear(win, sfBlack);
    sfRenderWindow_drawRectangleShape(win, fight->background, NULL);
    draw_fighter(fight->player, win);
    if (fight->debug_mode)
        draw_debug(fight, win);
    draw_ui(fight, win);
    draw_fighter(fight->npc, win);
    sfRenderWindow_drawRectangleShape(win, fight->foreground, NULL);
    sfRenderWindow_display(win);
}
