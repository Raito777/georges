#ifndef JOUEUR_H
#define JOUEUR_H

#include "couleurs.h"
#include "plateforme.h"

typedef struct Joueur {
    float x;
    float y;
    float largeur;
    float hauteur;
    float vitesse;
    int aFini;
    ColorRGB color;

} Joueur;

Joueur creerJoueur(float x, float y, float largeur, float hauteur, float vitesse, int aFini, ColorRGB color);

void afficherJoueur(Joueur joueur);

bool collision(Joueur joueur, Plateforme plateforme);

void setCouleur(Joueur * joueur, ColorRGB color);

#endif /* JOUEUR_H */