/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** entities
*/

#include "dict.h"
#include "string.h"
#include "entity.h"
#include "init_texture.h"
#include "inventory.h"
#include "myutils.h"

static const int ANIMATION_COOLDOWN = 100;

static const int ENTITY_RECT_SIZE = 15;

static const sfVector2f FRAME_SIZE = {1024 / 8, 128};
static const int FRAME_NUMBER = 9;

static const float BASE_VELOCITY = 4.3;

static void setup_entity(physical_entity_t *entity, sfVector2f pos)
{
    dict_t *dict = entity->sprite_sheets;

    sfRectangleShape_setPosition(entity->rect, pos);
    sfRectangleShape_setSize(entity->rect,
        (sfVector2f){ENTITY_RECT_SIZE, ENTITY_RECT_SIZE});
    sfRectangleShape_setFillColor(entity->rect, sfRed);
    entity->current_frame = 0;
    entity->animation_cooldown = ANIMATION_COOLDOWN;
    for (; dict; dict = dict->next)
        sfSprite_setTextureRect(dict->value,
            (sfIntRect){0, 0, FRAME_SIZE.x, FRAME_SIZE.y});
    entity->is_valid = true;
}

physical_entity_t *init_entity(sfVector2f pos, int type, char *name,
    dict_t *sheets_dict)
{
    physical_entity_t *entity = calloc(1, sizeof(physical_entity_t));

    strcpy(entity->name, name);
    entity->font = sfFont_createFromFile("./assets/font/default.ttf");
    entity->type = type;
    entity->sprite_sheets = dup_sprites(dict_get(sheets_dict, type));
    entity->current_sprite_sheet = dict_get(entity->sprite_sheets, IDLE);
    entity->clock = sfClock_create();
    entity->last_animation_update = sfClock_getElapsedTime(entity->clock);
    entity->rect = sfRectangleShape_create();
    entity->velocity = BASE_VELOCITY;
    if (!entity->rect || !entity->clock ||
        !entity->sprite_sheets || !entity->font)
        return entity;
    entity->inventory = create_inventory((sfVector2f){50, 300},
        "player_inventory", entity->font);
    entity->stats = create_stats(name, sheets_dict, entity->font);
    setup_entity(entity, pos);
    return entity;
}

static sfVector2f get_movement(game_t *game)
{
    sfVector2f movement = {0, 0};

    if (sfKeyboard_isKeyPressed(game->game_info->key[MOVE_LEFT])) {
        movement.x += -1;
        movement.y += 1;
    }
    if (sfKeyboard_isKeyPressed(game->game_info->key[MOVE_RIGHT])) {
        movement.x += 1;
        movement.y += -1;
    }
    if (sfKeyboard_isKeyPressed(game->game_info->key[MOVE_UP])) {
        movement.y += -1;
        movement.x += -1;
    }
    if (sfKeyboard_isKeyPressed(game->game_info->key[MOVE_DOWN])) {
        movement.y += 1;
        movement.x += 1;
    }
    return normalize(movement);
}

static bool collide_npc(char *entity_name,
    sfFloatRect *player_rect, world_t *world)
{
    sfFloatRect entity_rect = {0};

    for (int i = 0; world->entities && world->entities[i]; i++) {
        if (strcmp(entity_name, world->entities[i]->name) == 0)
            continue;
        entity_rect = sfRectangleShape_getGlobalBounds(
            world->entities[i]->rect);
        if (sfFloatRect_intersects(player_rect, &entity_rect, NULL))
            return true;
    }
    return false;
}

static void change_linear_sprite(physical_entity_t *entity,
    sfVector2f mvt)
{
    if (mvt.x < 0 && mvt.y > 0)
        entity->current_sprite_sheet = dict_get(entity->sprite_sheets, LEFT);
    if (mvt.x > 0 && mvt.y < 0)
        entity->current_sprite_sheet = dict_get(entity->sprite_sheets, RIGHT);
    if (mvt.x < 0 && mvt.y < 0)
        entity->current_sprite_sheet = dict_get(entity->sprite_sheets, UP);
    if (mvt.x > 0 && mvt.y > 0)
        entity->current_sprite_sheet = dict_get(entity->sprite_sheets, DOWN);
    if (mvt.x == 0 && mvt.y == 0)
        entity->current_sprite_sheet = dict_get(entity->sprite_sheets, IDLE);
}

static void change_entity_sprite(physical_entity_t *entity, sfVector2f mvt)
{
    if (mvt.x < 0 && mvt.y == 0)
        entity->current_sprite_sheet = dict_get(
            entity->sprite_sheets, UP_LEFT);
    if (mvt.x == 0 && mvt.y < 0)
        entity->current_sprite_sheet = dict_get(
            entity->sprite_sheets, UP_RIGHT);
    if (mvt.x == 0 && mvt.y > 0)
        entity->current_sprite_sheet = dict_get(
            entity->sprite_sheets, DOWN_LEFT);
    if (mvt.x > 0 && mvt.y == 0)
        entity->current_sprite_sheet = dict_get(
            entity->sprite_sheets, DOWN_RIGHT);
    change_linear_sprite(entity, mvt);
}

void move_entity(physical_entity_t *entity, sfEvent *event,
    world_t *world, game_t *game)
{
    sfFloatRect new_rect = {0};
    sfVector2f mouvement = get_movement(game);

    change_entity_sprite(entity, mouvement);
    new_rect = sfRectangleShape_getGlobalBounds(entity->rect);
    new_rect.left += mouvement.x * entity->velocity;
    new_rect.top += mouvement.y * entity->velocity;
    if (still_collide(&new_rect, world) && dont_collide(&new_rect, world) &&
        !collide_npc(entity->name, &new_rect, world))
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
            entity->current_sprite_sheet, frame_rect);
        entity->current_frame += 1;
        entity->last_animation_update = sfClock_getElapsedTime(entity->clock);
    }
}

void draw_entity(void *entity, sfRenderWindow *window)
{
    physical_entity_t *nentity = entity;

    sfSprite_setOrigin(nentity->current_sprite_sheet,
        (sfVector2f){FRAME_SIZE.x / 2, FRAME_SIZE.y * 1.7});
    sfSprite_setPosition(nentity->current_sprite_sheet,
        isom_pos_converter((sfVector2f){
        sfRectangleShape_getPosition(nentity->rect).x / TILE_SIZE,
        sfRectangleShape_getPosition(nentity->rect).y / TILE_SIZE}));
    sfRenderWindow_drawSprite(window,
        nentity->current_sprite_sheet, NULL);
}
