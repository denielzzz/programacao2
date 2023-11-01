#include "config.h"

#define SHIP_SPEED 2
#define SHIP_Y (BUFFER_H - BUFFER_H / 11)
#define SHIP_W 15
#define SHIP_H 8

typedef struct ship
{
    int x, y, dx;
    int lives;
    int respawn_timer;
    int invincible_timer;
} ship_t;

void ship_init(ship_t *ship);

void ship_update();
