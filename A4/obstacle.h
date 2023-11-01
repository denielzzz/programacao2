#include "config.h"

#define OBSTACLE_W 32
#define OBSTACLE_H 16
#define OBSTACLE_LIFE 10
#define OBSTACLE_N 4


typedef struct obstacle
{
    int x, y;
    int life;
} obstacle_t;

void obstacle_init(obstacle_t *obstacle);

void obstacle_update(obstacle_t *obstacle);