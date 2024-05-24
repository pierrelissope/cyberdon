/*
** EPITECH PROJECT, 2024
** my rpg
** File description:
** state actions
*/

#include "fight.h"
#include "fight_entity.h"
#include "fight_macros.h"
#include "struct.h"

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>
#include <stdbool.h>

bool annimation_bypass(fighter_entity_t *, fighter_state_t new_state)
{
    for (fighter_state_t i = 0; i < N_OF_BYPASS; i++) {
        if (new_state == STATE_LOCKS_BYPASS[i]) {
            return true;
        }
    }
    return false;
}

bool change_state(fighter_entity_t *entity, fighter_state_t new_state)
{
    if (entity->hit &&
        sfTime_asMilliseconds(sfClock_getElapsedTime(entity->i_counter)) <
        entity->iframes)
        return false;
    if (entity->annimation_lock && !annimation_bypass(entity, new_state))
        return false;
    if (entity->state != new_state) {
        entity->annimation_sheets[entity->state]->current_frame = 0;
        entity->annimation_sheets[entity->state]->text_rec.left = 0;
        sfClock_restart(entity->clock);
        entity->state = new_state;
        return true;
    }
    return false;
}
