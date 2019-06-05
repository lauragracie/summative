#define SETUP_H_INCLUDED

struct Image {
    ALLEGRO_BITMAP *bitmap;               // picture
    int x, y;                             // position on screen
    int bbRight, bbLeft, bbTop, bbBottom; // boundary box
};

struct game_peice{
    Image element_image;
    bool picked_up;
    bool placed;
    //int ship_placed;
};

struct ship{
    Image ship_image;
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
#define numPieces 9
#define numSpaceships 2
#define numCargoShips 1

#ifdef SETUP_H_INCLUDED

#endif // SETUP_H_INCLUDED
