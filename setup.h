#define SETUP_H_INCLUDED

//Structure to store data on an image
struct Image {
    ALLEGRO_BITMAP *bitmap;               // picture
    int x, y;                             // position on screen
    int bbRight, bbLeft, bbTop, bbBottom; // boundary box
};


struct astronaut{
    Image astronaut_image[12];
    int dx;
    int dy;
    int x;
    int y;
    int frame;
    int direction;
    bool moving;
    bool has_piece;
};

//Structure to store data on game pieces (hatches and cargo)

struct game_peice{
    Image element_image; //The image of the cargo/hatch
    bool picked_up; //If the game piece is being carried by the astronaut
    bool placed; //If the game piece is placed on a spaceship/cargo ship
};

//Structure to store data on ships (spaceships and cargo ships)
struct ship{
    Image ship_image; //The image of the spaceship/cargo ship

    //Each boolean in the array represents a spot where a game piece can be placed. Is becomes true when a piece is placed there
    bool panel_spots[3];
    bool cargo_spots[3];
};


/*struct level{
    int game_clock;
    int numPieces;
    int numCargoShips;
    int numSpaceships;
    int hatches_x[numPieces];
    int hatches_y[numPieces];
    int cargo_x[numPieces];
    int cargo_y[numPieces];
    int cargoShip_x[numCargoShips];
    int cargoShip_y[numCargoShips];
    int spaceship_x[numSpaceships];
    int spaceship_y[numSpaceships];
};*/

#define WHITE al_map_rgb(255,255,255)

//Macro definitions for the number of hatches, cargo pieces, spaceships, and cargo ships
//These variables are used throughout the code, so it's very easy to change how many elements you want to be displayed.
#define numPieces 9
#define numSpaceships 2
#define numCargoShips 0

#ifdef SETUP_H_INCLUDED

#endif // SETUP_H_INCLUDED
