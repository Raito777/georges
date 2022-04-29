#ifndef JOUEUR_H
#define JOUEUR_H

#include "couleurs.h"
#include "plateforme.h"

typedef struct Joueur {
    float x;
    float y;
    float largeur;
    float hauteur;
    float velociteSaut;
    float hauteurSaut;
    int nbSaut;
    int nbSautMax;
    int aFini;
    ColorRGB color;

} Joueur;

Joueur creerJoueur(float x, float y, float largeur, float hauteur, float velociteSaut, int aFini, ColorRGB color);

void afficherJoueur(Joueur joueur);

bool collision(Joueur joueur, Plateforme plateforme);

void setCouleur(Joueur * joueur, ColorRGB color);

void gravite(Plateforme *plateforme, Joueur *unJoueur, float deltaTme);

void saut(Joueur *unJoueur, float deltaTime);

void updateJoueur(Joueur * joueur, Plateforme * plateforme, float deltaTime);

void setvelociteSaut(Joueur *joueur);

#endif /* JOUEUR_H */