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
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "setup.h"

int dx = 0;
int dy = 0;

int astronautX = 320;
int astronautY = 240;
int counter;
int frame;
int direction;
int game_clock = 150;

bool doexit = false;
bool moving = false;
bool has_piece = false;
bool game_complete = false;
bool action_complete = false;


// Initialize display
ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *background;
ship spaceship[numSpaceships];
ship cargoShip[numCargoShips];
Image astronaut[12];
game_peice hatches[numPieces];
game_peice cargo[numPieces];
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *timer;
ALLEGRO_FONT *font;

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
                    action_complete = false;
                    for(int i = 0; i < numPieces; i++){
                        for(int j = 0; j < numSpaceships; j++){
                            if (isCollision(astronaut[frame], spaceship[j].ship_image) && hatches[i].picked_up){
                                //printf("collision\n");
                                for(int k = 0; k < 3; k++){
                                    if (!spaceship[j].panel_spots[k]){
                                        hatches[i].element_image.x = spaceship[j].ship_image.x + 33 + k;
                                        hatches[i].element_image.y = spaceship[j].ship_image.y + 63 + 63*k;
                                        spaceship[j].panel_spots[k] = true;
                                        hatches[i].placed = true;
                                        hatches[i].picked_up = false;
                                        has_piece = false;
                                        printf("placed\n");
                                        break;
                                    }
                                }
                                action_complete = true;
                                break;
                            }
                            else if (isCollision(astronaut[frame], spaceship[j].ship_image) && cargo[i].picked_up){
                                //printf("collision\n");
                                for(int k = 0; k < 3; k++){
                                    if (!spaceship[j].cargo_spots[k] && spaceship[j].panel_spots[k]){
                                        cargo[i].element_image.x = spaceship[j].ship_image.x + 43;
                                        cargo[i].element_image.y = spaceship[j].ship_image.y + 73 + 63*k;
                                        spaceship[j].cargo_spots[k] = true;
                                        cargo[i].placed = true;
                                        cargo[i].picked_up = false;
                                        has_piece = false;
                                        printf("placed\n");
                                        break;
                                    }
                                }
                                action_complete = true;
                                break;
                            }
                        }

                        for(int j = 0; j < numCargoShips; j++){
                            if (isCollision(astronaut[frame], cargoShip[j].ship_image) && hatches[i].picked_up){
                                for(int k = 0; k < 3; k++){
                                    if (!cargoShip[j].panel_spots[k]){
                                        hatches[i].element_image.x = cargoShip[j].ship_image.x + 8 + 71*k;
                                        hatches[i].element_image.y = cargoShip[j].ship_image.y + 43 - k;
                                        cargoShip[j].panel_spots[k] = true;
                                        hatches[i].placed = true;
                                        hatches[i].picked_up = false;
                                        has_piece = false;
                                        printf("placed\n");
                                        break;
                                    }

                                }
                                action_complete = true;
                                break;
                            }
                            else if (isCollision(astronaut[frame], cargoShip[j].ship_image) && cargo[i].picked_up){
                                //printf("collision\n");
                                for(int k = 0; k < 3; k++){
                                    if (!cargoShip[j].cargo_spots[k] && cargoShip[j].panel_spots[k]){
                                        cargo[i].element_image.x = cargoShip[j].ship_image.x + 15 + 71*k;
                                        cargo[i].element_image.y = cargoShip[j].ship_image.y + 50 -  k;
                                        cargoShip[j].cargo_spots[k] = true;
                                        cargo[i].placed = true;
                                        cargo[i].picked_up = false;
                                        has_piece = false;
                                        printf("placed\n");
                                        break;
                                    }
                                }
                                action_complete = true;
                                break;
                            }
                        }

                        if (isCollision(astronaut[frame], hatches[i].element_image) && !hatches[i].placed && !has_piece){
                            printf("picking up\n");
                            hatches[i].picked_up = true;
                            has_piece = true;
                            action_complete = true;
                            break;
                        }

                        else if (has_piece && hatches[i].picked_up){
                            hatches[i].picked_up = false;
                            hatches[i].element_image.y += 15;
                            has_piece = false;
                            action_complete = true;
                            break;
                        }

                        else if (isCollision(astronaut[frame], cargo[i].element_image) && !cargo[i].placed && !has_piece){
                            printf("picking up\n");
                            cargo[i].picked_up = true;
                            has_piece = true;
                            action_complete = true;
                            break;
                        }

                        else if (has_piece && cargo[i].picked_up){
                            cargo[i].picked_up = false;
                            cargo[i].element_image.y += 15;
                            has_piece = false;
                            action_complete = true;
                            break;
                        }

                        if(action_complete){
                            break;
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
            for(int i = 0; i < 12; i++){
                calcBounds(astronaut[i]);
            }

            for(int i = 0; i < numPieces; i++){
                calcBounds(hatches[i].element_image);
                calcBounds(cargo[i].element_image);
            }

            for(int i = 0; i < numPieces; i++){
                if (hatches[i].picked_up){
                    hatches[i].element_image.x = astronaut[frame].x;
                    hatches[i].element_image.y = astronaut[frame].y + 10;
                    has_piece = true;

                    if (direction == 1){
                        hatches[i].element_image.x -= 25;
                    }
                    else if(direction == 3){
                        hatches[i].element_image.x += 25;
                    }
                    else if(direction == 0){
                        hatches[i].element_image.y += 15;
                    }
                }

                else if (cargo[i].picked_up){
                    cargo[i].element_image.x = astronaut[frame].x + 10;
                    cargo[i].element_image.y = astronaut[frame].y + 20;
                    has_piece = true;

                    if (direction == 1){
                        cargo[i].element_image.x -= 25;
                    }
                    else if(direction == 3){
                        cargo[i].element_image.x += 25;
                    }
                    else if(direction == 0){
                        cargo[i].element_image.y += 15;
                    }
                }
            }

            draw_background();

            if (game_complete){
                al_rest(0.5);
                al_draw_text(font, WHITE, 1380/2, (700/4), ALLEGRO_ALIGN_CENTRE, "Level Completed");
            }

            else{
                al_draw_textf(font, WHITE, 10, 0, 0, "%d", game_clock);
                for(int i = 0; i < numSpaceships; i++){
                    draw_image(spaceship[i].ship_image);
                    drawBoundingBox(spaceship[i].ship_image);
                }

                for(int i = 0; i < numCargoShips; i++){
                    draw_image(cargoShip[i].ship_image);
                    drawBoundingBox(cargoShip[i].ship_image);
                }


                for(int i = 0; i < numPieces; i++){
                    if(!cargo[i].picked_up || (cargo[i].picked_up && direction != 0)){
                        draw_image(cargo[i].element_image);
                        drawBoundingBox(cargo[i].element_image);
                    }

                }
                for(int i = 0; i < numPieces; i++){
                    if(!hatches[i].picked_up || (hatches[i].picked_up && direction != 0)){
                        draw_image(hatches[i].element_image);
                        drawBoundingBox(hatches[i].element_image);
                    }
                }

                if (!moving){
                    frame = 0;
                }

                drawBoundingBox(astronaut[frame]);
                draw_astronaut(astronaut, frame, direction);

                for(int i = 0; i < numPieces; i++){
                    if(cargo[i].picked_up && direction == 0){
                        draw_image(cargo[i].element_image);
                        drawBoundingBox(cargo[i].element_image);
                    }

                    if(hatches[i].picked_up && direction == 0){
                        draw_image(hatches[i].element_image);
                        drawBoundingBox(hatches[i].element_image);
                    }

                }


            }

            game_complete = true;
            for(int i = 0; i < numSpaceships; i++){
                if (!spaceship[i].panel_spots[2] || !spaceship[i].cargo_spots[2]){
                    game_complete = false;
                }
            }
            for(int i = 0; i < numCargoShips; i++){
                if (!cargoShip[i].panel_spots[2] || !cargoShip[i].cargo_spots[2]){
                    game_complete = false;
                }
            }

            al_flip_display();
            counter ++;
            counter %= 60;

            if(counter%12 == 0){
                if(moving){
                    frame = frame%2 + 1;
                }
            }
            if(counter%60 == 0){
                game_clock--;
            }
        }
	}

    // Free up memory taken by display.
    al_destroy_display(display);
    for(int i = 0; i < 12; i++){
        al_destroy_bitmap(astronaut[i].bitmap);
    }
    for(int i = 0; i < numPieces; i++){
        al_destroy_bitmap(hatches[i].element_image.bitmap);
        al_destroy_bitmap(cargo[i].element_image.bitmap);
    }
    for(int i = 0; i < numSpaceships; i++){
        al_destroy_bitmap(spaceship[i].ship_image.bitmap);
    }
    for(int i = 0; i < numCargoShips; i++){
        al_destroy_bitmap(cargoShip[i].ship_image.bitmap);
    }

    // Exit with no errors
	return 0;
}
