#include "map.h"
#include <stdlib.h>

void stars_init(STAR* stars)
{
    for(int i = 0; i < STARS_N; i++)
    {
        stars[i].y = rand() % BUFFER_H;
        stars[i].speed = (float)rand() / (float)RAND_MAX * (1 - 0.1);
    }
}

void stars_update(STAR* stars)
{
    for(int i = 0; i < STARS_N; i++)
    {
        stars[i].y += stars[i].speed;
        if(stars[i].y >= BUFFER_H)
        {
            stars[i].y = 0;
            stars[i].speed = (float)rand() / (float)RAND_MAX * (1 - 0.1);
        }
    }
}   