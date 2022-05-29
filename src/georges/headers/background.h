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



Cercle createCercle(float x, float y, float radius, ColorRGB color);

Background createBackground(int nbElements, Cercle *cercles);

void updateBackground(Background background, Camera camera);

void afficherCercle(Cercle cercle, Camera camera);

GLuint loadTexture(const char* filename);

void drawTexture(float weight, float height, float x, float y,char* adresse);

#endif /* BACKGROUND_h */