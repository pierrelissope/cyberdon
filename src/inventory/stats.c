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

static sfText *create_text(sfVector2f pos, char *str)
{
    sfText *text = sfText_create();

    sfText_setFont(text, FONT);
    sfText_setCharacterSize(text, 36);
    sfText_setString(text, str);
    sfText_setFillColor(text, sfWhite);
    sfText_setPosition(text, pos);
    free(str);
    return text;
}

void draw_stats_menu(sfRenderWindow *window, stats_t *stats)
{
    sfRenderWindow_drawRectangleShape(window, stats->box, NULL);

    sfRenderWindow_drawRectangleShape(window, stats->sprite_rect, NULL);

    sfRenderWindow_drawSprite(window, stats->sprite, NULL);
    sfRenderWindow_drawText(window, stats->level_text, NULL);
    sfRenderWindow_drawText(window, stats->xp_text, NULL);
    sfRenderWindow_drawText(window, stats->hp_text, NULL);
    sfRenderWindow_drawText(window, stats->defense_text, NULL);
    sfRenderWindow_drawText(window, stats->attack_text, NULL);
    sfRenderWindow_drawText(window, stats->speed_text, NULL);
    sfRenderWindow_drawText(window, stats->strength_text, NULL);
    sfRenderWindow_drawText(window, stats->stamina_text, NULL);
    sfRenderWindow_drawText(window, stats->stamina_regeneration_text, NULL);
}

stats_t create_stats(char const *name, dict_t *sheets_dict)
{
    stats_t stats = {0};
    sfVector2f pos = {1000, 215};

    strcpy(stats.name, name);

    stats.sprite = sfSprite_create();
    stats.attack = 1;
    stats.speed = 1;
    stats.strength = 1;
    stats.current_level = 1;
    stats.stamina = 10;
    stats.stamina_regeneration = 1;
    stats.current_xp = 0;

    stats.attack_bonus = 0;
    stats.speed_bonus = 0;
    stats.strength_bonus = 0;
    stats.stamina_bonus = 0;
    stats.stamina_regeneration_bonus = 0;

    stats.xp_to_levelup = stats.current_level * 1.5;
    stats.box = sfRectangleShape_create();
    stats.sprite_rect = sfRectangleShape_create();
    stats.values_rect = sfRectangleShape_create();

    sfSprite_setTexture(stats.sprite,
        dict_get(dict_get(sheets_dict, PLAYER), IDLE), sfTrue);
    sfSprite_setTextureRect(stats.sprite, (sfIntRect){0, 0, 128, 128});
    sfSprite_setScale(stats.sprite, (sfVector2f){2.5, 2.5});
    sfSprite_setPosition(stats.sprite, (sfVector2f){1030, 400});

    sfRectangleShape_setSize(stats.box, (sfVector2f){750, 650});
    sfRectangleShape_setOutlineThickness(stats.box, 1);
    sfRectangleShape_setOutlineColor(stats.box, LIGHT_WHITE);
    sfRectangleShape_setPosition(stats.box, pos);
    sfRectangleShape_setFillColor(stats.box, GREY);

    sfRectangleShape_setSize(stats.sprite_rect, (sfVector2f){280, 350});
    sfRectangleShape_setOutlineThickness(stats.sprite_rect, 1);
    sfRectangleShape_setOutlineColor(stats.sprite_rect, LIGHT_WHITE);
    sfRectangleShape_setPosition(stats.sprite_rect, (sfVector2f){1050, 390});
    sfRectangleShape_setFillColor(stats.sprite_rect, DARK_GREY);
    

    stats.xp_text = create_text((sfVector2f){1400, 280}, strdup("Xp 0 / 10"));
    stats.level_text = create_text((sfVector2f){1400, 340}, strdup("Level 1"));
    stats.hp_text = create_text((sfVector2f){1400, 400}, strdup("HP 100"));
    stats.defense_text = create_text((sfVector2f){1400, 460}, strdup("Defense 1"));
    stats.attack_text = create_text((sfVector2f){1400, 520}, strdup("Attack 1"));
    stats.speed_text = create_text((sfVector2f){1400, 580}, strdup("Speed 1"));
    stats.strength_text = create_text((sfVector2f){1400, 640}, strdup("Strength 1"));
    stats.stamina_text = create_text((sfVector2f){1400, 700}, strdup("Stamina 10"));
    stats.stamina_regeneration_text = create_text((sfVector2f){1400, 760}, strdup("Stamina Regen 1"));

    return stats;
}
