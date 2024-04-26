/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** loopers for fighting
*/

#include "fight_macros.h"
#include "struct.h"
#include "fight.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <stdbool.h>

int run_fight(game_t *game, physical_entity_t *player_stats,
    physical_entity_t *npc_stats, arenas_t arena)
{
    sfEvent event;
    fight_t *fight = load_fight();

    while (sfRenderWindow_isOpen(game->window)) {
        if (handle_fight_event(game, &event, fight) == sfEvtClosed)
            return 42;
        draw_fight(game, fight);
    }
    return 0;
}
