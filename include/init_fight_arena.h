/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** init_fight
*/

#ifndef INIT_ARENA_H
    #define INIT_ARENA_H

    #include "fight_macros.h"
    #include <SFML/Graphics/Rect.h>
    #include <SFML/System/Vector2.h>
    #include <stddef.h>

static const sfIntRect BACKGROUND_REC = {
    .height = 1920,
    .width = 1080,
    .top = 0,
    .left = 0
};

static const char *ARENA_FOLDERS[] = {
    [DEFAULT] = "assets/arenas/default/",
    [STREET] = "assets/arenas/street/",
    [BAR] = "assets/arenas/bar/",
    [SUS] = "assets/arenas/sus/",
    NULL
};

static const int BACKGROUND_FRAMES = 1;
static const int FORGROUND_FRAMES = 1;
static const int BACKGROUND_REFRESH_RATE = 1;
static const int FORGROUND_REFRESH_RATE = 1;

#endif
