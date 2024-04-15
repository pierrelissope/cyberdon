/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** main
*/

#include "game.h"
#include "basics.h"

int main(int ac, char **av)
{
    game_t game = init_game();

    run_game(&game);
}