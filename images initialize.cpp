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
extern astronaut astronaut_1;
extern astronaut astronaut_2;
extern game_peice hatches[numPieces];
extern game_peice cargo[numPieces];

void calcBounds(Image &a);

int images_innitialize() {

    background = al_load_bitmap("Images/Moon background.jpg");
    if (!background) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (background)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }


    for(int i = 0; i < numSpaceships; i++){
        spaceship[i].ship_image.bitmap = al_load_bitmap("Images/spaceship.png");
        al_convert_mask_to_alpha(spaceship[i].ship_image.bitmap, WHITE);
        spaceship[i].ship_image.x = 320 + 400*i;
        spaceship[i].ship_image.y = 150;
        calcBounds(spaceship[i].ship_image);
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

    for(int i = 0; i < numCargoShips; i++){
        cargoShip[i].ship_image.bitmap = al_load_bitmap("Images/cargo ship.png");
        al_convert_mask_to_alpha(cargoShip[i].ship_image.bitmap, WHITE);
        cargoShip[i].ship_image.x = 500 + 400*i;
        cargoShip[i].ship_image.y = 550;
        calcBounds(cargoShip[i].ship_image);
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

    astronaut_1.astronaut_image[0].bitmap = al_load_bitmap("Images/astronaut_front_1.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[0].bitmap , WHITE);
    calcBounds(astronaut_1.astronaut_image[0]);
    if (!astronaut_1.astronaut_image[0].bitmap ) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }

    astronaut_1.astronaut_image[1].bitmap  = al_load_bitmap("Images/astronaut_front_2.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[1].bitmap , WHITE);
    calcBounds(astronaut_1.astronaut_image[1]);
    if (!astronaut_1.astronaut_image[1].bitmap ) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }

    astronaut_1.astronaut_image[2].bitmap = al_load_bitmap("Images/astronaut_front_3.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[2].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[2]);
    if (!astronaut_1.astronaut_image[2].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_1.astronaut_image[3].bitmap = al_load_bitmap("Images/astronaut_left_1.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[3].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[3]);
    if (!astronaut_1.astronaut_image[3].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_1.astronaut_image[4].bitmap = al_load_bitmap("Images/astronaut_left_2.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[4].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[4]);
    if (!astronaut_1.astronaut_image[4].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }


    astronaut_1.astronaut_image[5].bitmap = al_load_bitmap("Images/astronaut_left_3.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[5].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[5]);
    if (!astronaut_1.astronaut_image[5].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_1.astronaut_image[6].bitmap = al_load_bitmap("Images/astronaut_back_1.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[6].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[6]);
    if (!astronaut_1.astronaut_image[6].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_1.astronaut_image[7].bitmap = al_load_bitmap("Images/astronaut_back_2.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[7].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[7]);
    if (!astronaut_1.astronaut_image[7].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_1.astronaut_image[8].bitmap = al_load_bitmap("Images/astronaut_back_3.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[8].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[8]);
    if (!astronaut_1.astronaut_image[8].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_1.astronaut_image[9].bitmap = al_load_bitmap("Images/astronaut_right_1.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[9].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[9]);
    if (!astronaut_1.astronaut_image[9].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_right_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut_1.astronaut_image[10].bitmap = al_load_bitmap("Images/astronaut_right_2.png");
    al_convert_mask_to_alpha(astronaut_1.astronaut_image[10].bitmap, WHITE);
    calcBounds(astronaut_1.astronaut_image[10]);
    if (!astronaut_1.astronaut_image[10].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

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
    for(int i = 0; i < numPieces; i++){
        hatches[i].element_image.bitmap = al_load_bitmap("Images/hatch panel.png");
        al_convert_mask_to_alpha(hatches[i].element_image.bitmap, WHITE);
        hatches[i].element_image.x= 500 + 25*i;
        hatches[i].element_image.y = 300 + 25*i;
        calcBounds(hatches[i].element_image);
        hatches[i].picked_up = false;
        hatches[i].placed = false;
        //hatches[i].ship_placed = 0;

        if (!hatches[i].element_image.bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image (hatch)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -1;
        }
    }


    for(int i = 0; i < numPieces; i++){
        cargo[i].element_image.bitmap = al_load_bitmap("Images/cargo.png");
        al_convert_mask_to_alpha(cargo[i].element_image.bitmap, WHITE);
        cargo[i].element_image.x= 200 + 50*i;
        cargo[i].element_image.y = 600;
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
