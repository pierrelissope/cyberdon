/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** displayers for fighting
*/

#include "fight_entity.h"
#include "fight_macros.h"
#include "struct.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>

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
    if (current->current_frame >= current->n_of_frames)
        current->current_frame = 0;
    current->text_rec.left = current->current_frame * current->text_rec.width;
    sfSprite_setTextureRect(current->sprite_sheet, current->text_rec);
    sfClock_restart(entity->clock);
}

static void draw_fighter(fighter_entity_t *fighter, sfRenderWindow *win)
{
    sfSprite_setTextureRect(fighter->annimation_sheets[fighter->state]->sprite_sheet,
        fighter->annimation_sheets[fighter->state]->text_rec);
    sfRenderWindow_drawSprite(win,
        fighter->annimation_sheets[fighter->state]->sprite_sheet, NULL);
}

void draw_fight(fight_t *fight, sfRenderWindow *win)
{
    sfRenderWindow_clear(win, sfBlack);
    sfRenderWindow_drawRectangleShape(win, fight->background, NULL);
    draw_fighter(fight->player, win);
    draw_fighter(fight->npc, win);
    sfRenderWindow_drawRectangleShape(win, fight->foreground, NULL);
    sfRenderWindow_display(win);
}
