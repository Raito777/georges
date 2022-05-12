#ifndef JOUEUR_H
#define JOUEUR_H

#include "couleurs.h"
#include "level.h"

Joueur creerJoueur(float x, float y, float largeur, float hauteur, int id, ColorRGB color);

Camera creerCamera(float x, float y);

void updateCamera(Camera *camera, Joueur *joueur);

void afficherJoueur(Joueur joueur, Level level);

bool collision(Joueur joueur, Plateforme plateforme);

bool collisionJoueur(Joueur joueur1, Joueur joueur2);

bool collisionJoueurHaut(Joueur joueur, Joueur joueur1);

bool collisionJoueurBas(Joueur joueur, Joueur joueur1);

bool collisionJoueurX(Joueur joueur, Joueur joueur1);

bool collisionX(Joueur joueur, Plateforme plateforme);

bool collisionHaut(Joueur joueur, Plateforme plateforme);

bool collisionBas(Joueur joueur, Plateforme plateforme);

void setVelocite(Joueur *joueur, float velocite);

void resetVelocite(Joueur *joueur, float step);

void deplacerJoueur(Joueur *joueur, float deltaTime);

void setCouleur(Joueur * joueur, ColorRGB color);

void gravite(Joueur *unJoueur, float deltaTme);

void checkCollision(Level * level, float deltaTime);

void checkCollisionJoueur(Joueur *joueur, Joueur *joueur1, float deltaTime);

void saut(Joueur *unJoueur, float deltaTime);

void updateJoueur(Joueur * joueur, Camera * camera, float deltaTime);

void setvelociteSaut(Joueur *joueur, float step);

void respawn(Joueur *joueur);

void cameraTranslate(Camera camera);

#endif /* JOUEUR_H */