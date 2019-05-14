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


// Initialize display
ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *background;
Image spaceship;
Image astronaut[12];
ALLEGRO_BITMAP *hatch;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *timer;

int main_innitialize();
int images_innitialize();
int functions_innitialize();
void draw_background();
void draw_spaceship(Image &a);
void draw_hatch();
void draw_astronaut(Image astronaut[], int posX, int posY, int frame, int direction);
bool check_in_bounds(int &posX, int &posY);

// NOTE: argc, argv parameters are required.
int main(int argc, char *argv[]) {

    // Initialize Allegro
    al_init();

	main_innitialize();
	images_innitialize();

    al_start_timer(timer);

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
            }
      	}

        else if(event.type == ALLEGRO_EVENT_KEY_UP){
            dx = 0;
            dy = 0;
            moving = false;
        }
        else if(event.type == ALLEGRO_EVENT_TIMER){
            if (check_in_bounds(astronautX, astronautY)){
                astronautX += dx;
                astronautY += dy;
            }

            draw_background();
            draw_spaceship(spaceship);
            draw_hatch();
            if (!moving){
                frame = 0;
            }

            draw_astronaut(astronaut, astronautX, astronautY, frame, direction);
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
