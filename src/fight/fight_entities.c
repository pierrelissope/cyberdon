/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** special entities init
*/

#include "dict.h"
#include "fight_entity.h"
#include "fight_macros.h"
#include "init_fighters.h"
#include "struct.h"

#include <SFML/Config.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include "stdio.h"

static sfSprite *init_fight_sprite(fighter_entity_t *entity,
    int moves_index, dict_t *text_dict)
{
    sfSprite *sp = sfSprite_create();
    sfFloatRect bounds = {0};

    if (entity->name == PLAYER_FIGHTER) {
        sfSprite_setTexture(sp, dict_get(text_dict,
            MOVES_INIT[moves_index].state), sfFalse);
        sfSprite_setPosition(sp, PLAYER_SPAWN);
        entity->sprite_pos = PLAYER_SPAWN;
    } else {
        sfSprite_setTexture(sp, dict_get(text_dict,
            MOVES_INIT[moves_index].state + PLAYER_TEXTURES_END + 1), sfFalse);
        sfSprite_setPosition(sp, NPC_SPAWN);
        entity->sprite_pos = NPC_SPAWN;
    }
    sfSprite_setTextureRect(sp, MOVES_INIT[moves_index].frame_rec);
    bounds = sfSprite_getGlobalBounds(sp);
    sfSprite_setOrigin(sp, (sfVector2f) {bounds.width / 2, 0});
    return sp;
}

static annimation_t **init_annimations(fighter_entity_t *entity,
    dict_t *text_dict)
{
    annimation_t **annimations = calloc(
        STATES_END + 1, sizeof(annimation_t *));

    for (int i = 0; MOVES_INIT[i].state != STATES_END; i++) {
        annimations[i] = calloc(1, sizeof(annimation_t));
        annimations[i]->text_rec = MOVES_INIT[i].frame_rec;
        annimations[i]->n_of_frames = MOVES_INIT[i].frame_number;
        annimations[i]->id = MOVES_INIT[i].state;
        annimations[i]->cooldown_mili = MOVES_INIT[i].animation_cooldown;
        annimations[i]->sprite_sheet = init_fight_sprite(entity, i, text_dict);
    }
    return annimations;
}

fighter_entity_t *init_fighter_entity(physical_entity_t *entity_stats,
    fight_t *fight)
{
    fighter_entity_t *entity = calloc(1, sizeof(fighter_entity_t));

    entity->clock = sfClock_create();
    entity->ability_clock = sfClock_create();
    entity->ability_cooldown = COOLDOWN;
    entity->velocity = BASE_FIGHTER_VELOCITY;
    if (entity_stats->type == 0) {
        entity->looking_right = true;
        entity->name = PLAYER_FIGHTER;
    } else {
        entity->looking_left = true;
        entity->name = NPC1;
    }
    entity->annimation_sheets = init_annimations(entity, fight->text_dict);
    entity->state = IDLE;
    return entity;
}

void destroy_fighter_entity(fighter_entity_t *entity)
{
    if (entity->clock)
        sfClock_destroy(entity->clock);
    printf("Entity Destroyed\n");
}
