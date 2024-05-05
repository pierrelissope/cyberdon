/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** entity
*/

#include "fighting_entity.h"
#include "init_texture.h"

static const ANIMATION_COOLDOWN = 200;
static const sfVector2f entity_size = {80, 200};

static void setup_entity(fighting_entity_t *entity, sfVector2f pos)
{
    dict_t *dict = entity->sprite_sheets;

    sfRectangleShape_setPosition(entity->rect, pos);
    sfRectangleShape_setSize(entity->rect,
        (sfVector2f){entity_size.x, entity_size.y});
    sfRectangleShape_setFillColor(entity->rect, sfRed);
    entity->current_frame = 0;
    entity->animation_cooldown = ANIMATION_COOLDOWN;
    for (;dict; dict = dict->next)
        sfSprite_setTextureRect(dict->value,
        (sfIntRect){0, 0, entity_size.x, entity_size.y});
    entity->is_valid = true;
}

fighting_entity_t *init_fighting_entity(sfVector2f pos, int type, char *name,
    dict_t *sheets_dict)
{
    fighting_entity_t *entity = calloc(1, sizeof(fighting_entity_t));

    entity->type = type;
    entity->sprite_sheets = dup_sprites(dict_get(sheets_dict, type));
    entity->current_sprite_sheet = dict_get(entity->sprite_sheets, RIGHT);
    entity->clock = sfClock_create();
    entity->last_animation_update = sfClock_getElapsedTime(entity->clock);
    entity->rect = sfRectangleShape_create();
    if (!entity->rect || !entity->clock || !entity->sprite_sheets)
        return entity;
    setup_entity(entity, pos);
    return entity;
}