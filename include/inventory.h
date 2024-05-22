/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** inventory
*/

#pragma once

#define INVENTORY_SIZE_X 5
#define INVENTORY_SIZE_Y 3
#define SLOT_SIZE 100
#define SLOT_MARGIN 10
#define SLOTS_MARGIN_TOP 100
#define OUTLINE_THIKNESS 1
#define ITEM_SIZE 80
#define ORB_MULTIPLIER 1

#define LIGHT_GREY sfColor_fromRGB(50, 50, 50)
#define GREY sfColor_fromRGB(39, 40, 44)
#define DARK_GREY sfColor_fromRGB(31, 32, 34)
#define LIGHT_WHITE sfColor_fromRGBA(150, 150, 150, 100)

#include "entity.h"

typedef struct inventory_items_link_s {
    char *str_type;
    item_type_t enum_type;
    char *description;
    void (*effect)(stats_t *);
} inventory_items_link_t;

void vitality_orb_effect(stats_t *stats);
void defense_orb_effect(stats_t *stats);
void speed_orb_effect(stats_t *stats);
void strength_orb_effect(stats_t *stats);
void stamina_orb_effect(stats_t *stats);
void stamina_regen_orb_effect(stats_t *stats);

static const inventory_items_link_t ITEMS_LINK_ARRAY[] =
{
    {
        .str_type = "speed_orb",
        .enum_type = SPEED_ORB,
        .description = "A mysterious blue orb which\nimproves speed",
        .effect = speed_orb_effect
    },
    {
        .str_type = "strength_orb",
        .enum_type = STRENGTH_ORB,
        .description = "A mysterious red orb which\nimproves strength",
        .effect = strength_orb_effect
    },
    {
        .str_type = "stamina_orb",
        .enum_type = STAMINA_ORB,
        .description = "A mysterious blue orange which\nimproves stamina",
        .effect = stamina_orb_effect
    },
    {
        .str_type = "stamina_regen_orb",
        .enum_type = STAMINA_REGEN_ORB,
        .description =
        "A mysterious blue orange which\nimproves stamina regeneration",
        .effect = stamina_regen_orb_effect
    },
    {
        .str_type = "vitality_orb",
        .enum_type = VITALITY_ORB,
        .description =
        "A mysterious blue orange which\nimproves vitality",
        .effect = vitality_orb_effect
    },
    {
        NULL,
        EMPTY_ITEM,
        NULL,
        NULL
    },
};

stats_t create_stats(char const *name, dict_t *sheets_dict);
void draw_stats_menu(sfRenderWindow *window, stats_t *stats);
inventory_t *create_inventory(sfVector2f position, char const *name);
void destroy_inventory(inventory_t *inventory);
void play_inventory(sfRenderWindow *window,
    inventory_t *inventory, inventory_t *inventory2);
void insert_item(inventory_t *inventory,
    item_type_t item, dict_t *items_dict);
void drag_into_slot(slot_t *slot, item_t *item);
chest_t **load_level_chests(char *level, dict_t *tiles,
    inventory_t ***inventories, dict_t *items_dict);
void check_openned_chest(game_t *game);
void show_single_inventory(sfRenderWindow *window, physical_entity_t *player);
void update_stats(stats_t *stats, inventory_t *inventory);
void show_item_description(sfRenderWindow *window, sfVector2f mouse_pos,
    inventory_t *inventory);
void dragg_item(inventory_t *inventory, sfVector2f mouse_pos,
    bool *dragging, item_t *dragged_item);
void update_inventory(inventory_t *inventory, sfVector2f mouse_pos);
void draw_inventory(sfRenderWindow *window, inventory_t *inventory);
void draw_stats_menu(sfRenderWindow *window, stats_t *stats);
