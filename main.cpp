/*****************************************************************************
 *	Name:                                                                    *
 *	Date:                                                                    *
 *                                                                           *
 *	Purpose:                                                                 *
 *	                                                                         *
 *	Usage:                                                                   *
 *	                                                                         *
 *	Revision History:                                                        *
 *	                                                                         *
 *	Known Issues:                                                            *
 *	                                                                         *
 *****************************************************************************/

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "setup.h"

int dx = 0;
int dy = 0;

int astronautX = 320;
int astronautY = 240;
int counter;
int frame;
int direction;

bool doexit = false;
bool moving = false;
bool has_hatch_1 = false;


// Initialize display
ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *background;
Image spaceship;
Image astronaut[12];
Image hatch;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *timer;

int main_innitialize();
int images_innitialize();
int functions_innitialize();
void draw_background();
void draw_image(Image &a);
void draw_astronaut(Image astronaut[], int frame, int direction);
bool check_in_bounds(int &posX, int &posY);
bool isCollision(Image a, Image b);
void drawBoundingBox(Image image);
void calcBounds(Image &a);

// NOTE: argc, argv parameters are required.
int main(int argc, char *argv[]) {

    // Initialize Allegro
    al_init();

	main_innitialize();
	images_innitialize();

    al_start_timer(timer);

    for(int i = 0; i < 12; i ++){
        astronaut[i].x = 320;
        astronaut[i].y = 240;
    }

	while (!doexit){
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	doexit = true;
      	}
      	else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    dy -=2;
                    moving = true;
                    direction = 2;
                    break;
                case ALLEGRO_KEY_DOWN:
                    dy += 2;
                    moving = true;
                    direction = 0;
                    break;
                case ALLEGRO_KEY_LEFT:
                    dx -= 2;
                    moving = true;
                    direction = 1;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    dx += 2;
                    moving = true;
                    direction = 3;
                    break;
                case ALLEGRO_KEY_SPACE:
                    if (isCollision(astronaut[frame], spaceship) && has_hatch_1){
                        hatch.x = spaceship.x + 10;
                        hatch.y = spaceship.y + 30;
                        has_hatch_1 = false;
                    }
                    else if (isCollision(astronaut[frame], hatch)){
                        has_hatch_1 = !has_hatch_1;
                    }
                    break;
            }
      	}

        else if(event.type == ALLEGRO_EVENT_KEY_UP){
            dx = 0;
            dy = 0;
            moving = false;
        }

        else if(event.type == ALLEGRO_EVENT_TIMER){
            if (check_in_bounds(astronaut[frame].x, astronaut[frame].y)){
                for(int i = 0; i < 12; i++){
                    astronaut[i].x += dx;
                    astronaut[i].y += dy;
                }
            }

            printf("x=%d, y=%d", astronaut[frame].x, astronaut[frame].y);
            calcBounds(astronaut[frame]);
            calcBounds(hatch);

            if (has_hatch_1){
                hatch.x = astronaut[frame].x;
                hatch.y = astronaut[frame].y;
            }

            draw_background();
            draw_image(spaceship);
            draw_image(hatch);
            //printf("before\n");
            drawBoundingBox(astronaut[frame]);
            //printf("middle\n");
            drawBoundingBox(hatch);
            //printf("end\n");
            if (!moving){
                frame = 0;
            }

            draw_astronaut(astronaut, frame, direction);
            printf("width:%d\n", al_get_bitmap_width(astronaut[frame].bitmap));
            al_flip_display();
            counter ++;
            counter %= 60;

            if(counter%15 == 0){
                if(moving){
                    frame = frame%2 + 1;
                }
            }
        }
	}

    // Free up memory taken by display.
    al_destroy_display(display);

    // Exit with no errors
	return 0;
}
