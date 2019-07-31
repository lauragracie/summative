/*****************************************************************************
 *	Name: Laura Gracie                                                       *
 *	Date: June 11th, 2019                                                    *
 *                                                                           *
 *	Purpose: Summative Game Destination Deep Space: The Video Game           *
 *	                                                                         *
 *	Usage: Use arrow keys to move the astronaut around the screen. Use the   *
 *          space bar to pick up hatch panels and cargo and put them in the  *
 *          ships. Fill up the ships before the timer runs out.              *
 *	                                                                         *
 *	Revision History: Version 1.0 completed May 14th                         *
 *                    Version 2.0 completed May 28th                         *
 *	                                                                         *
 *	Known Issues: No known issues                                            *
 *	                                                                         *
 *****************************************************************************/

//include allegro add-on libraries and setup.h file
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "setup.h"


//int dx1 = 0;
//int dy1 = 0;

int counter;
//int frame1;
//int direction1;
int game_clock = 150;

bool doexit = false;
//bool moving = false;
//bool has_piece = false;
bool game_complete = false;
bool game_over = false;
bool action_complete = false;


char instructions[600];     //Stores the instructions on how to play the game.

//Initialize Allegro add-ons (display, event queue, timer, fonts etc)
ALLEGRO_DISPLAY *display;

ALLEGRO_BITMAP *background;
ship spaceship[numSpaceships];
ship cargoShip[numCargoShips];
astronaut astronaut_1;
astronaut astronaut_2;
game_peice hatches[numPieces];
game_peice cargo[numPieces];
Image logo;
Image logo_background;

ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *timer;
ALLEGRO_FONT *font;
ALLEGRO_FONT *font_small;


//prototype functions that run background processes. These are each declared in separate files
int allegro_innitialize();
int images_innitialize();

//These functions are all declared in functions initialize.cpp
void draw_background();
void draw_image(Image &a);
void draw_astronaut(Image astronaut[], int frame, int direction);
void drawBoundingBox(Image image);

bool check_in_bounds(Image astronaut[]);
bool isCollision(Image a, Image b);
void calcBounds(Image &a);



// NOTE: argc, argv parameters are required.
int main(int argc, char *argv[]) {

    // Initialize Allegro
    al_init();

    //Run background initialization programs
	allegro_innitialize();
	images_innitialize();

	//Open file "instructions.txt" and scan the text to char array instructions[600]
	FILE *fptr = fopen("instructions.txt", "r");
	fgets(instructions, 600, fptr);

	//Draw the main menu, including the Destination Deep Space logo and the play button
    draw_image(logo);
    al_draw_text(font_small, WHITE, 500, 400, 0, "The Video Game");
    al_draw_rectangle(620, 450, 800, 500, WHITE, 2);
    al_draw_text(font_small, WHITE, 640, 460, 0, "PLAY");
    al_flip_display();


    //wait for user to click the play button, then display the instructions screen
    while (!start_game){
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	doexit = true;
      	}
      	//If the user clicks within the area of the play button, start_game is set to true and it exits the loop.
      	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(event.mouse.x > 620 && event.mouse.x < 800 && event.mouse.y > 450 && event.mouse.y < 500){
                start_game = true;
                show_instructions = true;
            }
      	}


    //Display the instructions screen: the logo background, instructions on how to play the game and the play button.
    draw_image(logo_background);
    // The text scanned from the file is displayed
    al_draw_multiline_textf(font_small, WHITE, 40, 80, 1280, 40, 0, "%s", instructions);
    al_draw_rectangle(620, 600, 800, 650, WHITE, 2);
    al_draw_text(font_small, WHITE, 620, 610, 0, "START");
    al_flip_display();

    //wait for the user to press the play button, then start the game
    while (show_instructions){
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	doexit = true;
      	}
      	//if the user clicks within the area of the play button, set show_instructions to false, which exits the loop
      	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(event.mouse.x > 620 && event.mouse.x < 800 && event.mouse.y > 600 && event.mouse.y < 650){
                show_instructions = false;
            }
        }
    }

    for(int i = 0; i < 12; i ++){
        astronaut_1.x = 320;
        astronaut_1.y = 240;
        astronaut_2.x = 800;
        astronaut_2.y = 400;
    }
      
    al_start_timer(timer); //Start the timer. This timer will go off 60 times per second

    //This is the main code for the game play.
	while (!doexit){
        al_wait_for_event(event_queue, &event);

        //If the user closes the display, the code stops running
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	doexit = true;
      	}

      	else if(event.type == ALLEGRO_EVENT_KEY_DOWN){ //If a key has been pressed
            switch(event.keyboard.keycode){
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

                // The following code contains all the sequences that could happen when the user presses the space key
                case ALLEGRO_KEY_SPACE:
                    //The code has to consider collisions between the astronaut and every single game piece and every spaceship or cargo ship
                    for(int i = 0; i < numPieces; i++){
                        for(int j = 0; j < numSpaceships; j++){

                            //If the astronaut is colliding with a spaceship and is carrying a hatch, the hatch is placed in the spaceship     
                            if (isCollision(astronaut_1.astronaut_image[0], spaceship[j].ship_image) && hatches[i].picked_up){
                                for(int k = 0; k < 3; k++){
                                    //The code goes through each of the panel spots (k) on the rocket until it finds an empty one
                                    if (!spaceship[j].panel_spots[k]){
                                        //The hatch is sent to the empty panel spot. Its new coordinates depend on the value of k
                                        hatches[i].element_image.x = spaceship[j].ship_image.x + 33 + k;
                                        hatches[i].element_image.y = spaceship[j].ship_image.y + 63 + 63*k;
                                        spaceship[j].panel_spots[k] = true; //The panel spot of the spaceship has been filled
                                        hatches[i].placed = true; //The hatch has been placed
                                        hatches[i].picked_up = false; //The hatch is no longer being carried
                                        astronaut_1.has_piece = false; //The astronaut isn't carrying anything
                                        break;
                                    }
                                }
                                break;
                            }

                            //This section of the code does the same thing as the section above, except for placing cargo pieces instead of hatches
                            else if (isCollision(astronaut_1.astronaut_image[0], spaceship[j].ship_image) && cargo[i].picked_up){
                                //printf("collision\n");
                                for(int k = 0; k < 3; k++){
                                    if (!spaceship[j].cargo_spots[k] && spaceship[j].panel_spots[k]){
                                        cargo[i].element_image.x = spaceship[j].ship_image.x + 43;
                                        cargo[i].element_image.y = spaceship[j].ship_image.y + 73 + 63*k;
                                        spaceship[j].cargo_spots[k] = true;
                                        cargo[i].placed = true;
                                        cargo[i].picked_up = false;
                                        astronaut_1.has_piece = false;
                                        printf("placed\n");

                                        break;
                                    }
                                }
                                break;
                            }

                        }

                        //This part of the code does the same thing as the above section,
                        //except for placing game pieces on cargo ships instead of spaceships
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
                                        printf("placed\n");
                                        break;
                                    }

                                }
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
                                        printf("placed\n");
                                        break;
                                    }
                                }
                                break;
                            }
                        }


                        //If the astronaut is touching a hatch that isn't on a ship and the astronaut isn't carrying anything, pick up the hatch
                        if (isCollision(astronaut_1.astronaut_image[0], hatches[i].element_image) && !hatches[i].placed && !astronaut_1.has_piece){
                            printf("picking up\n");
                            hatches[i].picked_up = true;
                            astronaut_1.has_piece = true;
                            action_complete = true;
                            break;
                        }
                        
                        //If the astronaut is already carrying a hatch, drop it
                        else if (astronaut_1.has_piece && hatches[i].picked_up){
                            hatches[i].picked_up = false;
                            hatches[i].element_image.y += 15;
                            astronaut_1.has_piece = false;
                            action_complete = true;
                            break;
                        }
                          
                        //If the astronaut is touching a cargo piece that isn't on a ship and the astronaut isn't carrying anything, pick up the cargo piece
                        else if (isCollision(astronaut_1.astronaut_image[0], cargo[i].element_image) && !cargo[i].placed && !astronaut_1.has_piece){
                            printf("picking up\n");
                            cargo[i].picked_up = true;
                            astronaut_1.has_piece = true;
                            action_complete = true;
                            break;
                        }

                        //If the astronaut is already carrying a cargo, drop it
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

      	//When the key has been released, the astronaut's x and y values stop changing
        else if(event.type == ALLEGRO_EVENT_KEY_UP){
            astronaut_1.dx = 0;
            astronaut_1.dy = 0;
            astronaut_1.moving = false;
        }

        //This next section of the code runs every timer click (60 times per second)
        else if(event.type == ALLEGRO_EVENT_TIMER){
            //If the astronaut is still in bounds, its x and y values change by the dx or dy values
            if (check_in_bounds(astronaut_1.astronaut_image)){
                for(int i = 0; i < 12; i++){
                    astronaut_1.astronaut_image[i].x += astronaut_1.dx;
                    astronaut_1.astronaut_image[i].y += astronaut_1.dy;
                }
            }

            //Calculate the boundary boxes of the astronaut frames, the hatch panels and the cargo pieces
            for(int i = 0; i < 12; i++){
                calcBounds(astronaut_1.astronaut_image[i]);
            }
            for(int i = 0; i < numPieces; i++){
                calcBounds(hatches[i].element_image);
                calcBounds(cargo[i].element_image);
            }


            for(int i = 0; i < numPieces; i++){
                //If a hatch is picked up, it moves with the astronaut
                if (hatches[i].picked_up){
                    hatches[i].element_image.x = astronaut_1.astronaut_image[0].x;
                    hatches[i].element_image.y = astronaut_1.astronaut_image[0].y + 10;
                    astronaut_1.has_piece = true;


                    //The x and y values change depending on which direction the astronaut is walking in
                    if (astronaut_1.direction == 1){
                        hatches[i].element_image.x -= 25;
                    }
                    else if(astronaut_1.direction == 3){
                        hatches[i].element_image.x += 25;
                    }
                    else if(astronaut_1.direction == 0){
                        hatches[i].element_image.y += 15;
                    }
                }

                //This section is the same as the previous one, except for cargo.
                //Some of the x and y values are different because the cargo pieces are smaller than hatches
                else if (cargo[i].picked_up){
                    cargo[i].element_image.x = astronaut_1.astronaut_image[0].x + 10;
                    cargo[i].element_image.y = astronaut_1.astronaut_image[0].y + 20;
                    astronaut_1.has_piece = true;

                    if (astronaut_1.direction == 1){
                        cargo[i].element_image.x -= 25;
                    }
                    else if(astronaut_1.direction == 3){
                        cargo[i].element_image.x += 25;
                    }
                    else if(astronaut_1.direction == 0){
                        cargo[i].element_image.y += 15;
                    }
                }
            }

            draw_background();

            //If the game is completed, there is a short rest, then "Level Complete" and the time is displayed.
            if (game_complete){
                al_rest(0.5);
                al_draw_text(font, WHITE, 1380/2, (700/4), ALLEGRO_ALIGN_CENTRE, "Level Completed");
                al_draw_textf(font, WHITE, 1380/2, 700/2, ALLEGRO_ALIGN_CENTER, "Time: %d seconds", (100 - game_clock) );
            }

            //If the game clock reaches 0 and the level hasn't been completed, display the 'game over' message.
            else if (game_clock < 0){
                al_rest(0.5);
                al_draw_multiline_text(font, WHITE, 1380/2, 700/4, 1200, 200, ALLEGRO_ALIGN_CENTER, "You ran out of time Game Over");
            }

            //If the level isn't completed and the timer hasn't run out, display the main game elements
            else{
                //game clock is drawn in the top left corner
                al_draw_textf(font, WHITE, 10, 0, 0, "%d", game_clock);
                //display all the spaceships and cargo ships
                for(int i = 0; i < numSpaceships; i++){
                    draw_image(spaceship[i].ship_image);
                }
                for(int i = 0; i < numCargoShips; i++){
                    draw_image(cargoShip[i].ship_image);
                }

                //If a game piece hasn't been picked up, or it has been picked and the astronaut isn't facing down,
                //the game piece will be drawn behind the astronaut.
                for(int i = 0; i < numPieces; i++){
                    if(!cargo[i].picked_up || (cargo[i].picked_up && astronaut_1.direction != 0)){
                        draw_image(cargo[i].element_image);
                    }
                }

                for(int i = 0; i < numPieces; i++){
                    //The hatches are drawn after the cargo so that they appear in that order when they are placed on a ship
                    if(!hatches[i].picked_up || (hatches[i].picked_up && astronaut_1.direction != 0)){
                        draw_image(hatches[i].element_image);
                    }
                }


                //If the astronaut isn't moving, the frame is set to 0 (standing still frame)
                if (!astronaut_1.moving){
                    astronaut_1.frame = 0;
                }

                drawBoundingBox(astronaut_1.astronaut_image[0]);
                draw_astronaut(astronaut_1.astronaut_image, astronaut_1.frame, astronaut_1.direction);

            
                //If the astronaut is carrying a game piece and facing downwards, the piece is drawn in front of the astronaut
                for(int i = 0; i < numPieces; i++){
                    if(cargo[i].picked_up && astronaut_1.direction == 0){
                        draw_image(cargo[i].element_image);
                    }

                    if(hatches[i].picked_up && astronaut_1.direction == 0){
                        draw_image(hatches[i].element_image);
                    }

                }

                //The frame counter goes up by one every frame and when it gets to 60, it gets set back to 0
                counter ++;
                counter %= 60;
            }

            //If the 3rd hatch and panel spots are filled up on each of the spaceships and cargo ships, the level is completed.
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

            //Every 12 counts (5 times per second), if the astronaut is moving,
            //the frame alternates between 1 and 2 (the two walking frames)
            if(counter%12 == 0){
                if(astronaut_1.moving){
                    astronaut_1.frame = astronaut_1.frame%2 + 1;
                }
            }

            //Every 60 counts (every second), the game clock goes down by one
            if(counter%60 == 0){
                game_clock--;
            }

        }
	}

    // Free up memory taken by display.
    al_destroy_display(display);

    //Free up memory taken by bitmaps
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
