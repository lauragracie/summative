/*
This program declares all the functions that will be used in the other programs. Most of the functions involve
calculating or collision detection of boundary boxes or drawing images, as these functions repeat often
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "setup.h"


//These Allegro add-ons and images are initialized in main.cpp
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *background;
extern Image spaceship;
extern Image astronaut[12];
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER *timer;


//Calculate the boundary box of an image based on its x and y coordinates, width and hight
void calcBounds(Image &a) {
    a.bbLeft = a.x;
	a.bbTop  = a.y;
	a.bbRight = a.bbLeft + al_get_bitmap_width(a.bitmap);
	a.bbBottom = a.bbTop + al_get_bitmap_height(a.bitmap);
}

//Draw the background image, covering the whole screen
void draw_background(){
    al_draw_scaled_bitmap(background,0,0,1300,1300,0,0,1380,1000,0);
}

//Takes an Image structure and draws it based on its bitmap and x and y coordinates
void draw_image(Image &a){
    al_draw_bitmap(a.bitmap, a.x, a.y, 0);
}

//Draws the astronaut sprite
void draw_astronaut(Image astronaut[], int frame, int direction){
    //The astronaut sprite that will be displayed depends on the direction in which it is walking.
    //Ex: If the astronaut is on the first walking frame(1) and facing up (dirction = 2), sprite #7 will be displayed
    frame += direction*3;
    al_draw_bitmap(astronaut[frame].bitmap,astronaut[frame].x,astronaut[frame].y,0);
}

//Returns true if the astronaut is in the bounds of the screen, else returns false
bool check_in_bounds(Image astronaut[]){

        int dx = 0;
        int dy = 0;

        //If the astronaut is at the edge of the screen, it gets redrawn a bit away from the edge
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

//Returns true if the boundary boxes of the two images are overlapping, returns false if they aren't overlapping
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

//Draws the boundary box of an image. Used mostly for testing/troubleshooting the code
void drawBoundingBox(Image image) {
    calcBounds(image);
	al_draw_line(image.bbLeft, image.bbTop, image.bbRight, image.bbTop, WHITE, 1);
    al_draw_line(image.bbLeft, image.bbBottom, image.bbRight, image.bbBottom, WHITE, 1);
	al_draw_line(image.bbLeft, image.bbTop, image.bbLeft, image.bbBottom, WHITE, 1);
	al_draw_line(image.bbRight, image.bbTop, image.bbRight, image.bbBottom, WHITE,1);
}

