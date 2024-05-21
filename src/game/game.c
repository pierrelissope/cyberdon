/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** game
*/

#include "game.h"
#include "init_texture.h"
#include "init_entity.h"
#include "view.h"
#include "dict.h"
#include "world.h"
#include "status.h"
#include "inventory.h"
#include "mymenu.h"

static dict_t *load_textures_dict(const init_texture_t ENTIY_TEXTURE_INIT[])
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
    if (!dict_insert(&game->sheets_dict, PLAYER,
        load_textures_dict(PLAYER_TEXTURE_INIT)) ||
        !dict_insert(&game->sheets_dict, VILLAGER,
        load_textures_dict(VILLAGER_TEXTURE_INIT)))
        return EXIT_FAILURE;
    game->tiles_dict = load_textures_dict(TILES_TEXTURE_INIT);
    game->items_dict = load_textures_dict(ITEMS_TEXTURE_INIT);
    return EXIT_SUCCESS;
}

static void init_game_components(game_t *game)
{
    game->status = init_status();
    if (!game->status.is_valid)
        return;
    game->loading_page = init_loading_page(game->tiles_dict);
    load_level(game, "city", game->tiles_dict);
    game->is_valid = true;
}

game_t init_game(void)
{
    game_t game = {0};

    if (load_assets_dicts(&game) == EXIT_FAILURE)
        return game;
    game.clock = sfClock_create();
    game.world = init_world();
    game.player = init_entity(PLAYER_START_POS, PLAYER, "playername",
        game.sheets_dict);
    if (!game.player->is_valid)
        return game;
    game.player_view = init_player_view();
    if (!game.player_view)
        return game;
    init_game_components(&game);
    return game;
}

void destroy_game(game_t *game)
{
    if (game->player)
        destroy_entity(game->player);
}

void draw_game(game_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    sfRenderWindow_setView(game->window, game->player_view);
    draw_level(game->window, &game->world, game->player);
    sfRenderWindow_display(game->window);
}

void run_game(game_t *game)
{
    sfEvent event;

    game->window = sfRenderWindow_create(
        (sfVideoMode){1920, 1080, 32}, "MyRPG", sfClose | sfResize, NULL);
    sfRenderWindow_setFramerateLimit(game->window, 60);
    while (sfRenderWindow_isOpen(game->window)) {
        if (handle_event(game, &event) == sfEvtClosed)
            return;
        if (game->game_state == IN_GAME)
            move_entity(game->player, &event, &(game->world));
        if (sfKeyboard_isKeyPressed(sfKeyE))
            show_single_inventory(game->window, game->player);
        check_openned_chest(game);
        teleport_player(game, game->world.teleporters, &game->status);
        animate_world(&(game->world));
        update_entity(game->player);
        center_view(game->player_view, game->player->rect, game);
        draw_game(game);
    }
}
