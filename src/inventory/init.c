/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** init
*/

#include <string.h>

#include "game.h"
#include "basics.h"
#include "struct.h"
#include "inventory.h"

static sfRectangleShape *create_inventory_box(sfVector2f position)
{
    sfRectangleShape *box = sfRectangleShape_create();

    sfRectangleShape_setSize(box, (sfVector2f){560.f, 440.f});
    sfRectangleShape_setOutlineColor(box, LIGHT_WHITE);
    sfRectangleShape_setOutlineThickness(box, 1);
    sfRectangleShape_setFillColor(box, GREY);
    sfRectangleShape_setPosition(box, position);
    return box;
}

static void setup_slot(slot_t **slots, size_t x, size_t y,
    sfVector2f position)
{
    float x_offset = position.x + SLOT_MARGIN;
    float y_offset = position.y + SLOT_MARGIN;

    sfRectangleShape_setOutlineColor(slots[y][x].box,
        LIGHT_WHITE);
    sfRectangleShape_setOutlineThickness(slots[y][x].box,
        OUTLINE_THIKNESS);
    sfRectangleShape_setSize(slots[y][x].box,
        (sfVector2f){SLOT_SIZE, SLOT_SIZE});
    sfRectangleShape_setFillColor(slots[y][x].box, DARK_GREY);
    sfRectangleShape_setPosition(slots[y][x].box,
    (sfVector2f){x_offset + x * (SLOT_SIZE + SLOT_MARGIN),
        y_offset + y * (SLOT_SIZE + SLOT_MARGIN) + SLOTS_MARGIN_TOP});
}

static slot_t **create_inventory_slots(sfVector2f position)
{
    slot_t **slots = calloc(INVENTORY_SIZE_Y, sizeof(slot_t *));

    for (size_t y = 0; y < INVENTORY_SIZE_Y; ++y) {
        slots[y] = calloc(INVENTORY_SIZE_X, sizeof(slot_t));
        for (size_t x = 0; x < INVENTORY_SIZE_X; ++x) {
            slots[y][x].box = sfRectangleShape_create();
            setup_slot(slots, x, y, position);
            slots[y][x].item = calloc(1, sizeof(item_t));
        }
    }
    return slots;
}

static sfText *create_text(sfVector2f pos, const char *str, sfFont *font)
{
    sfText *text = sfText_create();

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 36);
    sfText_setString(text, str);
    sfText_setFillColor(text, sfWhite);
    sfText_setPosition(text, pos);
    return text;
}

inventory_t *create_inventory(sfVector2f position, char const *name,
    sfFont *font)
{
    inventory_t *inventory = calloc(1, sizeof(inventory_t));

    inventory->name = strdup(name);
    inventory->text =
        create_text((sfVector2f){position.x + 172,
            position.y + 30}, name, font);
    inventory->box = create_inventory_box(position);
    inventory->slots = create_inventory_slots(position);
    return inventory;
}
