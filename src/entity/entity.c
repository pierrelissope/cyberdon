/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** entity
*/

#include "entity.h"
#include "world.h"
#include "basics.h"
#include "init_entity.h"

const int ANIMATION_COOLDOWN = 200;

const int MAP_TILE_SIZE = 50;

const int ENTITY_RECT_SIZE = 15;

const sfVector2f FRAME_SIZE = {119, 128};
const int FRAME_NUMBER = 3;

const int BASE_VELOCITY = 5;

static void setup_entity(physical_entity_t *entity, sfVector2f pos)
{
    sfRectangleShape_setPosition(entity->rect, pos);
    sfRectangleShape_setSize(entity->rect,
        (sfVector2f){ENTITY_RECT_SIZE, ENTITY_RECT_SIZE});
    sfRectangleShape_setFillColor(entity->rect, sfRed);
    entity->current_frame = 0;
    entity->animation_cooldown = ANIMATION_COOLDOWN;
    for (int i = 0; entity->sprite_sheets[i]; i++)
        sfSprite_setTextureRect(entity->sprite_sheets[i],
            (sfIntRect){0, 0, FRAME_SIZE.x, FRAME_SIZE.y});
    entity->is_valid = true;
}

physical_entity_t *init_entity(sfVector2f pos, int type, char *name,
    dict_t *sheets_dict)
{
    physical_entity_t *entity = malloc(sizeof(physical_entity_t));

    memset(entity, 0, sizeof(physical_entity_t));
    strcpy(entity->name, name);
    entity->type = type;
    entity->current_spritesheet = 1;
    entity->sprite_sheets = dup_sprites(dict_get(sheets_dict, type));
    entity->clock = sfClock_create();
    entity->last_animation_update = sfClock_getElapsedTime(entity->clock);
    entity->rect = sfRectangleShape_create();
    entity->velocity = BASE_VELOCITY;
    if (!entity->rect || !entity->clock || !entity->sprite_sheets)
        return entity;
    setup_entity(entity, pos);
    return entity;
}

void destroy_entity(physical_entity_t *entity)
{
    for (int i = 0; entity->sprite_sheets && entity->sprite_sheets[i]; i++)
        sfSprite_destroy(entity->sprite_sheets[i]);
    if (entity->rect)
        sfRectangleShape_destroy(entity->rect);
    if (entity->clock)
        sfClock_destroy(entity->clock);
    printf("Entity Destroyed\n");
}

static sfVector2f get_movement(sfEvent *event)
{
    sfVector2f movement = {0, 0};

    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        movement.x += -1;
        movement.y += 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        movement.x += 1;
        movement.y += -1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        movement.y += -1;
        movement.x += -1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        movement.y += 1;
        movement.x += 1;
    }
    return normalize(movement);
}

void move_entity(physical_entity_t *entity, sfEvent *event, world_t *world)
{
    sfFloatRect new_rect = {0};
    sfVector2f mouvement = get_movement(event);

    new_rect = sfRectangleShape_getGlobalBounds(entity->rect);
    new_rect.left += mouvement.x * entity->velocity;
    new_rect.top += mouvement.y * entity->velocity;
    if (still_collide(&new_rect, world) && dont_collide(&new_rect, world))
        sfRectangleShape_setPosition(entity->rect,
            (sfVector2f){new_rect.left, new_rect.top});
}

void update_entity(physical_entity_t *entity)
{
    int now = sfTime_asMilliseconds(sfClock_getElapsedTime(entity->clock));
    int last_update = sfTime_asMilliseconds(entity->last_animation_update);
    sfIntRect frame_rect = {0};

    entity->current_frame %= FRAME_NUMBER;
    frame_rect = (sfIntRect){
        (int)(entity->current_frame * FRAME_SIZE.x), 0,
        FRAME_SIZE.x, FRAME_SIZE.y};
    if (now - last_update > entity->animation_cooldown) {
        sfSprite_setTextureRect(
            entity->sprite_sheets[entity->current_spritesheet], frame_rect);
        entity->current_frame += 1;
        entity->last_animation_update = sfClock_getElapsedTime(entity->clock);
    }
}

void draw_entity(void *entity, sfRenderWindow *window)
{
    physical_entity_t *nentity = entity;

    sfRenderWindow_drawRectangleShape(window, nentity->rect, NULL);
    sfSprite_setOrigin(nentity->sprite_sheets[nentity->current_spritesheet],
        (sfVector2f){0, 0.95 * FRAME_SIZE.y});
    sfSprite_setPosition(nentity->sprite_sheets[nentity->current_spritesheet],
        isom_pos_converter((sfVector2f){
        sfRectangleShape_getPosition(nentity->rect).x / MAP_TILE_SIZE,
        sfRectangleShape_getPosition(nentity->rect).y / MAP_TILE_SIZE}));
    sfRenderWindow_drawSprite(window,
        nentity->sprite_sheets[nentity->current_spritesheet], NULL);
}
