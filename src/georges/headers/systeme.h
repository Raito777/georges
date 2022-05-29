#ifndef SYSTEME_H
#define SYSTEME_H


#include "joueur.h"
#include "plateforme.h"
#include "level.h"

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "Georges was alone";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 150.;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

static const int CIRCLE_SUBDIVS = 2<<5;

void drawCircle(int filled);

void drawSquare(int filled);

void drawTriangle(int filled);

void checkEvenements(int *gameLoop, Joueur *joueur, Level level, float deltaTime);

void onWindowResized(unsigned int width, unsigned int height);

void checkMenu(int* gameLoop, int* phase, int* etat);


#endif /* SYSTEME_H */