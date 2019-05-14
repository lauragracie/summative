#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "setup.h"


extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *background;
extern Image *spaceship;
extern ALLEGRO_BITMAP *astronaut[12];
extern ALLEGRO_BITMAP *hatch;
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

void draw_spaceship(Image &a){
    al_draw_bitmap(a.bitmap, a.x, a.y, 0);
}

void draw_hatch(){
    al_draw_scaled_bitmap(hatch,0,0,300,300,500,250,50,50,0);
}

void draw_astronaut(Image astronaut[], int posX, int posY, int frame, int direction){
    frame += direction*3;
    al_draw_scaled_bitmap(astronaut[frame].bitmap,0,0,95,115,posX,posY,58,69,0);
}

bool check_in_bounds(int &posX, int &posY){

        if (posX <= 0){
            posX += 1;
        }
        else if (posX >= 1322){
            posX -= 1;
        }
        else if (posY <= 0){
            posY += 1;
        }
        else if (posY >= 631){
            posY -= 1;
        }
        else{
            return true;
        }

        return false;
}
