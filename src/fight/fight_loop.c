/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** loopers for fighting
*/

#include "struct.h"

int run_fight(game_t *game, physical_entity_t *player, physical_entity_t *npc)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(game->window)) {
        if (handle_fight_event(game, &event, player, npc) == sfEvtClosed)
            return;
        draw_game(game);
    }
    return
}
