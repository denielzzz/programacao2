#ifndef SHIP_LIB
#define SHIP_LIB

#include "config.h"

#define SHIP_SPEED 2
#define SHIP_Y (BUFFER_H - BUFFER_H / 12)
#define SHIP_W 20
#define SHIP_H 10

typedef struct ship
{
    int x, y, dx;
    int lives;
    int respawn_timer;
    int invincible_timer;
    int shot_timer;
    int shot_cooldown;
    int frame;
} ship_t;

void ship_init(ship_t *ship);

void ship_update();

#endif