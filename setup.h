#define SETUP_H_INCLUDED

struct Image {
    ALLEGRO_BITMAP *bitmap;               // picture
    int x, y;                             // position on screen
    int bbRight, bbLeft, bbTop, bbBottom; // boundary box
};

#define WHITE al_map_rgb(255,255,255)

#ifdef SETUP_H_INCLUDED

#endif // SETUP_H_INCLUDED
