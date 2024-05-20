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
#include "menu.h"

game_info_t *init_game_info(void)
{
    game_info_t *game_info = malloc(sizeof(game_info_t));
    if (!game_info) {
        printf("malloc failled");
        return NULL;
    }
    game_info->save_file = "save/default_save.dat";
    game_info->screen_res.x = 1920;
    game_info->screen_res.y = 1080;

    return game_info;
}

int main(int ac, char **av)
{
    game_info_t *info = init_game_info();
    menu(info);
    return 0;
}
