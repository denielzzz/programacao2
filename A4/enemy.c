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
        }
    }
}

void enemies_update(enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS])
{   
    for(int i = 0; i < ENEMY_LINES; i++)
    {
        int coli = 0;
        for(int j = 0; j < ENEMY_COLUNS; j++)
        {
            if(enemy[i][j].alive)
            {
                enemy[i][j].x += enemy[i][j].dx;
                if(enemy[i][j].x - ENEMY_W/2 <= 0 || enemy[i][j].x + ENEMY_W/2 >= BUFFER_W)
                {
                    if(enemy[i][j].dx < 0)
                        enemy[i][j].x -= enemy[i][j].dx;
                    else
                    {
                        for(int l = 0; l < ENEMY_COLUNS; l++)
                            enemy[i][l].x -= enemy[i][j].dx;
                    }
                    for(int k = 0; k < ENEMY_LINES; k++)
                        for(int l = 0; l < ENEMY_COLUNS; l++)
                        {
                            enemy[k][l].y += BUFFER_H/24;
                            enemy[k][l].dx *= -1;
                        }
                    coli = 1;
                    break;
                }
            }
        }
        if(coli)
            break;
    }
}