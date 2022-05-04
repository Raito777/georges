#ifndef PLATEFORME_H
#define PLATEFORME_H


#include "couleurs.h"
#include "joueur.h"

Plateforme creerPlateforme(float x, float y, float largeur, float hauteur, ColorRGB color);

void updatePlateforme(Plateforme *plateforme, Joueur *joueur, float deltaTime);

void afficherPlateforme(Plateforme plateforme);

void deplacerPlateforme(Plateforme *plateforme, Joueur *joueur, float deltaTime);




#endif /* PLATEFORME_H */