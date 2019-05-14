#define SETUP_H_INCLUDED

struct Image {
    ALLEGRO_BITMAP *bitmap;               // picture
    int x, y;                             // position on screen
    int bbRight, bbLeft, bbTop, bbBottom; // boundary box
};

#ifdef SETUP_H_INCLUDED

#endif // SETUP_H_INCLUDED
