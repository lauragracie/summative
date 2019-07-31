/*
This program initializes all the allegro add ons, including the display, event queue, timer, font, keyboard mouse etc.
The allegro_innitiaize function that is declared here gets called in main.cpp
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "setup.h"
#include <stdio.h>

//These Allegro add ons are initialized in main.cpp
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_FONT *font;
extern ALLEGRO_FONT *font_small;

int SCREEN_W  = 1380;       // screen width
int SCREEN_H = 700;         // screen hight
float FPS = 60.0;           // Frames per second

int allegro_innitialize() {

    // Initialize image add on
    if (!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error",
            "Failed to initialize image addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //Initialize display
    display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    al_set_window_title(display, "Laura Gracie Allegro Summative");

    // Initialize keyboard routines
	if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	return -1;
   	}

   	// Initialize mouse routines
   	if(!al_install_mouse()){
        al_show_native_message_box(display, "Error", "Error", "failed to initialize the mouse!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	return -1;
   	}

    // Initialize event queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}

	//Initialize timer
    timer = al_create_timer(1.0 / FPS);
   	if (!timer) {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer(movement)!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //Initialize Allegro primitives
    if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	//Initialize font add on
    if (!al_init_font_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize font addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	//Initialize True Type Font add on
    if (!al_init_ttf_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize True Type Font addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	//Initialize two space age fonts of two different sizes
    font = al_load_ttf_font("Font/space age.ttf", 72, 0);
    font_small = al_load_ttf_font("Font/space age.ttf", 40, 0);

    if (!font){
        al_show_native_message_box(display, "Error", "Error", "Could not load space age.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //Register events from the display, keyboard, timer and mouse
    al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    return 0;
}
