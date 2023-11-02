#include "shot.h"

void ship_shot_init(shot_t *shot)
{
    for(int i = 0; i < SHOT_N; i++)
    {
        shot[i].dy = -SHIP_SHOT_SPEED;
        shot[i].alive = 0;
        shot[i].frame = 0;
        shot[i].damage = 1;
    }
}

void enemy_shot_init(shot_t *shot)
{
    for(int i = 0; i < SHOT_N; i++)
    {
        shot[i].dy = ENEMY_SHOT_SPEED;
        shot[i].alive = 0;
        shot[i].frame = 0;
    }
}

void ship_shot_fire(shot_t *shot, ship_t *ship, int shots)
{
    if(ship->respawn_timer)
        return;

    for(int i = 0; i < shots; i++)
    {
        if(!shot[i].alive)
        {
            shot[i].x = ship->x;
            shot[i].y = ship->y;
            shot[i].alive = 1;
            shot[i].frame = 0;
            shot[i].frames = SHIP_SHOT;
            ship->shot_cooldown = 10;
            break;
        }
    }
}

void enemy_shot_fire(shot_t *shot, enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS], int x, int y)
{
    if(enemy[x][y].type != STRONG_ENEMY)
    {
        for(int i = x; i < ENEMY_LINES-1; i++)
            if(enemy[i][y].alive)        
                return;
    }

    for(int i = 0; i < SHOT_N; i++)
    {
        if(!shot[i].alive)
        {
            shot[i].x = enemy[x][y].x;
            shot[i].y = enemy[x][y].y;
            shot[i].alive = 1;
            shot[i].frame = 0;
            if(enemy[x][y].type == WEAK_ENEMY)
            {
                shot[i].frames = WEAK_SHOT;
                shot[i].damage = 1;
            }
            else if(enemy[x][y].type == MEDIUM_ENEMY)
            {
                shot[i].frames = MEDIUM_SHOT;
                shot[i].damage = 2;
            }
            else if(enemy[x][y].type == STRONG_ENEMY)
            {
                shot[i].frames = STRONG_SHOT;
                shot[i].damage = 2;
            }
            break;
        }
    }
}

void shot_update(shot_t *shot)
{
    for(int i = 0; i < SHOT_N; i++)
    {
        if(shot[i].alive)
        {
            shot[i].y += shot[i].dy;

            if(shot[i].frame < (int)shot[i].frames*5-1)
                shot[i].frame++;
            else
                shot[i].frame = 0;

            if(shot[i].y <= -5 || shot[i].y >= BUFFER_H + 5)
            {
                shot[i].alive = 0;
            }
        }
    }
}