#include "shot.h"

void shot_init(shot_t *shot)
{
    shot->alive = 0;
}

void shot_fire(shot_t *shot, int x, int y)
{
    if(!shot->alive)
    {
        shot->x = x;
        shot->y = y;
        shot->dy = -SHOT_SPEED;
        shot->alive = 1;
    }
}

void shot_update(shot_t *shot)
{
    if(shot->alive)
    {
        shot->y += shot->dy;
        if(shot->y <= 0)
        {
            shot->alive = 0;
        }
    }
}