#ifndef BACKGROUND_h
#define BACKGROUND_h

#include "couleurs.h"
#include "joueur.h"

typedef struct Cercle {
    
    float x;
    float y;
    float z;
    float radius;
    ColorRGB color;

} Cercle;

typedef struct Background {
    
    int nbElements;
    Cercle *cercles;

} Background;



Cercle createCercle(float x, float y, float radius, ColorRGB color);

Background createBackground(int nbElements, Cercle *cercles);

void updateBackground(Background background, Camera camera);

void afficherCercle(Cercle cercle, Camera camera);
#endif /* BACKGROUND_h */