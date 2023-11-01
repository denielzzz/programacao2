#include "config.h"

#define SHOT_W 2
#define SHOT_H 5
#define SHOT_SPEED 4

typedef struct shot
{
    int x, y, dy;
    int alive;
} shot_t;

void shot_init(shot_t *shot);

void shot_fire(shot_t *shot, int x, int y);

void shot_update(shot_t *shot);