#include "config.h"

#define ENEMY_W BUFFER_W/21
#define ENEMY_H BUFFER_H/24

#define ENEMY_LINES 5
#define ENEMY_COLUNS 11

#define ENEMY_SPEED BUFFER_W/32

typedef enum enemy_type
{
    WEAK_ENEMY = 0,
    MEDIUM_ENEMY,
    STRONG_ENEMY,
} enemy_type_t;

typedef struct enemy
{
    enemy_type_t type;
    int x, y, dx;
    int alive;
} enemy_t;

void enemies_init(enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS]);

void enemies_update(enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS]);