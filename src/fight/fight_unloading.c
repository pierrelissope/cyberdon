/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** the fight destroyer
*/

#include "dict.h"
#include "fight.h"
#include "fight_entity.h"
#include "init_fighters.h"
#include "struct.h"
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderTexture.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/View.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <stdlib.h>

static void destroy_annimation(annimation_t **annimations)
{
    for (int i = 0; MOVES_INIT[i].state != STATES_END; i++) {
        sfSprite_destroy(annimations[i]->sprite_sheet);
        free(annimations[i]);
    }
    free(annimations);
}

static void destroy_fighter_entity(fighter_entity_t *entity)
{
    sfClock_destroy(entity->clock);
    sfClock_destroy(entity->i_counter);
    destroy_annimation(entity->annimation_sheets);
    free(entity);
}

void destroy_ui(fight_t *fight)
{
    sfRectangleShape_destroy(fight->ui.npc_hp);
    sfRectangleShape_destroy(fight->ui.player_hp);
    sfRectangleShape_destroy(fight->ui.npc_stamina);
    sfRectangleShape_destroy(fight->ui.player_stamina);
}

void destroy_dict_text(void *to_free)
{
    sfTexture *to_destroy = to_free;

    sfTexture_destroy(to_destroy);
}

void destroy_fight(fight_t *fight)
{
    destroy_fighter_entity(fight->player);
    destroy_fighter_entity(fight->npc);
    sfView_destroy(fight->view);
    sfClock_destroy(fight->fps_clock);
    sfClock_destroy(fight->end_game_timer);
    sfClock_destroy(fight->stamina_clock);
    sfRectangleShape_destroy(fight->background);
    sfRectangleShape_destroy(fight->foreground);
    destroy_ui(fight);
    dict_destroy(fight->text_dict, destroy_dict_text);
    free(fight);
}
