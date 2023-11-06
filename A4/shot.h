#include "config.h"
#include "ship.h"
#include "enemy.h"
#include "obstacle.h"

#define SHOT_W 2
#define SHOT_H 5
#define SHIP_SHOT_SPEED 4
#define ENEMY_SHOT_SPEED 1
#define SHOT_N 2

typedef enum shot_frame_type
{
    SHIP_SHOT = 1,
    MEDIUM_SHOT = 2,
    WEAK_SHOT = 3,
    STRONG_SHOT = 4,
} shot_frame_type_t;
typedef struct shot
{
    int x, y, dy;
    int alive;
    int damage;
    shot_frame_type_t frames;
    int frame;
} shot_t;

void ship_shot_init(shot_t *shot);

void enemy_shot_init(shot_t *shot);

void ship_shot_fire(shot_t *shot, ship_t *ship, int shots);

void enemy_shot_fire(shot_t *shot, enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS], int x, int y);

void shot_update(shot_t *shot);

void collide_update(shot_t *shot, enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS], ship_t *ship, obstacle_t *obstacle);

void shots_collide(shot_t *shot, shot_t *shot2);