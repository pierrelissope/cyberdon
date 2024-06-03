/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** fight loading
*/

#include "dict.h"
#include "fight_entity.h"
#include "fight_macros.h"
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

static bool init_hp(ui_t *ui)
{
    ui->player_hp = sfRectangleShape_create();
    if (ui->player_hp == NULL)
        return true;
    sfRectangleShape_setSize(ui->player_hp, hp_SIZE);
    sfRectangleShape_setFillColor(ui->player_hp, HIGH_HP);
    sfRectangleShape_setPosition(ui->player_hp, PLAYER_HP_POS);
    ui->npc_hp = sfRectangleShape_create();
    if (ui->npc_hp == NULL)
        return true;
    sfRectangleShape_setSize(ui->npc_hp, hp_SIZE);
    sfRectangleShape_setFillColor(ui->npc_hp, HIGH_HP);
    sfRectangleShape_setPosition(ui->npc_hp, NPC_HP_POS);
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

static void init_portraits_rec(fight_t *fight)
{
    sfRectangleShape_setSize(fight->ui.player_portrait, PORTRAIT_SIZE);
    sfRectangleShape_setSize(fight->ui.npc_portrait, PORTRAIT_SIZE);
    sfRectangleShape_setPosition(fight->ui.player_portrait,
        PLAYER_PORTRAIT_POS);
    sfRectangleShape_setPosition(fight->ui.npc_portrait, NPC_PORTRAIT_POS);
    sfRectangleShape_setTexture(fight->ui.player_portrait,
        dict_get(fight->text_dict,
        PLAYER_PORTRAIT_TEXT), false);
    sfRectangleShape_setTexture(fight->ui.npc_portrait,
        dict_get(fight->text_dict,
        NPC_PORTRAIT_TEXT), false);
    sfRectangleShape_setOutlineColor(fight->ui.player_portrait, sfWhite);
    sfRectangleShape_setOutlineColor(fight->ui.npc_portrait, sfWhite);
    sfRectangleShape_setOutlineThickness(fight->ui.npc_portrait, 2.5);
    sfRectangleShape_setOutlineThickness(fight->ui.player_portrait, 2.5);
}

static bool init_portraits(fight_t *fight)
{
    fight->ui.npc_portrait = sfRectangleShape_create();
    if (fight->ui.npc_portrait == NULL)
        return true;
    fight->ui.player_portrait = sfRectangleShape_create();
    if (fight->ui.player_portrait == NULL)
        return true;
    init_portraits_rec(fight);
    return false;
}

static bool init_end_rec(sfRectangleShape **rec, sfTexture *text)
{
    *rec = sfRectangleShape_create();
    if (*rec == NULL)
        return true;
    sfRectangleShape_setSize(*rec, END_SIZE);
    sfRectangleShape_setPosition(*rec, END_POS);
    sfRectangleShape_setTexture(*rec, text, false);
    return false;
}

bool load_ui(fight_t *fight)
{
    if (init_hp(&fight->ui))
        return true;
    if (init_portraits(fight))
        return true;
    if (init_stamina(&fight->ui))
        return true;
    if (init_end_rec(&fight->ui.lose, dict_get(fight->text_dict, LOSE_TEXT)) ||
        init_end_rec(&fight->ui.win, dict_get(fight->text_dict, WIN_TEXT)))
        return true;
    return false;
}
