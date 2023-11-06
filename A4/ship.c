#include "ship.h"

void ship_init(ship_t *ship)
{
    ship->x = BUFFER_W / 2;
    ship->y = SHIP_Y;
    ship->dx = 0;
    ship->lives = 1;
    ship->respawn_timer = 0;
    ship->invincible_timer = 60;
    ship->double_shot_timer = 0;
    ship->frame = 0;
    ship->shot_cooldown = 30;
    ship->score = 0;
}

void ship_update(ship_t *ship)
{
    ship->x += ship->dx;

    if(ship->x < SHIP_W / 2)
        ship->x = SHIP_W / 2;
    if(ship->x > BUFFER_W - SHIP_W / 2)
        ship->x = BUFFER_W - SHIP_W / 2;

    if(ship->respawn_timer > 0)
        ship->respawn_timer--;
    if(ship->invincible_timer > 0)
        ship->invincible_timer--;
    if(ship->double_shot_timer > 0)
        ship->double_shot_timer--;
    if(ship->shot_cooldown > 0)
        ship->shot_cooldown--;
}