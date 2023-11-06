#ifndef ENEMY_LIB
#define ENEMY_LIB

#include "config.h"

#define ENEMY_W 12
#define ENEMY_H 8

#define ENEMY_LINES 5
#define ENEMY_COLUNS 11

#define ENEMY_SPEED BUFFER_W/80

typedef enum enemy_type
{
    STRONG_ENEMY = 0,
    MEDIUM_ENEMY,
    WEAK_ENEMY,
} enemy_type_t;

typedef struct enemy
{
    enemy_type_t type;
    int x, y, dx;
    int alive;
    int frame;
    int score;
} enemy_t;

void enemies_init(enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS]);

int enemies_update(enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS]);

#endif