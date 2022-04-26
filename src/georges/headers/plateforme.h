#ifndef PLATEFORME_H
#define PLATEFORME_H

#include "couleurs.h"

typedef struct Plateforme {
    float x;
    float y;
    float largeur;
    float hauteur;
    float velocite;
    float acceleration;
    ColorRGB color;

} Plateforme;

Plateforme creerPlateforme(float x, float y, float largeur, float hauteur, float velocite, float acceleration, ColorRGB color);

void updatePlateforme(Plateforme *plateforme);

void afficherPlateforme(Plateforme plateforme);

void deplacerPlateforme(Plateforme *plateforme);

void setVelocite(Plateforme *plateforme, float velocite);

void resetVelocite(Plateforme *plateforme, float step);

#endif /* PLATEFORME_H */