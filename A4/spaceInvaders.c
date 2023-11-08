#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

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

void ship_draw(ship_t *ship, sprites_t *sprites, int pause)
{
    if(ship->lives == 0 && ship->respawn_timer > 0)
    {
        if(ship->frame/5 == 2)
            ship->frame = 0;
        al_draw_bitmap(sprites->ship_explosion[ship->frame/5], ship->x - SHIP_W/2, ship->y - SHIP_H/2, 0);
        // Para a animação da explosão quando o jogo pausa
        if(!pause)
            ship->frame++;
        return;
    }
    if(ship->lives == 0)
        return;

    if(ship->invincible_timer/2%3 == 1 && ship->respawn_timer)
        return;
    
    al_draw_bitmap(sprites->ship, ship->x - SHIP_W/2, ship->y - SHIP_H/2, 0);
    if(ship->invincible_timer)
        al_draw_circle(ship->x+0.5, ship->y+2, SHIP_W/3*2, al_map_rgb(65,122,255), 1);
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
            if(!enemy[i][j].alive && enemy[i][j].frame > 7)
                continue;

            if(!enemy[i][j].alive)
            {
                al_draw_bitmap(sprites->enemy_explosion[enemy[i][j].frame/4], enemy[i][j].x - ENEMY_W/2, enemy[i][j].y - ENEMY_H/2, 0);
                enemy[i][j].frame++;
                continue;
            }

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
        if(!shot[i].alive && shot[i].dead_frame > 5)
            continue;

        if(!shot[i].alive)
        {
            al_draw_bitmap(sprites->shot_explosion, shot[i].x - SHOT_W/2, shot[i].y - SHOT_H/2, 0);
            shot[i].dead_frame++;
            continue;
        }
        
        if(shot[i].frames == SHIP_SHOT)
            al_draw_filled_rectangle(shot[i].x - SHOT_W/2 + 1, shot[i].y - SHOT_H/2, shot[i].x + SHOT_W/2, shot[i].y + SHOT_H/2, al_map_rgb(255,255,255));
        else if(shot[i].frames == MEDIUM_SHOT)
            al_draw_bitmap(sprites->medium_enemy_shot[shot[i].frame/5], shot[i].x - SHOT_W/2, shot[i].y - SHOT_H/2, 0);
        else if(shot[i].frames == WEAK_SHOT)
            al_draw_bitmap(sprites->weak_enemy_shot[shot[i].frame/5], shot[i].x - SHOT_W/2, shot[i].y - SHOT_H/2, 0);
        else if(shot[i].frames == STRONG_SHOT)
            al_draw_bitmap(sprites->strong_enemy_shot[shot[i].frame/5], shot[i].x - SHOT_W/2, shot[i].y - SHOT_H/2, 0);
    }
}

void draw_game_over(ship_t *ship, ALLEGRO_FONT *big_font, ALLEGRO_FONT *medium_font, ALLEGRO_FONT *small_font, unsigned long long int cont)
{
    al_draw_filled_rectangle(0, 0, BUFFER_W, BUFFER_H, al_map_rgba(1,1,1,80));
    al_draw_text(big_font, al_map_rgb(255,255,255), BUFFER_W/2, BUFFER_H/5, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_draw_textf(medium_font, al_map_rgb(255,255,255), BUFFER_W/2, BUFFER_H/2 + 20, ALLEGRO_ALIGN_CENTER, "SCORE: %d", ship->score);
    if(cont % 90 < 45)
    {
        al_draw_text(small_font, al_map_rgb(255,255,255), BUFFER_W/2, BUFFER_H/2 + 60, ALLEGRO_ALIGN_CENTER, "PRESS ESC TO EXIT OR");
        al_draw_text(small_font, al_map_rgb(255,255,255), BUFFER_W/2, BUFFER_H/2 + 80, ALLEGRO_ALIGN_CENTER, "SPACE TO PLAY AGAIN");
    }
}

void hud_draw(int score, int lives, sprites_t *sprites, ALLEGRO_FONT *small_font)
{
    al_draw_textf(small_font, al_map_rgb(255,255,255), 10, 10, ALLEGRO_ALIGN_LEFT, "SCORE: %d", score);
    al_draw_textf(small_font, al_map_rgb(255,255,255), BUFFER_W*3/5 + 25, 10, ALLEGRO_ALIGN_LEFT, "LIVES: %dx", lives);
    al_draw_bitmap(sprites->ship, BUFFER_W*5/6 + 25, 9, 0);
}

void mothership_draw(enemy_t *mothership, sprites_t *sprites)
{
    if(!mothership->alive && mothership->frame > 7)
        return;
    if(!mothership->alive)
    {
        al_draw_bitmap(sprites->enemy_explosion[mothership->frame/4], mothership->x - ENEMY_W/2, mothership->y - ENEMY_H/2, 0);
        mothership->frame++;
        return;
    }
    al_draw_bitmap(sprites->mother_ship, mothership->x - ENEMY_W/2, mothership->y - ENEMY_H/2, 0);
}

void powerup_draw(powerup_t *powerup, sprites_t *sprites)
{
    if(!powerup->alive)
        return;
    if(powerup->type == 0)
        al_draw_bitmap(sprites->powerup[0], powerup->x - 4, powerup->y - 4, 0);
    else if(powerup->type == 1)
        al_draw_bitmap(sprites->powerup[1], powerup->x - 4, powerup->y - 4, 0);
}

void pause_draw(ALLEGRO_FONT *big_font, ALLEGRO_FONT *small_font, long long int cont)
{
    al_draw_filled_rectangle(0, 0, BUFFER_W, BUFFER_H, al_map_rgba(1,1,1,80));
    al_draw_text(big_font, al_map_rgb(255,255,255), BUFFER_W/2, BUFFER_H/5, ALLEGRO_ALIGN_CENTER, "PAUSE");
    if(cont % 90 < 45)
        al_draw_text(small_font, al_map_rgb(255,255,255), BUFFER_W/2, BUFFER_H/2 + 20, ALLEGRO_ALIGN_CENTER, "PRESS P TO CONTINUE");
}

void menu_draw(ALLEGRO_FONT *medium_font, ALLEGRO_FONT *small_font, long long int cont, sprites_t *sprites)
{
    al_draw_filled_rectangle(0, 0, BUFFER_W, BUFFER_H, al_map_rgba(1,1,1,80));
    al_draw_text(medium_font, al_map_rgb(255,255,255), BUFFER_W/2, BUFFER_H/5, ALLEGRO_ALIGN_CENTER, "SPACE INVADERS");

    al_draw_bitmap(sprites->weak_enemy[0], 15 + BUFFER_W/3 - ENEMY_W/2, BUFFER_H/3 - ENEMY_H/2 + 10, 0);
    al_draw_text(small_font, al_map_rgb(255,255,255), 15 + BUFFER_W/2, BUFFER_H/3 - ENEMY_H/2 + 10, ALLEGRO_ALIGN_CENTER, "= 10 PTS");

    al_draw_bitmap(sprites->medium_enemy[0], 16 + BUFFER_W/3 - ENEMY_W/2, BUFFER_H/3 - ENEMY_H/2 + 33, 0);
    al_draw_text(small_font, al_map_rgb(255,255,255), 15 + BUFFER_W/2, BUFFER_H/3 - ENEMY_H/2 + 33, ALLEGRO_ALIGN_CENTER, "= 20 PTS");

    al_draw_bitmap(sprites->strong_enemy[1], 18 + BUFFER_W/3 - ENEMY_W/2, BUFFER_H/3 - ENEMY_H/2 + 56, 0);
    al_draw_text(small_font, al_map_rgb(255,255,255), 15 + BUFFER_W/2, BUFFER_H/3 - ENEMY_H/2 + 56, ALLEGRO_ALIGN_CENTER, "= 40 PTS");

    al_draw_bitmap(sprites->mother_ship, 14 + BUFFER_W/3 - ENEMY_W/2, BUFFER_H/3 - ENEMY_H/2 + 80, 0);
    al_draw_text(small_font, al_map_rgb(255,255,255), 15 + BUFFER_W/2, BUFFER_H/3 - ENEMY_H/2 + 80, ALLEGRO_ALIGN_CENTER, " = ??? PTS");
    if(cont % 90 < 45)
    {
        al_draw_text(small_font, al_map_rgb(255,255,255), BUFFER_W/2, BUFFER_H*4/5, ALLEGRO_ALIGN_CENTER, "PRESS SPACE TO START");
        al_draw_text(small_font, al_map_rgb(255,255,255), BUFFER_W/2, BUFFER_H*4/5 + 20, ALLEGRO_ALIGN_CENTER, "PRESS ESC TO EXIT");
    }
}

void reset(ship_t *ship, STAR stars[STARS_N], enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS], enemy_t *mothership, obstacle_t obstacle[OBSTACLE_N], shot_t ship_shot[2], shot_t enemy_shot[2], powerup_t *powerup, int *dificulty)
{
    ship_init(ship);
    stars_init(stars);
    enemies_init(enemy);
    mothership->alive = 0;
    obstacle_init(obstacle);
    ship_shot_init(ship_shot);
    enemy_shot_init(enemy_shot);
    powerup->alive = 0;
    *dificulty = 0;
}

int main()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_BITMAP* buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "buffer");
    
    ALLEGRO_DISPLAY* disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    must_init(al_init_font_addon(), "image");
    must_init(al_init_ttf_addon(), "ttf");;

    ALLEGRO_FONT* big_font = al_load_ttf_font("./fonts/ARCADE_N.TTF", 30, 0);
    ALLEGRO_FONT* medium_font = al_load_ttf_font("./fonts/ARCADE_N.TTF", 16, 0);
    ALLEGRO_FONT* small_font = al_load_ttf_font("./fonts/ARCADE_N.TTF", 8, 0);
    must_init(big_font, "font");
    must_init(medium_font, "font");
    must_init(small_font, "font");

    must_init(al_init_primitives_addon(), "primitives");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ship_t ship;

    STAR stars[STARS_N];
    stars_init(stars);

    enemy_t enemy[ENEMY_LINES][ENEMY_COLUNS];
    enemy_t mothership;

    obstacle_t obstacle[OBSTACLE_N];

    shot_t ship_shot[2];

    shot_t enemy_shot[2];

    powerup_t powerup;

    sprites_t sprites;
    sprites_init(&sprites);

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE key;
    bool done = false;
    bool redraw = true;
    int game_over = 0;
    int dificulty = 0;
    int pause = 0;
    int pause_timer = 0;
    int menu = 1;
    unsigned long long int cont = 0;

    al_start_timer(timer);

    while(1)
    {
        cont++;
        al_wait_for_event(queue, &event);

        switch(event.type)
        {

            case ALLEGRO_EVENT_TIMER:
                al_get_keyboard_state(&key);
                
                if(al_key_down(&key, ALLEGRO_KEY_SPACE) && game_over)
                {
                    reset(&ship, stars, enemy, &mothership, obstacle, ship_shot, enemy_shot, &powerup, &dificulty);
                    game_over = 0;
                }
                if(al_key_down(&key, ALLEGRO_KEY_ESCAPE))
                    done = true;
                if(al_key_down(&key, ALLEGRO_KEY_SPACE) && menu)
                {
                    menu = 0;
                    reset(&ship, stars, enemy, &mothership, obstacle, ship_shot, enemy_shot, &powerup, &dificulty);
                }
                if(al_key_down(&key, ALLEGRO_KEY_P) && !pause_timer && !game_over && !menu)
                {
                    pause = !pause;
                    pause_timer = 10;
                }
                if(menu)
                {
                    stars_update(stars);
                    redraw = true;
                    break;
                }
                if(!pause)
                {
                    if(ship.lives > 0)
                    {
                        if(al_key_down(&key, ALLEGRO_KEY_LEFT))
                            ship.dx = -SHIP_SPEED;
                        else if(al_key_down(&key, ALLEGRO_KEY_RIGHT))
                            ship.dx = SHIP_SPEED;
                        else
                            ship.dx = 0;
                        
                        if(al_key_down(&key, ALLEGRO_KEY_SPACE) && !ship.shot_cooldown && !ship.double_shot_timer)
                            ship_shot_fire(ship_shot, &ship, SHOT_N-1);
                        else if(al_key_down(&key, ALLEGRO_KEY_SPACE) && !ship.shot_cooldown && ship.double_shot_timer)
                            ship_shot_fire(ship_shot, &ship, SHOT_N);

                        if(cont % ((rand() % 2*FPS) + 10) == 0)
                        {
                            while(1)
                            {
                                int x = rand() % ENEMY_LINES;
                                int y = rand() % ENEMY_COLUNS;
                                if(!enemy[x][y].alive)
                                    continue;
                                enemy_shot_fire(enemy_shot, enemy, x, y, dificulty);
                                break;
                            }
                        }
                    }
                    if(ship.lives > 0 || ship.respawn_timer)
                    {
                        if(ship.lives == 0 && ship.respawn_timer)
                            ship.dx = 0;
                        stars_update(stars);
                        ship_update(&ship);
                        if(cont % (30 - 3*dificulty) == 0)
                            if(enemies_update(enemy))
                                ship.lives = 0;
                        if(rand() % 1000 == 0)
                            mothership_init(&mothership);
                        if(cont%2 || cont%3)
                            mothership_update(&mothership);
                        if(rand() % 1000 == 0)
                            powerup_init(&powerup);
                        if(cont%2 || cont%3)
                            powerup_update(&powerup);
                        shot_update(ship_shot);
                        shot_update(enemy_shot);
                        collide_update(enemy_shot, enemy, &mothership, &ship, obstacle);
                        collide_update(ship_shot, enemy, &mothership, &ship, obstacle);
                        powerup_collide(&powerup, &ship);
                        if(reset_verify(enemy))
                        {
                            enemies_init(enemy);
                            if(dificulty < 6)
                                dificulty++;
                            if(ship.lives < 5)
                                ship.lives++;
                        }
                        shots_collide(ship_shot, enemy_shot);
                        obstacle_update(obstacle);
                    }
                    else
                        game_over = 1;

                }
                if(pause_timer > 0)
                    pause_timer--;
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

            if(menu)
            {
                stars_draw(stars);
                menu_draw(medium_font, small_font, cont, &sprites);
            }
            else
            {
                stars_draw(stars);
                powerup_draw(&powerup, &sprites);
                ship_draw(&ship, &sprites, pause);
                enemies_draw(enemy, &sprites);
                mothership_draw(&mothership, &sprites);
                obstacle_draw(obstacle, &sprites);
                shot_draw(enemy_shot, &sprites);
                shot_draw(ship_shot, &sprites);
                hud_draw(ship.score, ship.lives, &sprites, small_font);
                if(pause)
                    pause_draw(big_font, small_font, cont);
                if(game_over)
                    draw_game_over(&ship, big_font, medium_font, small_font, cont);
            }

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
    al_destroy_font(big_font);
    al_destroy_font(medium_font);
    al_destroy_font(small_font);

    return 0;
}