/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** loopers for fighting
*/

#include "fight_entity.h"
#include "fight_macros.h"
#include "fight_transfer.h"
#include "struct.h"
#include "fight.h"
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>
#include <SFML/Window/Event.h>
#include <stdio.h>

static int run_frame(fight_t *fight, game_t *game, sfEvent *event)
{
    update_fight(fight);
    if (handle_fight_event(game, fight, event) == sfEvtClosed)
        return -1;
    if (fight->npc->stats.hp <= 0)
        return 1;
    if (fight->player->stats.hp <= 0)
        return 2;
    draw_fight(fight, game->window);
    return 0;
}

int run_fight(game_t *game, physical_entity_t *player,
    physical_entity_t *npc, arenas_t arena)
{
    sfEvent event;
    fight_t *fight = load_fight(game, player, npc, arena);
    int carry = 0;

    if (fight == NULL)
        return -1;
    while (sfRenderWindow_isOpen(game->window)) {
        carry = run_frame(fight, game, &event);
        if (carry != 0)
            break;
    }
    destroy_fight(fight);
    return carry;
}

void test(game_t *game)
{
    physical_entity_t npc_tmp = {0};

    npc_tmp.type = 1;
    npc_tmp.fighter_skin = BIG_DUDE;
    npc_tmp.stats.attack = 3;
    npc_tmp.stats.defense = 1;
    npc_tmp.stats.stamina = 15;
    npc_tmp.stats.stamina_regen = 1;
    npc_tmp.stats.hp = 100;
    npc_tmp.stats.speed = 2;
    npc_tmp.stats.strength = 1;
    game->player->fighter_skin = BLUE_GIRL;
    game->player->stats.speed = 10;
    game->player->stats.stamina = 20;
    printf("%d\n", run_fight(game, game->player, &npc_tmp, DEFAULT));
}
