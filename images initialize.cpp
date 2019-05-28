#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "setup.h"
#include <stdio.h>


extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *background;
extern ship spaceship[numSpaceships];
extern Image astronaut[12];
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


    astronaut[0].bitmap = al_load_bitmap("Images/astronaut_front_1.png");
    al_convert_mask_to_alpha(astronaut[0].bitmap , WHITE);
    calcBounds(astronaut[0]);
    if (!astronaut[0].bitmap ) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }

    astronaut[1].bitmap  = al_load_bitmap("Images/astronaut_front_2.png");
    al_convert_mask_to_alpha(astronaut[1].bitmap , WHITE);
    calcBounds(astronaut[1]);
    if (!astronaut[1].bitmap ) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
	 }

    astronaut[2].bitmap = al_load_bitmap("Images/astronaut_front_3.png");
    al_convert_mask_to_alpha(astronaut[2].bitmap , WHITE);
    calcBounds(astronaut[2]);
    if (!astronaut[2].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_front_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut[3].bitmap = al_load_bitmap("Images/astronaut_left_1.png");
    al_convert_mask_to_alpha(astronaut[3].bitmap, WHITE);
    calcBounds(astronaut[3]);
    if (!astronaut[3].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut[4].bitmap = al_load_bitmap("Images/astronaut_left_2.png");
    al_convert_mask_to_alpha(astronaut[4].bitmap, WHITE);
    calcBounds(astronaut[4]);
    if (!astronaut[4].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }


    astronaut[5].bitmap = al_load_bitmap("Images/astronaut_left_3.png");
    al_convert_mask_to_alpha(astronaut[5].bitmap, WHITE);
    calcBounds(astronaut[5]);
    if (!astronaut[5].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut[6].bitmap = al_load_bitmap("Images/astronaut_back_1.png");
    al_convert_mask_to_alpha(astronaut[6].bitmap, WHITE);
    calcBounds(astronaut[6]);
    if (!astronaut[6].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut[7].bitmap = al_load_bitmap("Images/astronaut_back_2.png");
    al_convert_mask_to_alpha(astronaut[7].bitmap, WHITE);
    calcBounds(astronaut[7]);
    if (!astronaut[7].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut[8].bitmap = al_load_bitmap("Images/astronaut_back_3.png");
    al_convert_mask_to_alpha(astronaut[8].bitmap, WHITE);
    calcBounds(astronaut[8]);
    if (!astronaut[8].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_back_3)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut[9].bitmap = al_load_bitmap("Images/astronaut_right_1.png");
    al_convert_mask_to_alpha(astronaut[9].bitmap, WHITE);
    calcBounds(astronaut[9]);
    if (!astronaut[9].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_right_1)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut[10].bitmap = al_load_bitmap("Images/astronaut_right_2.png");
    al_convert_mask_to_alpha(astronaut[10].bitmap, WHITE);
    calcBounds(astronaut[10]);
    if (!astronaut[10].bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image (astronaut_left_2)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -1;
    }

    astronaut[11].bitmap = al_load_bitmap("Images/astronaut_right_3.png");
    al_convert_mask_to_alpha(astronaut[11].bitmap, WHITE);
    calcBounds(astronaut[11]);
    if (!astronaut[11].bitmap) {
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
