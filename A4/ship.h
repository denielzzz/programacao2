#include "config.h"

#define SHIP_SPEED 2
#define SHIP_Y (BUFFER_H - BUFFER_H / 12)
#define SHIP_W (BUFFER_W / 18)
#define SHIP_H (BUFFER_H / 36)

typedef struct ship
{
    int x, y, dx;
    int lives;
    int respawn_timer;
    int invincible_timer;
} ship_t;

void ship_init(ship_t *ship);

void ship_update();
