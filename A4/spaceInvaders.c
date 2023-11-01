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

void must_init(bool test, const char *description)
{
    if(test) 
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void ship_draw(ship_t *ship)
{
    al_draw_filled_rectangle(ship->x - SHIP_W/2, ship->y - SHIP_H/2, ship->x + SHIP_W/2, ship->y + SHIP_H/2, al_map_rgb(255,255,255));
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

void enemies_draw(enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS])
{   
    for(int i = 0; i < ENEMY_LINES; i++)
    {
        for(int j = 0; j < ENEMY_COLUNS; j++)
        {
            if(enemy[i][j].type == WEAK_ENEMY)
                al_draw_filled_rectangle(enemy[i][j].x - ENEMY_W/2, enemy[i][j].y - ENEMY_H/2, enemy[i][j].x + ENEMY_W/2, enemy[i][j].y + ENEMY_H/2, al_map_rgb(255,0,0));
            else if(enemy[i][j].type == MEDIUM_ENEMY)
                al_draw_filled_rectangle(enemy[i][j].x - ENEMY_W/2, enemy[i][j].y - ENEMY_H/2, enemy[i][j].x + ENEMY_W/2, enemy[i][j].y + ENEMY_H/2, al_map_rgb(0,255,0));
            else if(enemy[i][j].type == STRONG_ENEMY)
                al_draw_filled_rectangle(enemy[i][j].x - ENEMY_W/2, enemy[i][j].y - ENEMY_H/2, enemy[i][j].x + ENEMY_W/2, enemy[i][j].y + ENEMY_H/2, al_map_rgb(0,0,255));
        }
    }
}

void obstacle_draw(obstacle_t *obstacle)
{
    for(int i = 0; i < OBSTACLE_N; i++)
    {
        al_draw_filled_rectangle(obstacle[i].x - OBSTACLE_W/2, obstacle[i].y - OBSTACLE_H/2, obstacle[i].x - OBSTACLE_W/5, obstacle[i].y + OBSTACLE_H/2, al_map_rgb(255,255,255));
        al_draw_filled_rectangle(obstacle[i].x + OBSTACLE_W/2, obstacle[i].y - OBSTACLE_H/2, obstacle[i].x + OBSTACLE_W/5, obstacle[i].y + OBSTACLE_H/2, al_map_rgb(255,255,255));
        al_draw_filled_rectangle(obstacle[i].x - OBSTACLE_W/5, obstacle[i].y - OBSTACLE_H/2, obstacle[i].x + OBSTACLE_W/5, obstacle[i].y, al_map_rgb(255,255,255));
    }
}

void shot_draw(shot_t *shot)
{
    al_draw_filled_rectangle(shot->x - SHOT_W/2, shot->y - SHOT_H/2, shot->x + SHOT_W/2, shot->y + SHOT_H/2, al_map_rgb(255,255,255));
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

    shot_t ship_shot;
    shot_init(&ship_shot);

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE key;
    bool done = false;
    bool redraw = true;
    int cont = 0;

    al_start_timer(timer);

    while(1)
    {
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
                if(al_key_down(&key, ALLEGRO_KEY_SPACE))
                    shot_fire(&ship_shot, ship.x, ship.y);

                cont++;

                stars_update(stars);
                if(cont % 45 == 0)
                    enemies_update(enemy);
                ship_update(&ship);
                obstacle_update(obstacle);
                shot_update(&ship_shot);

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
            shot_draw(&ship_shot);
            ship_draw(&ship);
            enemies_draw(enemy);
            obstacle_draw(obstacle);

            al_set_target_backbuffer(disp);
            al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);
            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}