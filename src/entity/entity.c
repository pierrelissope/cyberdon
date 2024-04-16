/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** entity
*/

#include "entity.h"
#include "world.h"
#include "basics.h"

const int ANIMATION_COOLDOWN = 200;

const int PLAYER_IDLE_SPRITESHEET = 0;
const int PLAYER_RUNNING_SPRITESHEET = 1;

const int MAP_TILE_SIZE = 50;

const int ENTITY_RECT_SIZE = 15;

const sfVector2f FRAME_SIZE = {119, 128};
const int FRAME_NUMBER = 3;

Physical_Entity_t init_entity(sfVector2f pos, char *type, dict_t *sheets_dict)
{
    Physical_Entity_t entity = {0};

    my_strcpy(entity.type, type);
    entity.current_spritesheet = 0;
    entity.sprite_sheets = dup_sprites(dict_get(sheets_dict, type));
    entity.clock = sfClock_create();
    entity.last_animation_update = sfClock_getElapsedTime(entity.clock);

    entity.rect = sfRectangleShape_create();
    sfRectangleShape_setPosition(entity.rect,(sfVector2f){10, 110});
    sfRectangleShape_setSize(entity.rect,(sfVector2f){ENTITY_RECT_SIZE, ENTITY_RECT_SIZE});
    sfRectangleShape_setFillColor(entity.rect, sfRed);

    entity.current_frame = 0;
    entity.animation_cooldown = ANIMATION_COOLDOWN;
    sfSprite_setTextureRect(
            entity.sprite_sheets[0],
            (sfIntRect){0, 0, FRAME_SIZE.x, FRAME_SIZE.y});
    return entity;
}

static bool still_collide(sfFloatRect rect, world_t *world)
{
    sfFloatRect rectBounds = rect;
    bool  trigger = false;


    for (float x = rectBounds.left; x < rectBounds.left + rectBounds.width; x++) {
        for (float y = rectBounds.top; y < rectBounds.top + rectBounds.height; y++) {
            trigger = false;
            for (int i = 0; world->floor && world->floor[i]; i++) {
                sfFloatRect floor = sfRectangleShape_getGlobalBounds(world->floor[i]->rect);
                if (sfFloatRect_contains(&floor, x, y))
                    trigger = true;
            }
            if (trigger == false)
                return false;
        }
    }
    return true;
}

static bool dont_collide(sfFloatRect rect, world_t *world)
{
    for (int i = 0; world->walls && world->walls[i]; i++) {
        sfFloatRect walls = sfRectangleShape_getGlobalBounds(world->walls[i]->rect);
        if (sfFloatRect_intersects(&rect, &walls, NULL))
            return false;
    }
    return true;
}

void move_entity(Physical_Entity_t *entity, sfEvent *event, world_t *world)
{
    sfVector2f movement = {0, 0};
    sfFloatRect new_rect = {0};

    if (event->key.code == sfKeyLeft) {
        movement.x = -10;
        movement.y = 10;
    }
    if (event->key.code == sfKeyRight) {
        movement.x = 10;
        movement.y = -10;
    }
    if (event->key.code == sfKeyUp) {
        movement.y = -10;
        movement.x = -10;
    }
    if (event->key.code == sfKeyDown) {
        movement.y = 10;
        movement.x = 10;
    }
    new_rect = sfRectangleShape_getGlobalBounds(entity->rect);
    new_rect.left += movement.x;
    new_rect.top += movement.y;
    if (still_collide(new_rect, world) && dont_collide(new_rect, world))
        sfRectangleShape_setPosition(entity->rect,
            (sfVector2f){new_rect.left, new_rect.top});
}

void update_entity(Physical_Entity_t *entity)
{
    int now = sfTime_asMilliseconds(sfClock_getElapsedTime(entity->clock));
    int last_update = sfTime_asMilliseconds(entity->last_animation_update);
    sfIntRect frame_rect;
    
    entity->current_frame %= 3;
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

void draw_entity(Physical_Entity_t *entity, sfRenderWindow *window)
{
    sfRenderWindow_drawRectangleShape(window, entity->rect, NULL);
    sfSprite_setOrigin(entity->sprite_sheets[entity->current_spritesheet],
        (sfVector2f){0, 120});
    sfSprite_setPosition(entity->sprite_sheets[entity->current_spritesheet],
        isom_pos_converter((sfVector2f){
        sfRectangleShape_getPosition(entity->rect).x / MAP_TILE_SIZE,
        sfRectangleShape_getPosition(entity->rect).y / MAP_TILE_SIZE}));
    sfRenderWindow_drawSprite(window,
        entity->sprite_sheets[entity->current_spritesheet], NULL);
}
