#include "config.h"
#define STARS_N ((BUFFER_W / 2) - 1)

typedef struct STAR
{
    float y;
    float speed;
} STAR;

void stars_init(STAR* stars);

void stars_update(STAR* stars);