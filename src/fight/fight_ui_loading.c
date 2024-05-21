/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** fight loading
*/

#include "fight_entity.h"
#include "init_ui.h"

#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <stdlib.h>

static bool init_health(ui_t *ui)
{
    ui->player_health = sfRectangleShape_create();
    if (ui->player_health == NULL)
        return true;
    sfRectangleShape_setSize(ui->player_health, HEALTH_SIZE);
    sfRectangleShape_setFillColor(ui->player_health, HIGH_HEALTH);
    sfRectangleShape_setPosition(ui->player_health, PLAYER_HEALTH_POS);
    ui->npc_health = sfRectangleShape_create();
    if (ui->npc_health == NULL)
        return true;
    sfRectangleShape_setSize(ui->npc_health, HEALTH_SIZE);
    sfRectangleShape_setFillColor(ui->npc_health, HIGH_HEALTH);
    sfRectangleShape_setPosition(ui->npc_health, NPC_HEALTH_POS);
    return false;
}

static bool init_stamina(ui_t *ui)
{
    ui->player_stamina = sfRectangleShape_create();
    if (ui->player_stamina == NULL)
        return true;
    sfRectangleShape_setSize(ui->player_stamina, STAMINA_SIZE);
    sfRectangleShape_setFillColor(ui->player_stamina, HIGH_STAMINA);
    sfRectangleShape_setPosition(ui->player_stamina, PLAYER_STAMINA_POS);
    ui->npc_stamina = sfRectangleShape_create();
    if (ui->npc_stamina == NULL)
        return true;
    sfRectangleShape_setSize(ui->npc_stamina, STAMINA_SIZE);
    sfRectangleShape_setFillColor(ui->npc_stamina, HIGH_STAMINA);
    sfRectangleShape_setPosition(ui->npc_stamina, NPC_STAMINA_POS);
    return false;
}

static bool init_portraits(fight_t *fight)
{
    return false;
}

bool load_ui(fight_t *fight)
{
    if (init_health(&fight->ui))
        return true;
    if (init_portraits(fight))
        return true;
    if (init_stamina(&fight->ui))
        return true;
    return false;
}
