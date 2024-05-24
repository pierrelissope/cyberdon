/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** main
*/

#include "game.h"
#include "struct.h"
#include <SFML/System/Vector2.h>
#include "basics.h"
#include <time.h>
#include <string.h>
#include "mh_menu.h"

game_info_t *init_game_info(void)
{
    game_info_t *game_info = malloc(sizeof(game_info_t));
    sfVector2u sizes[] = {{800, 600}, {1280, 720}, {1920, 1080}};

    if (!game_info)
        return NULL;
    game_info->font = FONT;
    game_info->save_file = "save/default_save.dat";
    game_info->screen_res.x = 1920;
    game_info->screen_res.y = 1080;
    memcpy(game_info->sizes, sizes, sizeof(sizes));
    game_info->specifier = 0;
    game_info->key[MOVE_UP] = sfKeyUp;
    game_info->key[MOVE_DOWN] = sfKeyDown;
    game_info->key[MOVE_LEFT] = sfKeyLeft;
    game_info->key[MOVE_RIGHT] = sfKeyRight;
    return game_info;
}

int main(int ac, char **av)
{
    game_t game = init_game();

    if (game.is_valid != true) {
        destroy_game(&game);
        return 84;
    }
    run_game(&game);
    destroy_game(&game);
    return 0;
}
