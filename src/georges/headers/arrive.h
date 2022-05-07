#ifndef ARRIVE_H
#define ARRIVE_H

#include "couleurs.h"
#include "joueur.h"
#include "level.h"


Arrive creerArrive(float x, float y, float largeur, float hauteur, int id, ColorRGB color);

void updateArrive(Arrive *arrive, Joueur *joueur, Level *level);

void afficherArrive(Arrive arrive);

void verifierJoueur(Arrive *arrive, Joueur *joueur, Level *level);

bool collisionArrive(Joueur joueur, Arrive arrive);

#endif /* ARRIVE_H */