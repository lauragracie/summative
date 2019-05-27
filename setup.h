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

#define WHITE al_map_rgb(255,255,255)
#define numPieces 6
#define numSpaceships 2

#ifdef SETUP_H_INCLUDED

#endif // SETUP_H_INCLUDED
