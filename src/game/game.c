/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** game
*/

#include "game.h"
#include "init_texture.h"
#include "init_entity.h"

const sfVector2f PLAYER_START_POS = {10, 110};

static dict_t *load_entity_sheets(const init_texture_t ENTIY_TEXTURE_INIT[])
{
    dict_t *dict = NULL;
    sfTexture *texture = NULL;

    for (int i = 0; ENTIY_TEXTURE_INIT[i].texture_path; i++) {
        texture = sfTexture_createFromFile
            (ENTIY_TEXTURE_INIT[i].texture_path, NULL);
        if (!texture)
            return NULL;
        dict_insert(&dict, ENTIY_TEXTURE_INIT[i].texture_name, texture);
    }
    return dict;
}

static int load_assets_dicts(game_t *game)
{
    sfTexture *texture = NULL;

    if (!dict_insert(&game->sheets_dict, PLAYER,
        load_entity_sheets(PLAYER_TEXTURE_INIT)) ||
        !dict_insert(&game->sheets_dict, VILLAGER,
        load_entity_sheets(VILLAGER_TEXTURE_INIT)))
        return EXIT_FAILURE;
    for (int i = 0; TILES_TEXTURE_INIT[i].texture_path; i++) {
        texture = sfTexture_createFromFile
            (TILES_TEXTURE_INIT[i].texture_path, NULL);
        if (!texture)
            return EXIT_FAILURE;
        dict_insert(&game->tiles_dict,
            TILES_TEXTURE_INIT[i].texture_name, texture);
    }
    return EXIT_SUCCESS;
}

game_t init_game(void)
{
    game_t game = {0};

    if (load_assets_dicts(&game) == EXIT_FAILURE)
        return game;
    game.world = init_world();
    game.player = init_entity(PLAYER_START_POS, PLAYER, "playername",
        game.sheets_dict);
    if (!game.player->is_valid)
        return game;
    load_level(&game.world, 1, game.tiles_dict, game.sheets_dict);
    game.is_valid = true;
    return game;
}

void destroy_game(game_t *game)
{
    destroy_entity(game->player);
}

void draw_game(game_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    draw_level(game->window, &game->world, game->player);
    sfRenderWindow_display(game->window);
}

void run_game(game_t *game)
{
    sfEvent event;

    game->window = sfRenderWindow_create(
        (sfVideoMode){1920, 1080, 32}, "MyRPG", sfClose, NULL);
    sfRenderWindow_setFramerateLimit(game->window, 60);
    while (sfRenderWindow_isOpen(game->window)) {
        move_entity(game->player, &event, &(game->world));
        if (handle_event(game, &event) == sfEvtClosed)
            return;
        update_entity(game->player);
        draw_game(game);
    }
}
