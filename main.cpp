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
bool has_hatch = false;


// Initialize display
ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *background;
Image spaceship;
Image astronaut[12];
game_peice hatches[numHatches];
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *timer;

int main_innitialize();
int images_innitialize();
int functions_innitialize();
void draw_background();
void draw_image(Image &a);
void draw_astronaut(Image astronaut[], int frame, int direction);
bool check_in_bounds(Image astronaut[]);
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

    for(int i = 0; i < numHatches; i++){
        hatches[i].picked_up = false;
        hatches[i].placed = false;
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
                    for(int i = 0; i < numHatches; i++){
                        if (isCollision(astronaut[frame], spaceship) && hatches[i].picked_up){
                            hatches[i].element_image.x = spaceship.x + 33;
                            hatches[i].element_image.y = spaceship.y + 63;
                            hatches[i].picked_up = false;
                            hatches[i].placed = true;
                            has_hatch = false;
                        }

                        else if (isCollision(astronaut[frame], hatches[i].element_image) && !hatches[i].placed && !has_hatch){
                            printf("picking up\n");
                            hatches[i].picked_up = true;
                            has_hatch = true;
                        }

                        else if (isCollision(astronaut[frame], hatches[i].element_image) && has_hatch){
                            printf("has hatch\n");
                            if (hatches[i].picked_up){
                                hatches[i].picked_up = false;
                                printf("drop hatch\n");
                                has_hatch = false;
                            }
                            else{
                                printf("two hatches\n");
                                hatches[i].picked_up = false;
                            }

                        }

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
            if (check_in_bounds(astronaut)){
                for(int i = 0; i < 12; i++){
                    astronaut[i].x += dx;
                    astronaut[i].y += dy;
                }
            }

            //printf("x=%d, y=%d", astronaut[frame].x, astronaut[frame].y);
            calcBounds(astronaut[frame]);
            for(int i = 0; i < numHatches; i++){
                calcBounds(hatches[i].element_image);
            }

            for(int i = 0; i < numHatches; i++){
                //printf("%d", hatches[1].picked_up);
                if (hatches[i].picked_up){
                    hatches[i].element_image.x = astronaut[frame].x;
                    hatches[i].element_image.y = astronaut[frame].y;
                    has_hatch = true;
                }
            }


            draw_background();
            draw_image(spaceship);

            for(int i = 0; i < numHatches; i++){
                draw_image(hatches[i].element_image);
                drawBoundingBox(hatches[i].element_image);
            }

            drawBoundingBox(astronaut[frame]);
            drawBoundingBox(spaceship);
            if (!moving){
                frame = 0;
            }

            draw_astronaut(astronaut, frame, direction);
            //printf("width:%d\n", al_get_bitmap_width(astronaut[frame].bitmap));
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
