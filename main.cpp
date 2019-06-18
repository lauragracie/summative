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

int dx1 = 0;
int dy1 = 0;


int counter;
int frame1;
int direction1;
int game_clock = 150;

bool doexit = false;
bool moving = false;
bool has_piece = false;
bool game_complete = false;
bool game_over = false;
bool action_complete = false;


// Initialize display
ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *background;
ship spaceship[numSpaceships];
ship cargoShip[numCargoShips];
astronaut astronaut_1;
astronaut astronaut_2;
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
        astronaut_1.astronaut_image[i].x = 320;
        astronaut_1.astronaut_image[i].y = 240;
        astronaut_2.astronaut_image[i].x = 800;
        astronaut_2.astronaut_image[i].y = 400;
    }

	while (!doexit){
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	doexit = true;
      	}
      	else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_W:
                    astronaut_2.dy -=2;
                    astronaut_2.moving = true;
                    astronaut_2.direction = 2;
                    break;
                case ALLEGRO_KEY_S:
                    astronaut_2.dy += 2;
                    astronaut_2.moving = true;
                    astronaut_2.direction = 0;
                    break;
                case ALLEGRO_KEY_A:
                    astronaut_2.dx -= 2;
                    astronaut_2.moving = true;
                    astronaut_2.direction = 1;
                    break;
                case ALLEGRO_KEY_D:
                    astronaut_2.dx += 2;
                    astronaut_2.moving = true;
                    astronaut_2.direction = 3;
                    break;
                case ALLEGRO_KEY_SPACE:
                    action_complete = false;
                    for(int i = 0; i < numPieces; i++){
                        for(int j = 0; j < numSpaceships; j++){
                            if (isCollision(astronaut_2.astronaut_image[0], spaceship[j].ship_image) && hatches[i].picked_up && hatches[i].astronaut == 1){
                                for(int k = 0; k < 3; k++){
                                    if (!spaceship[j].panel_spots[k]){
                                        hatches[i].element_image.x = spaceship[j].ship_image.x + 33 + k;
                                        hatches[i].element_image.y = spaceship[j].ship_image.y + 63 + 63*k;
                                        spaceship[j].panel_spots[k] = true;
                                        hatches[i].placed = true;
                                        hatches[i].picked_up = false;
                                        astronaut_2.has_piece = false;
                                        break;
                                    }
                                }
                                action_complete = true;
                                break;
                            }
                            else if (isCollision(astronaut_2.astronaut_image[0], spaceship[j].ship_image) && cargo[i].picked_up && car){
                                for(int k = 0; k < 3; k++){
                                    if (!spaceship[j].cargo_spots[k] && spaceship[j].panel_spots[k]){
                                        cargo[i].element_image.x = spaceship[j].ship_image.x + 43;
                                        cargo[i].element_image.y = spaceship[j].ship_image.y + 73 + 63*k;
                                        spaceship[j].cargo_spots[k] = true;
                                        cargo[i].placed = true;
                                        cargo[i].picked_up = false;
                                        astronaut_2.has_piece = false;
                                        break;
                                    }
                                }
                                action_complete = true;
                                break;
                            }
                        }

                        for(int j = 0; j < numCargoShips; j++){
                            if (isCollision(astronaut_2.astronaut_image[0], cargoShip[j].ship_image) && hatches[i].picked_up){
                                for(int k = 0; k < 3; k++){
                                    if (!cargoShip[j].panel_spots[k]){
                                        hatches[i].element_image.x = cargoShip[j].ship_image.x + 8 + 71*k;
                                        hatches[i].element_image.y = cargoShip[j].ship_image.y + 43 - k;
                                        cargoShip[j].panel_spots[k] = true;
                                        hatches[i].placed = true;
                                        hatches[i].picked_up = false;
                                        astronaut_2.has_piece = false;
                                        break;
                                    }

                                }
                                action_complete = true;
                                break;
                            }
                            else if (isCollision(astronaut_2.astronaut_image[0], cargoShip[j].ship_image) && cargo[i].picked_up){
                                for(int k = 0; k < 3; k++){
                                    if (!cargoShip[j].cargo_spots[k] && cargoShip[j].panel_spots[k]){
                                        cargo[i].element_image.x = cargoShip[j].ship_image.x + 15 + 71*k;
                                        cargo[i].element_image.y = cargoShip[j].ship_image.y + 50 -  k;
                                        cargoShip[j].cargo_spots[k] = true;
                                        cargo[i].placed = true;
                                        cargo[i].picked_up = false;
                                        astronaut_2.has_piece = false;
                                        break;
                                    }
                                }
                                action_complete = true;
                                break;
                            }
                        }

                        if (isCollision(astronaut_2.astronaut_image[0], hatches[i].element_image) && !hatches[i].placed && !astronaut_2.has_piece){
                            hatches[i].picked_up = true;
                            astronaut_2.has_piece = true;
                            action_complete = true;
                            break;
                        }

                        else if (astronaut_2.has_piece && hatches[i].picked_up){
                            hatches[i].picked_up = false;
                            hatches[i].element_image.y += 15;
                            astronaut_2.has_piece = false;
                            action_complete = true;
                            break;
                        }

                        else if (isCollision(astronaut_2.astronaut_image[0], cargo[i].element_image) && !cargo[i].placed && !astronaut_2.has_piece){
                            cargo[i].picked_up = true;
                            astronaut_2.has_piece = true;
                            action_complete = true;
                            break;
                        }

                        else if (astronaut_2.has_piece && cargo[i].picked_up){
                            cargo[i].picked_up = false;
                            cargo[i].element_image.y += 15;
                            astronaut_2.has_piece = false;
                            action_complete = true;
                            break;
                        }

                        if(action_complete){
                            break;
                        }
                    }
                    break;

                case ALLEGRO_KEY_UP:
                    astronaut_1.dy -=2;
                    astronaut_1.moving = true;
                    astronaut_1.direction = 2;
                    break;
                case ALLEGRO_KEY_DOWN:
                    astronaut_1.dy += 2;
                    astronaut_1.moving = true;
                    astronaut_1.direction = 0;
                    break;
                case ALLEGRO_KEY_LEFT:
                    astronaut_1.dx -= 2;
                    astronaut_1.moving = true;
                    astronaut_1.direction = 1;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    astronaut_1.dx += 2;
                    astronaut_1.moving = true;
                    astronaut_1.direction = 3;
                    break;
                case ALLEGRO_KEY_ENTER:
                    action_complete = false;
                    for(int i = 0; i < numPieces; i++){
                        for(int j = 0; j < numSpaceships; j++){
                            if (isCollision(astronaut_1.astronaut_image[0], spaceship[j].ship_image) && hatches[i].picked_up && hatches[i].astronaut == 1){
                                for(int k = 0; k < 3; k++){
                                    if (!spaceship[j].panel_spots[k]){
                                        hatches[i].element_image.x = spaceship[j].ship_image.x + 33 + k;
                                        hatches[i].element_image.y = spaceship[j].ship_image.y + 63 + 63*k;
                                        spaceship[j].panel_spots[k] = true;
                                        hatches[i].placed = true;
                                        hatches[i].picked_up = false;
                                        astronaut_1.has_piece = false;
                                        break;
                                    }
                                }
                                action_complete = true;
                                break;
                            }
                            else if (isCollision(astronaut_1.astronaut_image[0], spaceship[j].ship_image) && cargo[i].picked_up){
                                for(int k = 0; k < 3; k++){
                                    if (!spaceship[j].cargo_spots[k] && spaceship[j].panel_spots[k]){
                                        cargo[i].element_image.x = spaceship[j].ship_image.x + 43;
                                        cargo[i].element_image.y = spaceship[j].ship_image.y + 73 + 63*k;
                                        spaceship[j].cargo_spots[k] = true;
                                        cargo[i].placed = true;
                                        cargo[i].picked_up = false;
                                        astronaut_1.has_piece = false;
                                        break;
                                    }
                                }
                                action_complete = true;
                                break;
                            }
                        }

                        for(int j = 0; j < numCargoShips; j++){
                            if (isCollision(astronaut_1.astronaut_image[0], cargoShip[j].ship_image) && hatches[i].picked_up){
                                for(int k = 0; k < 3; k++){
                                    if (!cargoShip[j].panel_spots[k]){
                                        hatches[i].element_image.x = cargoShip[j].ship_image.x + 8 + 71*k;
                                        hatches[i].element_image.y = cargoShip[j].ship_image.y + 43 - k;
                                        cargoShip[j].panel_spots[k] = true;
                                        hatches[i].placed = true;
                                        hatches[i].picked_up = false;
                                        astronaut_1.has_piece = false;
                                        break;
                                    }

                                }
                                action_complete = true;
                                break;
                            }
                            else if (isCollision(astronaut_1.astronaut_image[0], cargoShip[j].ship_image) && cargo[i].picked_up){
                                for(int k = 0; k < 3; k++){
                                    if (!cargoShip[j].cargo_spots[k] && cargoShip[j].panel_spots[k]){
                                        cargo[i].element_image.x = cargoShip[j].ship_image.x + 15 + 71*k;
                                        cargo[i].element_image.y = cargoShip[j].ship_image.y + 50 -  k;
                                        cargoShip[j].cargo_spots[k] = true;
                                        cargo[i].placed = true;
                                        cargo[i].picked_up = false;
                                        astronaut_1.has_piece = false;
                                        break;
                                    }
                                }
                                action_complete = true;
                                break;
                            }
                        }

                        if (isCollision(astronaut_1.astronaut_image[0], hatches[i].element_image) && !hatches[i].placed && !astronaut_1.has_piece){
                            hatches[i].picked_up = true;
                            astronaut_1.has_piece = true;
                            action_complete = true;
                            break;
                        }

                        else if (astronaut_1.has_piece && hatches[i].picked_up){
                            hatches[i].picked_up = false;
                            hatches[i].element_image.y += 15;
                            astronaut_1.has_piece = false;
                            action_complete = true;
                            break;
                        }

                        else if (isCollision(astronaut_1.astronaut_image[0], cargo[i].element_image) && !cargo[i].placed && !astronaut_1.has_piece){
                            cargo[i].picked_up = true;
                            astronaut_1.has_piece = true;
                            action_complete = true;
                            break;
                        }

                        else if (astronaut_1.has_piece && cargo[i].picked_up){
                            cargo[i].picked_up = false;
                            cargo[i].element_image.y += 15;
                            astronaut_1.has_piece = false;
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
            switch (event.keyboard.keycode){
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_LEFT:
                astronaut_1.dx = 0;
                astronaut_1.dy = 0;
                astronaut_1.moving = false;
                break;

            case ALLEGRO_KEY_W:
            case ALLEGRO_KEY_S:
            case ALLEGRO_KEY_D:
            case ALLEGRO_KEY_A:
                astronaut_2.dx = 0;
                astronaut_2.dy = 0;
                astronaut_2.moving = false;
                break;
            }
        }

        else if(event.type == ALLEGRO_EVENT_TIMER){
            if (check_in_bounds(astronaut_1.astronaut_image)){
                for(int i = 0; i < 12; i++){
                    astronaut_1.astronaut_image[i].x += astronaut_1.dx;
                    astronaut_1.astronaut_image[i].y += astronaut_1.dy;
                }
            }

            if (check_in_bounds(astronaut_2.astronaut_image)){
                for(int i = 0; i < 12; i++){
                    astronaut_2.astronaut_image[i].x += astronaut_2.dx;
                    astronaut_2.astronaut_image[i].y += astronaut_2.dy;
                }
            }

            for(int i = 0; i < 12; i++){
                calcBounds(astronaut_1.astronaut_image[i]);
                calcBounds(astronaut_2.astronaut_image[i]);
            }

            for(int i = 0; i < numPieces; i++){
                calcBounds(hatches[i].element_image);
                calcBounds(cargo[i].element_image);
            }

            for(int i = 0; i < numPieces; i++){
                if (hatches[i].picked_up){
                    hatches[i].element_image.x = astronaut_1.astronaut_image[frame1].x;
                    hatches[i].element_image.y = astronaut_1.astronaut_image[frame1].y + 10;
                    has_piece = true;

                    if (direction1 == 1){
                        hatches[i].element_image.x -= 25;
                    }
                    else if(direction1 == 3){
                        hatches[i].element_image.x += 25;
                    }
                    else if(direction1 == 0){
                        hatches[i].element_image.y += 15;
                    }
                }

                else if (cargo[i].picked_up){
                    cargo[i].element_image.x = astronaut_1.astronaut_image[frame1].x + 10;
                    cargo[i].element_image.y = astronaut_1.astronaut_image[frame1].y + 20;
                    has_piece = true;

                    if (direction1 == 1){
                        cargo[i].element_image.x -= 25;
                    }
                    else if(direction1 == 3){
                        cargo[i].element_image.x += 25;
                    }
                    else if(direction1 == 0){
                        cargo[i].element_image.y += 15;
                    }
                }
            }

            draw_background();

            if (game_complete){
                al_rest(0.5);
                al_draw_text(font, WHITE, 1380/2, (700/4), ALLEGRO_ALIGN_CENTRE, "Level Completed");
                al_draw_textf(font, WHITE, 1380/2, 700/2, ALLEGRO_ALIGN_CENTER, "Time: %d seconds", (150 - game_clock) );
            }

            else if (game_clock == 0){
                al_rest(0.5);
                al_draw_multiline_text(font, WHITE, 1380/2, 700/4, 1200, 200, ALLEGRO_ALIGN_CENTER, "You ran out of time Game Over");
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
                    if(!cargo[i].picked_up || (cargo[i].picked_up && direction1 != 0)){
                        draw_image(cargo[i].element_image);
                        drawBoundingBox(cargo[i].element_image);
                    }

                }
                for(int i = 0; i < numPieces; i++){
                    if(!hatches[i].picked_up || (hatches[i].picked_up && direction1 != 0)){
                        draw_image(hatches[i].element_image);
                        drawBoundingBox(hatches[i].element_image);
                    }
                }

                if (!moving){
                    frame1 = 0;
                }

                drawBoundingBox(astronaut_1.astronaut_image[frame1]);
                draw_astronaut(astronaut_1.astronaut_image, frame1, direction1);

                draw_astronaut(astronaut_2.astronaut_image, astronaut_2.frame, astronaut_2.direction);

                for(int i = 0; i < numPieces; i++){
                    if(cargo[i].picked_up && direction1 == 0){
                        draw_image(cargo[i].element_image);
                        drawBoundingBox(cargo[i].element_image);
                    }

                    if(hatches[i].picked_up && direction1 == 0){
                        draw_image(hatches[i].element_image);
                        drawBoundingBox(hatches[i].element_image);
                    }

                }

            counter ++;
            counter %= 60;

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


            if(counter%12 == 0){
                if(moving){
                    frame1 = frame1%2 + 1;
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
        al_destroy_bitmap(astronaut_1.astronaut_image[i].bitmap);
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
