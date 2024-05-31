/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** sfx
*/

#include "struct.h"
#include "entity.h"

sound_t init_sound(void)
{
    sound_t sounds = {0};

    sounds.ost = sfMusic_createFromFile("./assets/ost.ogg");
    sounds.punch = sfMusic_createFromFile("./assets/punch.ogg");
    sounds.effect = sfMusic_createFromFile("./assets/effect.wav");
    sounds.fight = sfMusic_createFromFile("./assets/fight.ogg");
    sfMusic_play(sounds.ost);
    sfMusic_setVolume(sounds.ost, 5);
    sfMusic_setVolume(sounds.effect, 9);
    sfMusic_setVolume(sounds.punch, 7);
    sfMusic_setVolume(sounds.fight, 20);
    sfMusic_setLoop(sounds.ost, sfTrue);
    return sounds;
}

void destroy_sound(sound_t *sounds)
{
    sfMusic_destroy(sounds->fight);
    sfMusic_destroy(sounds->effect);
    sfMusic_destroy(sounds->punch);
    sfMusic_destroy(sounds->ost);
}
