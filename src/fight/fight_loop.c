/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** loopers for fighting
*/
#include "fight_entity.h"
#include "fight_macros.h"
#include "struct.h"
#include "fight.h"

int run_fight(game_t *game, physical_entity_t *player,
    physical_entity_t *npc, arenas_t arena)
{
    sfEvent event;
    fight_t *fight = load_fight(game, player, npc, arena);

    while (sfRenderWindow_isOpen(game->window)) {
        if (handle_fight_event(game, fight, &event) == sfEvtClosed)
            return -1;
        draw_fight(fight, game->window);
        update_fight(fight);
    }
    return 0;
}

void test(game_t *game)
{
    physical_entity_t npc_tmp = {0};

    npc_tmp.type = 1;
    run_fight(game, game->player, &npc_tmp, DEFAULT);
}
