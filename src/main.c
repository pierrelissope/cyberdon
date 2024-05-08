/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** main
*/

#include "game.h"
#include "basics.h"
#include <time.h>

int main(int ac, char **av)
{
    game_t game = init_game();

    if (!game.is_valid) {
        destroy_game(&game);
        return 84;
    }
    run_game(&game);
    destroy_game(&game);
    return 0;
}
