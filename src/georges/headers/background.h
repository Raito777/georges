#ifndef BACKGROUND_h
#define BACKGROUND_h

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_image.h>

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



Cercle createCercle(float x, float y, float radius, ColorRGB color, int z);

Background createBackground(int nbElements, Cercle *cercles);

void updateBackground(Background background, Camera camera);

void afficherCercle(Cercle cercle, Camera camera);

void loadTexture(const char* filename, GLuint textureID[10], int numTexture);
#endif /* BACKGROUND_h */