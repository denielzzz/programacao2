#include "enemy.h"

void enemies_init(enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS])
{
    for(int i = 0; i < ENEMY_LINES; i++)
    {
        for(int j = 0; j < ENEMY_COLUNS; j++)
        {
            enemy[i][j].type = (enemy_type_t) (i+1)/2;
            enemy[i][j].x = BUFFER_W/7 + (j+1) * BUFFER_W/ENEMY_COLUNS*2/3;
            enemy[i][j].y = BUFFER_H/20 + (i+1) * BUFFER_H/ENEMY_LINES/3;
            enemy[i][j].alive = 1;
            enemy[i][j].dx = ENEMY_SPEED;
            enemy[i][j].frame = 0;
        }
    }
}

void enemies_update(enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS])
{   
    int coli = 0;
    for(int i = 0; i < ENEMY_LINES; i++)
    {
        for(int j = 0; j < ENEMY_COLUNS; j++)
        {
            if(!enemy[i][j].alive)
                continue;

            enemy[i][j].x += enemy[i][j].dx;
            enemy[i][j].frame = !enemy[i][j].frame;

            if(enemy[i][j].x - ENEMY_W/2 <= 0 || enemy[i][j].x + ENEMY_W/2 >= BUFFER_W)
                coli = 1;
        }
    }
    if(coli)
    {
        for(int i = 0; i < ENEMY_LINES; i++)
        {
            for(int j = 0; j < ENEMY_COLUNS; j++)
            {
                enemy[i][j].dx *= -1;
                enemy[i][j].x += enemy[i][j].dx;
                enemy[i][j].y += ENEMY_H/2;
            }
        }
    }
}