/*
This program initializes all the images used in the code. It also defines the x and y coordinates for the images
and calculates their boundary boxes. The image_initialize function is defined here and called in main.cpp
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "setup.h"
#include <stdio.h>


extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *background;
extern ship spaceship[numSpaceships];
extern ship cargoShip[numCargoShips];
extern Image logo;
extern Image logo_background;
extern astronaut astronaut_1;
extern astronaut astronaut_2;
extern game_peice hatches[numPieces];
extern game_peice cargo[numPieces];

void calcBounds(Image &a);


int images_innitialize() {

    //Load the background image
    background = al_load_bitmap("Images/Moon background.jpg");
    if (!background) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (background)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    //Load the logo image
    logo.bitmap = al_load_bitmap("Images/logo.jpg");
    logo.x = 0;
    logo.y = 0;
    if (!logo.bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (logo)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }

	 //Load the logo_background image
	 logo_background.bitmap = al_load_bitmap("Images/logo_background.png");
	 logo_background.x = 0;
	 logo_background.y = 0;
	 if (!logo_background.bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (logo_background)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }

    //Load the spaceship images
    for(int i = 0; i < numSpaceships; i++){
        spaceship[i].ship_image.bitmap = al_load_bitmap("Images/spaceship.png");
        al_convert_mask_to_alpha(spaceship[i].ship_image.bitmap, WHITE);
        //Every spaceship will be drawn in a different spot
        spaceship[i].ship_image.x = 320 + 400*i;
        spaceship[i].ship_image.y = 150;
        calcBounds(spaceship[i].ship_image);

        //The panel/cargo spots for each of the spaceships are set to false
        for(int j = 0; j < 3; j++){
            spaceship[i].panel_spots[j] = false;
            spaceship[i].cargo_spots[j] = false;
        }

        if (!spaceship[i].ship_image.bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image (spaceship)!",
                                     nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -1;
        }
    }

    //Load the cargo ships images
    for(int i = 0; i < numCargoShips; i++){
        cargoShip[i].ship_image.bitmap = al_load_bitmap("Images/cargo ship.png");
        al_convert_mask_to_alpha(cargoShip[i].ship_image.bitmap, WHITE);
        //Every cargo ship will be drawn in a different spot
        cargoShip[i].ship_image.x = 500;
        cargoShip[i].ship_image.y = 550;
        calcBounds(cargoShip[i].ship_image);

        //The panel/cargo spots for each of the spaceships are set to false
        for(int j = 0; j < 3; j++){
            cargoShip[i].panel_spots[j] = false;
            cargoShip[i].cargo_spots[j] = false;
        }

        if (!cargoShip[i].ship_image.bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image (cargoShip)!",
                                     nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -1;
        }
    }

    //Load the bitmaps for all 12 of the astronaut sprites

    //Facing front, standing still astronaut sprite

    astronaut_1.astronaut_image[0].bitmap = al_load_bitmap("Images/astronaut_front_1.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[0].bitmap , WHITE);
    calcBounds(astronaut_1.astronaut_image[0]);
    if (!astronaut_1.astronaut_image[0].bitmap ) 
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }


    //Facing front, walking pose 1 astronaut sprite
    astronaut_1.astronaut_image[1].bitmap  = al_load_bitmap("Images/astronaut_front_2.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[1].bitmap , WHITE);
    calcBounds(astronaut_1.astronaut_image[1]);
    if (!astronaut_1.astronaut_image[1].bitmap ) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }

    //Facing front, walking pose 2 astronaut sprite
    astronaut_1.astronaut_image[2].bitmap = al_load_bitmap("Images/astronaut_front_3.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[2].bitmap , WHITE);
    calcBounds(astronaut_1.astronaut_image[2]);
    if (!astronaut_1.astronaut_image[2].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    //Facing left, standing still astronaut sprite
    astronaut_1.astronaut_image[3].bitmap = al_load_bitmap("Images/astronaut_left_1.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[3].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[3]);
    if (!astronaut_1.astronaut_image[3].bitmap) {
		    al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    //Facing left, walking pose 1 astronaut sprite  
    astronaut_1.astronaut_image[4].bitmap = al_load_bitmap("Images/astronaut_left_2.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[4].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[4]);
    if (!astronaut_1.astronaut_image[4].bitmap) {
		    al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }


    //Facing left, walking pose 2 astronaut sprite
    astronaut_1.astronaut_image[5].bitmap = al_load_bitmap("Images/astronaut_left_3.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[5].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[5]);
    if (!astronaut_1.astronaut_image[5].bitmap) {
      	al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    //Facing back, standing still astronaut sprite
    astronaut_1.astronaut_image[6].bitmap = al_load_bitmap("Images/astronaut_back_1.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[6].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[6]);
    if (!astronaut_1.astronaut_image[6].bitmap) {
    		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    //Facing back, walking pose 1 astronaut sprite
    astronaut_1.astronaut_image[7].bitmap = al_load_bitmap("Images/astronaut_back_2.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[7].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[7]);
    if (!astronaut_1.astronaut_image[7].bitmap) {
    		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    //Facing back, walking pose 2 astronaut sprite
    astronaut_1.astronaut_image[8].bitmap = al_load_bitmap("Images/astronaut_back_3.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[8].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[8]);
    if (!astronaut_1.astronaut_image[8].bitmap) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    //Facing right, standing still astronaut sprite
    astronaut_1.astronaut_image[9].bitmap = al_load_bitmap("Images/astronaut_right_1.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[9].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[9]);
    if (!astronaut_1.astronaut_image[9].bitmap) {
    		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_right_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }


    //Facing right, walking pose 1 astronaut sprite
    astronaut_1.astronaut_image[10].bitmap = al_load_bitmap("Images/astronaut_right_2.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[10].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[10]);
    if (!astronaut_1.astronaut_image[10].bitmap) {
    		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    //Facing right, walking pose 2 astronaut sprite
    astronaut_1.astronaut_image[11].bitmap = al_load_bitmap("Images/astronaut_right_3.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[11].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[11]);
    if (!astronaut_1.astronaut_image[11].bitmap) {
    		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }


    // Astronaut #2
        astronaut_2.astronaut_image[0].bitmap = al_load_bitmap("Images/astronaut_front_1.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[0].bitmap , WHITE);
    calcBounds(astronaut_2.astronaut_image[0]);
    if (!astronaut_2.astronaut_image[0].bitmap ) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }

    astronaut_2.astronaut_image[1].bitmap  = al_load_bitmap("Images/astronaut_front_2.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[1].bitmap , WHITE);
    calcBounds(astronaut_2.astronaut_image[1]);
    if (!astronaut_2.astronaut_image[1].bitmap ) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }

    astronaut_2.astronaut_image[2].bitmap = al_load_bitmap("Images/astronaut_front_3.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[2].bitmap , WHITE);
    calcBounds(astronaut_2.astronaut_image[2]);
    if (!astronaut_2.astronaut_image[2].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_2.astronaut_image[3].bitmap = al_load_bitmap("Images/astronaut_left_1.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[3].bitmap, WHITE);
    calcBounds(astronaut_2.astronaut_image[3]);
    if (!astronaut_2.astronaut_image[3].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_2.astronaut_image[4].bitmap = al_load_bitmap("Images/astronaut_left_2.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[4].bitmap, WHITE);
    calcBounds(astronaut_2.astronaut_image[4]);
    if (!astronaut_2.astronaut_image[4].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }


    astronaut_2.astronaut_image[5].bitmap = al_load_bitmap("Images/astronaut_left_3.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[5].bitmap, WHITE);
    calcBounds(astronaut_2.astronaut_image[5]);
    if (!astronaut_2.astronaut_image[5].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_2.astronaut_image[6].bitmap = al_load_bitmap("Images/astronaut_back_1.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[6].bitmap, WHITE);
    calcBounds(astronaut_2.astronaut_image[6]);
    if (!astronaut_2.astronaut_image[6].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_2.astronaut_image[7].bitmap = al_load_bitmap("Images/astronaut_back_2.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[7].bitmap, WHITE);
    calcBounds(astronaut_2.astronaut_image[7]);
    if (!astronaut_2.astronaut_image[7].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_2.astronaut_image[8].bitmap = al_load_bitmap("Images/astronaut_back_3.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[8].bitmap, WHITE);
    calcBounds(astronaut_2.astronaut_image[8]);
    if (!astronaut_2.astronaut_image[8].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_2.astronaut_image[9].bitmap = al_load_bitmap("Images/astronaut_right_1.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[9].bitmap, WHITE);
    calcBounds(astronaut_2.astronaut_image[9]);
    if (!astronaut_2.astronaut_image[9].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_right_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_2.astronaut_image[10].bitmap = al_load_bitmap("Images/astronaut_right_2.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[10].bitmap, WHITE);
    calcBounds(astronaut_2.astronaut_image[10]);
    if (!astronaut_2.astronaut_image[10].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_2.astronaut_image[11].bitmap = al_load_bitmap("Images/astronaut_right_3.png");
    al_convert_mask_to_alpha(astronaut_2.astronaut_image[11].bitmap, WHITE);
    calcBounds(astronaut_2.astronaut_image[11]);
    if (!astronaut_2.astronaut_image[11].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    //Load the images for all the hatch panels. Each panel has differnt x and y coordinates, each stored in the array
    int hatch_starting_spots[9][2] {{300,100},{150,300},{250,550},{500,350},{600,200},{650,500},{900,70},{1000,600},{1070,350}};
    for(int i = 0; i < numPieces; i++){
        hatches[i].element_image.bitmap = al_load_bitmap("Images/hatch panel.png");
        al_convert_mask_to_alpha(hatches[i].element_image.bitmap, WHITE);
        hatches[i].element_image.x= hatch_starting_spots[i][0];
        hatches[i].element_image.y = hatch_starting_spots[i][1];
        calcBounds(hatches[i].element_image);
        hatches[i].picked_up = false;
        hatches[i].placed = false;

        if (!hatches[i].element_image.bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image (hatch)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -1;
        }
    }

    //Load the images for all the cargo pieces. Each cargo has differnt x and y coordinates, each stored in the array
    int cargo_starting_spots[9][2] {{145,314},{94,163},{673,106},{1290,171},{854,167},{647,388},{991,206},{193,277},{237,444}};
    for(int i = 0; i < numPieces; i++){
        cargo[i].element_image.bitmap = al_load_bitmap("Images/cargo.png");
        al_convert_mask_to_alpha(cargo[i].element_image.bitmap, WHITE);
        cargo[i].element_image.x= cargo_starting_spots[i][0];
        cargo[i].element_image.y = cargo_starting_spots[i][1];
        calcBounds(cargo[i].element_image);
        cargo[i].picked_up = false;
        cargo[i].placed = false;

        if (!cargo[i].element_image.bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image (cargo)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -1;
        }
    }


    return 0;
}
