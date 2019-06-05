#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "setup.h"


extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *background;
extern Image spaceship;
extern Image astronaut_1[12];
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER *timer;


void calcBounds(Image &a) {
    a.bbLeft = a.x;
	a.bbTop  = a.y;
	a.bbRight = a.bbLeft + al_get_bitmap_width(a.bitmap);
	a.bbBottom = a.bbTop + al_get_bitmap_height(a.bitmap);

}

void draw_background(){
    al_draw_scaled_bitmap(background,0,0,1300,1300,0,0,1380,1000,0);
}

void draw_image(Image &a){
    al_draw_bitmap(a.bitmap, a.x, a.y, 0);
}

void draw_astronaut(Image astronaut[], int frame, int direction){
    frame += direction*3;
    al_draw_bitmap(astronaut[frame].bitmap,astronaut[frame].x,astronaut[frame].y,0);
}

void draw_start_button(){
    al_draw_rectangle(620, 450, 800, 500, WHITE, 2);
}


bool check_in_bounds(Image astronaut[]){

        int dx = 0;
        int dy = 0;

        if (astronaut[0].x <= 0){
            dx = 1;
        }
        else if (astronaut[0].x >= 1322){
            dx = -1;
        }
        else if (astronaut[0].y <= 0){
            dy = 1;
        }
        else if (astronaut[0].y >= 631){
            dy = -1;
        }
        else{
            return true;
        }

        for(int i = 0; i < 12; i++){
            astronaut[i].x += dx;
            astronaut[i].y += dy;
        }

        return false;
}

bool isCollision(Image a, Image b) {
    if (a.bbBottom < b.bbTop) {
        return false;
    }
    else if (a.bbTop > b.bbBottom) {
        return false;
    }
    else if (a.bbRight < b.bbLeft) {
        return false;
    }
    else if (a.bbLeft > b.bbRight) {
        return false;
    }
    return true;
}

void drawBoundingBox(Image image) {
    calcBounds(image);
	al_draw_line(image.bbLeft, image.bbTop, image.bbRight, image.bbTop, WHITE, 1);
    al_draw_line(image.bbLeft, image.bbBottom, image.bbRight, image.bbBottom, WHITE, 1);
	al_draw_line(image.bbLeft, image.bbTop, image.bbLeft, image.bbBottom, WHITE, 1);
	al_draw_line(image.bbRight, image.bbTop, image.bbRight, image.bbBottom, WHITE,1);
}

