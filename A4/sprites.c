#include "sprites.h"
#include "stdio.h"
#include <allegro5/allegro_image.h>


ALLEGRO_BITMAP *sprite_get(ALLEGRO_BITMAP *sprites, int x, int y, int w, int h)
{
    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sprites, x, y, w, h);
    if(!sprite)
    {
        fprintf(stderr, "Error creating sprite\n");
        exit(1);
    }
    
    return sprite;
}

void sprites_init(sprites_t *sprites)
{
    sprites->sheet = al_load_bitmap("spritesheet.png");
    printf("spritesheet: %p\n", (void *)sprites->sheet);
    printf("spritesheet: %p\n", (void *)sprites->sheet);
    printf("spritesheet: %p\n", (void *)sprites->sheet);
    if(!sprites->sheet)
    {
        fprintf(stderr, "Error loading spritesheet\n");
        exit(1);
    }

    sprites->ship = sprite_get(sprites->sheet, 200, 12, 15, 7);
    // sprites->life = sprite_get(sprites->sheet, 32, 0, 32, 32);

    // sprites->waek_enemy[0] = sprite_get(sprites->sheet, 0, 32, 32, 32);
    // sprites->waek_enemy[1] = sprite_get(sprites->sheet, 32, 32, 32, 32);

    // sprites->medium_enemy[0] = sprite_get(sprites->sheet, 0, 64, 32, 32);
    // sprites->medium_enemy[1] = sprite_get(sprites->sheet, 32, 64, 32, 32);

    // sprites->strong_enemy[0] = sprite_get(sprites->sheet, 0, 96, 32, 32);
    // sprites->strong_enemy[1] = sprite_get(sprites->sheet, 32, 96, 32, 32);

    // sprites->mother_ship = sprite_get(sprites->sheet, 0, 128, 32, 32);

    // sprites->waek_enemy_shot[0] = sprite_get(sprites->sheet, 0, 160, 32, 32);
    // sprites->waek_enemy_shot[1] = sprite_get(sprites->sheet, 32, 160, 32, 32);
    // sprites->waek_enemy_shot[2] = sprite_get(sprites->sheet, 64, 160, 32, 32);

    // sprites->medium_enemy_shot[0] = sprite_get(sprites->sheet, 0, 192, 32, 32);
    // sprites->medium_enemy_shot[1] = sprite_get(sprites->sheet, 32, 192, 32, 32);

    // sprites->strong_enemy_shot[0] = sprite_get(sprites->sheet, 0, 224, 32, 32);
    // sprites->strong_enemy_shot[1] = sprite_get(sprites->sheet, 32, 224, 32, 32);
    // sprites->strong_enemy_shot[2] = sprite_get(sprites->sheet, 64, 224, 32, 32);
    // sprites->strong_enemy_shot[3] = sprite_get(sprites->sheet, 96, 224, 32, 32);

    // sprites->obstacle[0] = sprite_get(sprites->sheet, 0, 256, 32, 32);
    // sprites->obstacle[1] = sprite_get(sprites->sheet, 32, 256, 32, 32);
    // sprites->obstacle[2] = sprite_get(sprites->sheet, 64, 256, 32, 32);
    // sprites->obstacle[3] = sprite_get(sprites->sheet, 96, 256, 32, 32);
    // sprites->obstacle[4] = sprite_get(sprites->sheet, 128, 256, 32, 32);

    // sprites->enemy_explosion[0] = sprite_get(sprites->sheet, 0, 288, 32, 32);
    // sprites->enemy_explosion[1] = sprite_get(sprites->sheet, 32, 288, 32, 32);

    // sprites->ship_explosion[0] = sprite_get(sprites->sheet, 0, 320, 32, 32);
    // sprites->ship_explosion[1] = sprite_get(sprites->sheet, 32, 320, 32, 32);

    // sprites->powerup[0] = sprite_get(sprites->sheet, 0, 352, 32, 32);
    // sprites->powerup[1] = sprite_get(sprites->sheet, 32, 352, 32, 32);

}

void sprites_deinit(sprites_t *sprites)
{
    al_destroy_bitmap(sprites->sheet);

    al_destroy_bitmap(sprites->ship);
    // al_destroy_bitmap(sprites->life);

    // al_destroy_bitmap(sprites->waek_enemy[0]);
    // al_destroy_bitmap(sprites->waek_enemy[1]);
    // al_destroy_bitmap(sprites->medium_enemy[0]);
    // al_destroy_bitmap(sprites->medium_enemy[1]);
    // al_destroy_bitmap(sprites->strong_enemy[0]);
    // al_destroy_bitmap(sprites->strong_enemy[1]);
    // al_destroy_bitmap(sprites->mother_ship);

    // al_destroy_bitmap(sprites->waek_enemy_shot[0]);
    // al_destroy_bitmap(sprites->waek_enemy_shot[1]);
    // al_destroy_bitmap(sprites->waek_enemy_shot[2]);
    // al_destroy_bitmap(sprites->medium_enemy_shot[0]);
    // al_destroy_bitmap(sprites->medium_enemy_shot[1]);
    // al_destroy_bitmap(sprites->strong_enemy_shot[0]);
    // al_destroy_bitmap(sprites->strong_enemy_shot[1]);
    // al_destroy_bitmap(sprites->strong_enemy_shot[2]);
    // al_destroy_bitmap(sprites->strong_enemy_shot[3]);

    // al_destroy_bitmap(sprites->obstacle[0]);
    // al_destroy_bitmap(sprites->obstacle[1]);
    // al_destroy_bitmap(sprites->obstacle[2]);
    // al_destroy_bitmap(sprites->obstacle[3]);
    // al_destroy_bitmap(sprites->obstacle[4]);
    
    // al_destroy_bitmap(sprites->enemy_explosion[0]);
    // al_destroy_bitmap(sprites->enemy_explosion[1]);
    // al_destroy_bitmap(sprites->ship_explosion[0]);
    // al_destroy_bitmap(sprites->ship_explosion[1]);
    // al_destroy_bitmap(sprites->powerup[0]);
    // al_destroy_bitmap(sprites->powerup[1]);
}
