/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** game
*/

#include "game.h"

const char *PLAYER_IDLE_SHEET = "./assets/spritesheets/player/idle.png";
const char *PLAYER_RUNNING_SHEET = "./assets/spritesheets/player/running.png";

const char *GRASS_PATH = "./assets/blocks/grass.png";
const char *STONE_PATH = "./assets/blocks/stone.png";
const char *STONE_WALL_PATH = "./assets/blocks/stone_wall.png";
const char *WOOD_WALL_PATH = "./assets/blocks/wood_wall.png";

const sfVector2f PLAYER_START_POS = {10, 110};

static sfTexture **load_player_sheets(void)
{
    sfTexture **array = NULL;
    sfTexture *idle = sfTexture_createFromFile(PLAYER_IDLE_SHEET, NULL);
    sfTexture *running = sfTexture_createFromFile(PLAYER_RUNNING_SHEET, NULL);

    if (!idle || !running) {
        sfTexture_destroy(idle);
        sfTexture_destroy(running);
        return NULL;
    }
    append_ptr((void ***)&array, idle, NULL);
    if (!array)
        return NULL;
    append_ptr((void ***)&array, running, NULL);
    if (!array)
        return NULL;
    return array;
}

static int load_assets_dicts(game_t *game)
{
    sfTexture *grass = sfTexture_createFromFile(GRASS_PATH, NULL);
    sfTexture *stone = sfTexture_createFromFile(STONE_PATH, NULL);
    sfTexture *stone_wall = sfTexture_createFromFile(STONE_WALL_PATH, NULL);
    sfTexture *wood_wall = sfTexture_createFromFile(WOOD_WALL_PATH, NULL);
    sfTexture **texture_array = NULL;

    if (!grass || !stone || !stone_wall || !wood_wall)
        return EXIT_FAILURE;
    dict_insert(&game->tiles_dict, "grass", grass);
    dict_insert(&game->tiles_dict, "stone", stone);
    dict_insert(&game->tiles_dict, "stone_wall", stone_wall);
    dict_insert(&game->tiles_dict, "wood_wall", wood_wall);
    texture_array = load_player_sheets();
    if (!texture_array)
        return EXIT_FAILURE;
    dict_insert(&game->sheets_dict, "player", texture_array);
    return EXIT_SUCCESS;
}

game_t init_game(void)
{
    game_t game = {0};

    if (load_assets_dicts(&game) == EXIT_FAILURE)
        return game;
    game.world = init_world();
    game.player = init_entity(PLAYER_START_POS, "player", game.sheets_dict);
    if (!game.player.is_valid)
        return game;
    load_level(&game.world, 1, game.tiles_dict);
    game.is_valid = true;
    return game;
}

void destroy_game(game_t *game)
{
    destroy_entity(&(game->player));
}

void draw_game(game_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    draw_level(game->window, &game->world, &game->player);
    sfRenderWindow_display(game->window);
}

void run_game(game_t *game)
{
    sfEvent event;

    game->window = sfRenderWindow_create(
        (sfVideoMode){1920, 1080, 32}, "MyRPG", sfClose, NULL);
    sfRenderWindow_setFramerateLimit(game->window, 60);
    while (sfRenderWindow_isOpen(game->window)) {
        move_entity(&(game->player), &event, &(game->world));
        if (handle_event(game, &event) == sfEvtClosed)
            return;
        update_entity(&game->player);
        draw_game(game);
    }
}
