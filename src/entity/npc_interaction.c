/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** entities
*/

#include "dict.h"
#include "string.h"
#include "entity.h"
#include "inventory.h"
#include "dialog.h"
#include "myutils.h"
#include "fight.h"
#include "mymenu.h"

static void free_triple_array(char ***array)
{
    for (size_t i = 0; array && array[i]; ++i) {
        free_str_array(array[i]);
    }
    free(array);
}

static char **parse_single_action(char *action)
{
    char **tokens = my_str_to_all_array(action, ";");

    return tokens;
}

char ***parse_npc_interaction(char *npc_name)
{
    char path[200];
    char *buffer = NULL;
    char **tokens = NULL;
    char ***actions = NULL;

    sprintf(path, "./levels/dialogs/%s.conf", npc_name);
    buffer = open_file(path);
    if (buffer == NULL)
        return NULL;
    tokens = my_str_to_all_array(buffer, "=");
    for (size_t i = 0; tokens && tokens[i] != NULL; ++i)
        append_ptr((void ***)&actions, parse_single_action(tokens[i]), NULL);
    free_str_array(tokens);
    free(buffer);
    return actions;
}

static void process_fight_interaction(game_t *game, physical_entity_t *npc)
{
    play_transition_screen(game->window, game->tiles_dict);
    if (run_fight(game, game->player, npc, 0) == 1) {
        if (my_arraylen((void **)npc->actions) > LAST)
            npc->current_action = LAST;
        sfRenderWindow_setView(game->window, game->player_view);
        return free_triple_array(npc->actions);
    } else {
        sfRenderWindow_setView(game->window, game->player_view);
        return free_triple_array(npc->actions);
    }
}

void process_npc_interaction(physical_entity_t *npc,
    game_t *game, sfEvent *event)
{
    npc->actions = parse_npc_interaction(npc->name);
    if (!npc->actions)
        return;
    sfRenderWindow_setView(game->window,
        sfRenderWindow_getDefaultView(game->window));
    if (npc->current_action == FIGHT) {
        return process_fight_interaction(game, npc);
    }
    for (size_t i = 0; npc->actions &&
        npc->actions[npc->current_action][i] != NULL; ++i)
        display_dialogue(game, npc->actions[npc->current_action][i],
            npc, event);
    if (npc->current_action == FIRST &&
        my_arraylen((void **)npc->actions) > FIGHT)
        npc->current_action = FIGHT;
    sfRenderWindow_setView(game->window, game->player_view);
    free_triple_array(npc->actions);
}

void handle_npc_interactions(physical_entity_t *entity,
    game_t *game, sfEvent *event)
{
    sfFloatRect entity_rect = {0};
    sfFloatRect new_rect = sfRectangleShape_getGlobalBounds(entity->rect);
    world_t *world = &game->world;

    new_rect = (sfFloatRect){new_rect.left - 20, new_rect.top - 20,
        new_rect.height + 40, new_rect.width + 40};
    for (int i = 0; game->world.entities && game->world.entities[i]; i++) {
        if (strcmp(entity->name, world->entities[i]->name) == 0)
            continue;
        entity_rect = sfRectangleShape_getGlobalBounds(
            game->world.entities[i]->rect);
        if (sfFloatRect_intersects(&new_rect, &entity_rect, NULL) &&
            sfKeyboard_isKeyPressed(sfKeyEnter) && sfTime_asSeconds(
            sfClock_getElapsedTime(game->status.status_clock)) > 0.7) {
            process_npc_interaction(game->world.entities[i], game, event);
            sfClock_restart(game->status.status_clock);
            return;
        }
    }
}
