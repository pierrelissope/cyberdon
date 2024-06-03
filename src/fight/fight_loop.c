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
#include <stdbool.h>
#include <stdio.h>

static int handle_endgame_events(game_t *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window);
            return sfEvtClosed;
        }
    }
    return 0;
}

static int run_frame(fight_t *fight, game_t *game)
{
    update_fight(fight, game);
    if (handle_fight_event(game, fight) == sfEvtClosed)
        return -1;
    if (fight->npc->stats.hp <= 0)
        return 1;
    if (fight->player->stats.hp <= 0)
        return 2;
    draw_fight(fight, game->window);
    return 0;
}

static bool fight_checks(int *carry, game_t *game,
    fight_t *fight, bool *end_game)
{
    if (*end_game == false)
        *carry = run_frame(fight, game);
    if (*carry == -1)
        return true;
    if ((*carry == 1 || *carry == 2) && *end_game == false) {
        *end_game = true;
        sfClock_restart(fight->end_game_timer);
    }
    if (*end_game) {
        display_fight_end(fight, game, *carry);
        handle_endgame_events(game);
    }
    if (*end_game &&
        sfTime_asSeconds(sfClock_getElapsedTime(fight->end_game_timer)) > 1.5)
        return true;
    return false;
}

int run_fight(game_t *game, physical_entity_t *player,
    physical_entity_t *npc, arenas_t)
{
    fight_t *fight = load_fight(game, player, npc);
    int carry = 0;
    bool end_game = false;

    if (fight == NULL)
        return -1;
    while (sfRenderWindow_isOpen(game->window)) {
        if (fight_checks(&carry, game, fight, &end_game))
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
