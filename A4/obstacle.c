#include "obstacle.h"

void obstacle_init(obstacle_t *obstacle)
{
    for(int i = 0; i < OBSTACLE_N; i++)
    {
        obstacle[i].x = (i+1) * BUFFER_W / 5;
        obstacle[i].y = BUFFER_H - BUFFER_H / 4;
        obstacle[i].life = OBSTACLE_LIFE;
    }
}

void obstacle_update(obstacle_t *obstacle)
{
    for(int i = 0; i < OBSTACLE_N; i++)
    {
        if(obstacle[i].life <= 0)
            obstacle[i].life = 0;
    }
}