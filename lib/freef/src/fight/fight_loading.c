/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** fight loading
*/


#include "basics.h"
#include "dict.h"
#include "fight_macros.h"
#include "init_fight.h"
#include "struct.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <stdbool.h>
#include <stdlib.h>



// change when possible to fight->npc_stats->name
#define TO_REMOVE NPC1
// REMOVE THIS AS FAST AS POSSIBLE

static bool load_arena_textures(fight_t *fight)
{
    char *background_text = my_strcat(2, ARENA_FOLDERS[fight->arena],
        "background.png");
    char *forground_text = my_strcat(2, ARENA_FOLDERS[fight->arena],
        "forground.png");

    if (background_text == NULL || forground_text == NULL)
        return true;
    dict_insert(&fight->text_dict, BACKGROUND_TEXT,
        sfTexture_createFromFile(background_text, NULL));
    dict_insert(&fight->text_dict, FORGROUND_TEXT,
        sfTexture_createFromFile(forground_text, NULL));
    freef("%a%a", background_text, forground_text);
    return false;
}

static bool load_arena_sprites(fight_t *fight)
{
    fight->background = sfSprite_create();
    fight->forground = sfSprite_create();
    if (fight->forground == NULL || fight->background == NULL)
        return true;
    sfSprite_setTexture(fight->background,
        dict_get(fight->text_dict, BACKGROUND_TEXT), sfTrue);
    sfSprite_setTexture(fight->forground,
        dict_get(fight->text_dict, FORGROUND_TEXT), sfTrue);
    sfSprite_setTextureRect(fight->forground, BACKGROUND_REC);
    sfSprite_setTextureRect(fight->background, BACKGROUND_REC);
    return false;
}

bool load_textures(fight_t *fight)
{
    char *temp_path = NULL;

    load_arena_textures(fight);
    for (int i = PLAYER_IDLE_TEXT; i < PLAYER_TEXTURES_END; i++) {
        temp_path = my_strcat(2, FIGHTER_FOLDERS[PLAYER_FIGHTER],
            ANNIMATION_FILES[i - PLAYER_IDLE_TEXT]);
        dict_insert(&fight->text_dict, i,
            sfTexture_createFromFile(temp_path, NULL));
        free(temp_path);
    }
    for (int i = NPC_IDLE_TEXT; i < NPC_TEXTURES_END; i++) {
        temp_path = my_strcat(2, FIGHTER_FOLDERS[TO_REMOVE],
            ANNIMATION_FILES[i - NPC_IDLE_TEXT]);
        dict_insert(&fight->text_dict, i,
            sfTexture_createFromFile(temp_path, NULL));
        free(temp_path);
    }
    return false;
}

bool load_fighters(fight_t *fight)
{
    for (int i = PLAYER_IDLE_TEXT; i < PLAYER_TEXTURES_END; i++) {

    }
    for (int i = NPC_IDLE_TEXT; i < NPC_TEXTURES_END; i++) {

    }
    return false;
}

fight_t *load_fight(game_t *game, physical_entity_t *player_stats,
    physical_entity_t *npc_stats, arenas_t arena)
{
    fight_t *fight = calloc(1, sizeof(fight_t));

    fight->arena = arena;
    fight->npc_stats = npc_stats;
    fight->player_stats = player_stats;
    fight->player = (physical_entity_t) {0};
    fight->npc = (physical_entity_t) {0};
    if (fight == NULL)
        return NULL;
    if (load_textures(fight))
        return NULL;
    if (load_arena_sprites(fight))
        return NULL;
    if (load_fighters(fight))
        return NULL;
    return fight;
}
