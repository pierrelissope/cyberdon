/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** stats
*/

#include <string.h>

#include "game.h"
#include "basics.h"
#include "dict.h"
#include "init_texture.h"
#include "struct.h"
#include "inventory.h"

static sfText *create_text(sfVector2f pos, char *str, sfFont *font)
{
    sfText *text = sfText_create();

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 36);
    sfText_setString(text, str);
    sfText_setFillColor(text, sfWhite);
    sfText_setPosition(text, pos);
    return text;
}

static sfText *create_b_text(sfVector2f pos, char *str, sfFont *font)
{
    sfText *text = sfText_create();

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 36);
    sfText_setString(text, str);
    sfText_setFillColor(text, sfGreen);
    sfText_setPosition(text, pos);
    return text;
}

static void init_stats_components(stats_t *stats, dict_t *sheets_dict)
{
    sfVector2f pos = {1000, 215};

    sfSprite_setTexture(stats->sprite,
        dict_get(dict_get(sheets_dict, PLAYER), IDLE), sfTrue);
    sfSprite_setTextureRect(stats->sprite, (sfIntRect){0, 0, 128, 128});
    sfSprite_setScale(stats->sprite, (sfVector2f){2.5, 2.5});
    sfSprite_setPosition(stats->sprite, (sfVector2f){1030, 400});
    sfRectangleShape_setSize(stats->box, (sfVector2f){750, 650});
    sfRectangleShape_setOutlineThickness(stats->box, 1);
    sfRectangleShape_setOutlineColor(stats->box, LIGHT_WHITE);
    sfRectangleShape_setPosition(stats->box, pos);
    sfRectangleShape_setFillColor(stats->box, GREY);
    sfRectangleShape_setSize(stats->sprite_rect, (sfVector2f){280, 350});
    sfRectangleShape_setOutlineThickness(stats->sprite_rect, 1);
    sfRectangleShape_setOutlineColor(stats->sprite_rect, LIGHT_WHITE);
    sfRectangleShape_setPosition(stats->sprite_rect, (sfVector2f){1050, 390});
    sfRectangleShape_setFillColor(stats->sprite_rect, DARK_GREY);
}

void init_next_stats_text(stats_t *stats, sfFont *font)
{
    stats->defense_bonus_text =
        create_b_text((sfVector2f){1560, 460}, "+ 0", font);
    stats->attack_bonus_text =
        create_b_text((sfVector2f){1540, 520}, "+ 0", font);
    stats->speed_bonus_text = create_b_text((sfVector2f){1530, 580}, "+ 0",
        font);
    stats->strength_bonus_text =
        create_b_text((sfVector2f){1560, 640}, "+ 0", font);
    stats->stamina_bonus_text =
        create_b_text((sfVector2f){1560, 700}, "+ 0", font);
    stats->stamina_regeneration_bonus_text =
        create_b_text((sfVector2f){1650, 760}, "+ 0", font);
}

static void init_stats_text(stats_t *stats, sfFont *font)
{
    stats->xp_text = create_text((sfVector2f){1400, 280}, "Xp 0 / 10", font);
    stats->level_text = create_text((sfVector2f){1400, 340}, "Level 1", font);
    stats->hp_text = create_text((sfVector2f){1400, 400}, "HP 100", font);
    stats->defense_text = create_text((sfVector2f){1400, 460}, "Defense 1",
        font);
    stats->attack_text = create_text((sfVector2f){1400, 520}, "Attack 1",
        font);
    stats->speed_text = create_text((sfVector2f){1400, 580}, "Speed 1", font);
    stats->strength_text = create_text((sfVector2f){1400, 640}, "Strength 1",
        font);
    stats->stamina_text = create_text((sfVector2f){1400, 700}, "Stamina 1",
        font);
    stats->stamina_regeneration_text =
        create_text((sfVector2f){1400, 760}, "Stamina Regen 1", font);
    stats->hp_bonus_text = create_b_text((sfVector2f){1500, 400}, "+ 0", font);
    init_next_stats_text(stats, font);
}

stats_t create_stats(char const *name, dict_t *sheets_dict, sfFont *font)
{
    stats_t stats = {0};

    strcpy(stats.name, name);
    stats.sprite = sfSprite_create();
    stats.attack = 1;
    stats.speed = 1;
    stats.strength = 1;
    stats.current_level = 1;
    stats.stamina = 10;
    stats.stamina_regeneration = 1;
    stats.current_xp = 0;
    stats.xp_to_levelup = stats.current_level * 1.5;
    stats.box = sfRectangleShape_create();
    stats.sprite_rect = sfRectangleShape_create();
    init_stats_components(&stats, sheets_dict);
    init_stats_text(&stats, font);
    return stats;
}

static void set_bonus_string(sfText *text, int bonus)
{
    char *str = my_itoa(bonus);
    char content[100] = {0};

    sprintf(content, "+ %s", str);
    free(str);
    sfText_setString(text, content);
}

void apply_item_effect(stats_t *stats, item_t *item)
{
    if (item->type == EMPTY_ITEM)
        return;
    for (size_t i = 0; ITEMS_LINK_ARRAY[i].str_type != NULL; ++i) {
        if (ITEMS_LINK_ARRAY[i].enum_type == item->type)
            ITEMS_LINK_ARRAY[i].effect(stats);
    }
}

void update_stats(stats_t *stats, inventory_t *inventory)
{
    stats->hp_bonus = 0;
    stats->defense_bonus = 0;
    stats->attack = 0;
    stats->speed_bonus = 0;
    stats->strength_bonus = 0;
    stats->stamina_bonus = 0;
    stats->stamina_regeneration_bonus = 0;
    for (size_t y = 0; y < INVENTORY_SIZE_Y; ++y)
        for (size_t x = 0; x < INVENTORY_SIZE_X; ++x)
            apply_item_effect(stats, inventory->slots[y][x].item);
    set_bonus_string(stats->hp_bonus_text, stats->hp_bonus);
    set_bonus_string(stats->defense_bonus_text, stats->defense_bonus);
    set_bonus_string(stats->attack_bonus_text, stats->attack_bonus);
    set_bonus_string(stats->speed_bonus_text, stats->speed_bonus);
    set_bonus_string(stats->strength_bonus_text, stats->strength_bonus);
    set_bonus_string(stats->stamina_bonus_text, stats->stamina_bonus);
    set_bonus_string(stats->stamina_regeneration_bonus_text,
        stats->stamina_regeneration_bonus);
}
