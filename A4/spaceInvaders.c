#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "config.h"
#include "ship.h"
#include "map.h"
#include "enemy.h"
#include "obstacle.h"
#include "shot.h"
#include "sprites.h"

void must_init(bool test, const char *description)
{
    if(test) 
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void ship_draw(ship_t *ship, sprites_t *sprites)
{
    al_draw_scaled_bitmap(sprites->ship, 0, 0, 15, 9, ship->x - SHIP_W/2, ship->y - SHIP_H/2, SHIP_W, SHIP_H, 0);
}

void stars_draw(STAR* stars)
{
    float star_x = 1.5;
    for(int i = 0; i < STARS_N; i++)
    {
        float l = stars[i].speed * 0.8;
        al_draw_pixel(star_x, stars[i].y, al_map_rgb_f(l,l,l));
        star_x += 2;
    }
}

void enemies_draw(enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS], sprites_t *sprites)
{   
    for(int i = 0; i < ENEMY_LINES; i++)
    {
        for(int j = 0; j < ENEMY_COLUNS; j++)
        {
            if(!enemy[i][j].alive)
                continue;

            if(enemy[i][j].type == STRONG_ENEMY)
                al_draw_scaled_bitmap(sprites->strong_enemy[enemy[i][j].frame], 0, 0, 8, 8, enemy[i][j].x - ENEMY_W*3/7, enemy[i][j].y - ENEMY_H/2, 9, ENEMY_H, 0);
            else if(enemy[i][j].type == MEDIUM_ENEMY)
                al_draw_bitmap(sprites->medium_enemy[enemy[i][j].frame], enemy[i][j].x - ENEMY_W/2, enemy[i][j].y - ENEMY_H/2, 0);
            else if(enemy[i][j].type == WEAK_ENEMY)
                al_draw_bitmap(sprites->weak_enemy[enemy[i][j].frame], enemy[i][j].x - ENEMY_W/2, enemy[i][j].y - ENEMY_H/2, 0);
        }
    }
}

void obstacle_draw(obstacle_t *obstacle, sprites_t *sprites)
{
    for(int i = 0; i < OBSTACLE_N; i++)
    {
        if(obstacle[i].life == 10 || obstacle[i].life == 9)
            al_draw_scaled_bitmap(sprites->obstacle[0], 0, 0, 23, 17, obstacle[i].x - OBSTACLE_W/2, obstacle[i].y - OBSTACLE_H/2, OBSTACLE_W, OBSTACLE_H, 0);
        else if(obstacle[i].life == 8 || obstacle[i].life == 7)
            al_draw_scaled_bitmap(sprites->obstacle[1], 0, 0, 23, 17, obstacle[i].x - OBSTACLE_W/2, obstacle[i].y - OBSTACLE_H/2, OBSTACLE_W, OBSTACLE_H, 0);
        else if(obstacle[i].life == 6 || obstacle[i].life == 5)
            al_draw_scaled_bitmap(sprites->obstacle[2], 0, 0, 23, 17, obstacle[i].x - OBSTACLE_W/2, obstacle[i].y - OBSTACLE_H/2, OBSTACLE_W, OBSTACLE_H, 0);
        else if(obstacle[i].life == 4 || obstacle[i].life == 3)
            al_draw_scaled_bitmap(sprites->obstacle[3], 0, 0, 23, 17, obstacle[i].x - OBSTACLE_W/2, obstacle[i].y - OBSTACLE_H/2, OBSTACLE_W, OBSTACLE_H, 0);
        else if(obstacle[i].life == 2 || obstacle[i].life == 1)
            al_draw_scaled_bitmap(sprites->obstacle[4], 0, 0, 23, 17, obstacle[i].x - OBSTACLE_W/2, obstacle[i].y - OBSTACLE_H/2, OBSTACLE_W, OBSTACLE_H, 0);

    }
}

void shot_draw(shot_t *shot, sprites_t *sprites)
{
    for(int i = 0; i < 2; i++)
    {
        if(!shot[i].alive)
            continue;
        
        if(shot[i].frames == SHIP_SHOT)
            al_draw_filled_rectangle(shot[i].x - SHOT_W/2, shot[i].y - SHOT_H/2, shot[i].x + SHOT_W/2, shot[i].y + SHOT_H/2, al_map_rgb(255,255,255));
        else if(shot[i].frames == MEDIUM_SHOT)
            al_draw_bitmap(sprites->medium_enemy_shot[shot[i].frame/5], shot[i].x - SHOT_W/2, shot[i].y - SHOT_H/2, 0);
        else if(shot[i].frames == WEAK_SHOT)
            al_draw_bitmap(sprites->weak_enemy_shot[shot[i].frame/5], shot[i].x - SHOT_W/2, shot[i].y - SHOT_H/2, 0);
        else if(shot[i].frames == STRONG_SHOT)
            al_draw_bitmap(sprites->strong_enemy_shot[shot[i].frame/5], shot[i].x - SHOT_W/2, shot[i].y - SHOT_H/2, 0);
    }
}

int main()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    ALLEGRO_BITMAP* buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "buffer");
    
    ALLEGRO_DISPLAY* disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ship_t ship;
    ship_init(&ship);

    STAR stars[STARS_N];
    stars_init(stars);

    enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS];
    enemies_init(enemy);

    obstacle_t obstacle[OBSTACLE_N];
    obstacle_init(obstacle);

    shot_t ship_shot[2];
    ship_shot_init(ship_shot);

    shot_t enemy_shot[2];
    enemy_shot_init(enemy_shot);

    sprites_t sprites;
    sprites_init(&sprites);

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE key;
    bool done = false;
    bool redraw = true;
    int cont = 0;

    al_start_timer(timer);

    while(1)
    {
        cont++;
        al_wait_for_event(queue, &event);

        switch(event.type)
        {

            case ALLEGRO_EVENT_TIMER:
                al_get_keyboard_state(&key);
                
                if(al_key_down(&key, ALLEGRO_KEY_ESCAPE))
                    done = true;
                if(al_key_down(&key, ALLEGRO_KEY_LEFT))
                    ship.dx = -SHIP_SPEED;
                else if(al_key_down(&key, ALLEGRO_KEY_RIGHT))
                    ship.dx = SHIP_SPEED;
                else
                    ship.dx = 0;
                if(al_key_down(&key, ALLEGRO_KEY_SPACE) && !ship.shot_cooldown && !ship.shot_timer)
                    ship_shot_fire(ship_shot, &ship, SHOT_N-1);
                else if(al_key_down(&key, ALLEGRO_KEY_SPACE) && !ship.shot_cooldown && ship.shot_timer)
                    ship_shot_fire(ship_shot, &ship, SHOT_N);

                if(cont % ((rand() % 2*FPS) + 10) == 0)
                {
                    while(1)
                    {
                        int x = rand() % ENEMY_LINES;
                        int y = rand() % ENEMY_COLUNS;
                        if(!enemy[x][y].alive)
                            continue;
                        enemy_shot_fire(enemy_shot, enemy, x, y);
                        break;
                    }
                }


                stars_update(stars);
                if(cont % 30 == 0)
                    enemies_update(enemy);
                ship_update(&ship);
                obstacle_update(obstacle);
                shot_update(ship_shot);
                shot_update(enemy_shot);

                redraw = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(buffer);
            al_clear_to_color(al_map_rgb(10,10,10));

            stars_draw(stars);
            shot_draw(ship_shot, &sprites);
            shot_draw(enemy_shot, &sprites);
            ship_draw(&ship, &sprites);
            enemies_draw(enemy, &sprites);
            obstacle_draw(obstacle, &sprites);

            al_set_target_backbuffer(disp);
            al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);
            al_flip_display();
            redraw = false;
        }
    }
    sprites_deinit(&sprites);
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}