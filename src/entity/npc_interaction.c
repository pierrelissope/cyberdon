/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** entities
*/

#include "dict.h"
#include "string.h"
#include "entity.h"
#include "init_texture.h"
#include "inventory.h"
#include "dialog.h"
#include "myutils.h"

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

void process_npc_interaction(physical_entity_t *npc,
    game_t *game, sfEvent *event)
{
    npc->actions = parse_npc_interaction(npc->name);
    if (!npc->actions)
        return;
    sfRenderWindow_setView(game->window, sfRenderWindow_getDefaultView(game->window));
    if (npc->current_action == FIGHT){
        printf("LAUNCH fight\n");
        //LANCER LE COMBAT
        if (my_arraylen((void **)npc->actions) > LAST) {
            //DONNER RECOMPENSE COMBAT AU JOUEUR
            npc->current_action = LAST;
        }
    }
    for (size_t i = 0; npc->actions && npc->actions[npc->current_action][i] != NULL; ++i)
        displayDialogue(game->window, npc->actions[npc->current_action][i], game->font, event);
    if (npc->current_action == FIRST && my_arraylen((void **)npc->actions) > FIGHT)
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

    new_rect.left -= 10;
    new_rect.top -= 10;
    new_rect.height += 20;
    new_rect.width += 20;
    for (int i = 0; world->entities && world->entities[i]; i++) {
        if (strcmp(entity->name, world->entities[i]->name) == 0)
            continue;
        entity_rect = sfRectangleShape_getGlobalBounds(
            world->entities[i]->rect);
        if (sfFloatRect_intersects(&new_rect, &entity_rect, NULL) &&
            sfKeyboard_isKeyPressed(sfKeyEnter) && sfTime_asSeconds(
            sfClock_getElapsedTime(game->status.status_clock)) > 0.7) {
            process_npc_interaction(world->entities[i], game, event);
            sfClock_restart(game->status.status_clock);
            return;
        }
    }
}
