/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** chest
*/

#include <stdlib.h>
#include <string.h>

#include "myutils.h"
#include "entity.h"
#include "inventory.h"
#include "init_texture.h"

chest_t *create_chest(const char *chest_name,
    sfVector2f pos, dict_t *tiles_dict)
{
    chest_t *chest = calloc(1, sizeof(chest_t));

    if (chest == NULL)
        return NULL;
    chest->name = strdup(chest_name);
    chest->rect = sfRectangleShape_create();
    chest->sprite = sfSprite_create();
    sfRectangleShape_setPosition(chest->rect,
        (sfVector2f){pos.x * TILE_SIZE, pos.y * TILE_SIZE});
    sfRectangleShape_setSize(chest->rect, (sfVector2f){30, 30});
    sfSprite_setTexture(chest->sprite,
        dict_get(tiles_dict, CHEST), sfTrue);
    sfSprite_setOrigin(chest->sprite, (sfVector2f){128 / 2, 90});
    sfSprite_setPosition(chest->sprite, isom_pos_converter_z(pos));
    sfSprite_setTextureRect(chest->sprite, (sfIntRect){0, 0, 128, 94});
    return chest;
}

static item_type_t get_item_enum(char const *item)
{
    for (size_t i = 0; ITEMS_LINK_ARRAY[i].str_type != NULL; ++i) {
        if (strcmp(item, ITEMS_LINK_ARRAY[i].str_type) == 0) {
            printf("J'insert %s\n", ITEMS_LINK_ARRAY[i].str_type);
            return ITEMS_LINK_ARRAY[i].enum_type;
        }
    }
    dprintf(2, "INSERTING ISSUE\n");
    return SPEED_ORB;
}

static inventory_t *build_inventory_content(char const *chest_name,
    dict_t *items_dict)
{
    inventory_t *inventory = create_inventory((sfVector2f){1300, 300},
        chest_name);
    char *content = open_file("levels/chest_content.conf");
    char **lines = my_str_to_all_array(content, "\n");
    char **tokens = NULL;

    for (size_t i = 0; lines != NULL && lines[i] != NULL; ++i) {
        tokens = my_str_to_all_array(lines[i], ";");
        if (my_strlen_array(tokens) == 0 || strcmp(tokens[0], chest_name) != 0) {
            free_str_array(tokens);
            continue;
        }
        for (size_t j = 1; tokens != NULL && tokens[j] != NULL; ++j)
            insert_item(inventory, get_item_enum(tokens[j]), items_dict);
        free_str_array(tokens);
    }
    free(content);
    free_str_array(lines);
    return inventory;
}

static inventory_t *get_chest_inventory(const char *chest_name,
    inventory_t ***inventories, dict_t *items_dict)
{
    inventory_t *inventory = NULL;

    for (size_t i = 0; (*inventories) != NULL && (*inventories)[i] != NULL; ++i) {
        if (strcmp((*inventories)[i]->name, chest_name) == 0)
            return (*inventories)[i];
    }
    inventory = build_inventory_content(chest_name, items_dict);
    append_ptr((void ***)inventories, inventory, NULL);
    return inventory;
}

sfVector2f get_pos_by_token(char *coords)
{
    char **tokens = my_str_to_all_array(coords, ":");
    sfVector2f pos = {0};

    pos.x = atof(tokens[0]);
    pos.y = atof(tokens[1]);
    free_str_array(tokens);
    return pos;
}

static chest_t **parse_level_chests(char **lines, inventory_t ***inventories,
    dict_t *tiles, dict_t *items_dict)
{
    chest_t **chests = NULL;
    chest_t *chest = NULL;
    char **tokens = NULL;

    for (int i = 0; lines[i]; i++) {
        tokens = my_str_to_all_array(lines[i], ";");
        if (my_strlen_array(tokens) != 2)
            return NULL;
        chest = create_chest(tokens[0], get_pos_by_token(tokens[1]), tiles);
        chest->inventory = get_chest_inventory(chest->name,
            inventories, items_dict);
        append_ptr((void ***)&chests, chest, NULL);
    }
    free_str_array(lines);
    return chests;
}

chest_t **load_level_chests(char *level, dict_t *tiles,
    inventory_t ***inventories, dict_t *items_dict)
{
    char *path = concat_mem((char *)LEVELS_MAP_PATHS, level,
        "/chests.conf");
    char *buffer = NULL;
    char **lines = NULL;
    chest_t **chests = NULL;

    buffer = open_file(path);
    lines = my_str_to_all_array(buffer, "\n");
    chests = parse_level_chests(lines, inventories, tiles, items_dict);
    return chests;
}
