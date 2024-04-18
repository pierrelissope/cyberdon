/*
** EPITECH PROJECT, 2024
** csfml_isom
** File description:
** world
*/

#include "world.h"
#include "entity.h"

const int COLLISION_OPACITY = 30;

world_t init_world(void)
{
    world_t world = {0};

    return world;
}

int load_level(world_t *world, int level, dict_t *tiles)
{
    char **floor = load_floor(level);
    char **walls = load_walls(level);

    if (!floor || !walls) {
        freef("%t%t", floor, walls);
        return EXIT_FAILURE;
    }
    for (int y = 0; floor[y]; y++)
        if (parse_floor_line(floor, world, y, tiles) == EXIT_FAILURE) {
            freef("%t%t", floor, walls);
            return EXIT_FAILURE;
        }
    for (int y = 0; walls[y]; y++)
        if (parse_walls_line(walls, world, y, tiles) == EXIT_FAILURE) {
            freef("%t%t", floor, walls);
            return EXIT_FAILURE;
        }
    free_str_array(floor);
    return 0;
}

static void draw_walls_behind(world_t *world, sfFloatRect *player_bounds,
    sfRenderWindow *window)
{
    sfFloatRect wall_bounds = {0};

    for (int i = 0; world->walls && world->walls[i]; i++) {
        wall_bounds =
            sfSprite_getGlobalBounds(world->walls[i]->sprite);
        if (wall_bounds.top > player_bounds->top + COLLISION_OPACITY)
            continue;
        sfRenderWindow_drawSprite(window, world->walls[i]->sprite, NULL);
        sfRenderWindow_drawRectangleShape(window, world->walls[i]->rect, NULL);
    }
}

static void draw_walls_front(world_t *world, sfFloatRect *player_bounds,
    sfRenderWindow *window)
{
    sfFloatRect wall_bounds = {0};

    for (int i = 0; world->walls && world->walls[i]; i++) {
        wall_bounds = sfSprite_getGlobalBounds(world->walls[i]->sprite);
        if (wall_bounds.top <= player_bounds->top + COLLISION_OPACITY)
            continue;
        sfRenderWindow_drawSprite(window, world->walls[i]->sprite, NULL);
        sfRenderWindow_drawRectangleShape(window, world->walls[i]->rect, NULL);
    }
}

void draw_level(sfRenderWindow *window, world_t *world,
    physical_entity_t *player)
{
    sfFloatRect player_bounds =
        sfSprite_getGlobalBounds
        (player->sprite_sheets[player->current_spritesheet]);

    for (int i = 0; world->floor && world->floor[i]; i++) {
        sfRenderWindow_drawSprite(window, world->floor[i]->sprite, NULL);
        sfRenderWindow_drawRectangleShape(window, world->floor[i]->rect, NULL);
    }
    draw_walls_behind(world, &player_bounds, window);
    draw_entity(player, window);
    draw_walls_front(world, &player_bounds, window);
}
