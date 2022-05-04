#ifndef JOUEUR_H
#define JOUEUR_H

#include "couleurs.h"


typedef struct Joueur {
    
    float x;
    float y;
    float originX;
    float originY;
    float oldX;
    float oldY;
    float largeur;
    float hauteur;
    float velocite;
    float acceleration;
    float velociteSaut;
    float hauteurSaut;
    int nbSaut;
    int nbSautMax;
    int aFini;
    ColorRGB color;

} Joueur;

typedef struct Plateforme {
    float x;
    float y;
    float largeur;
    float hauteur;
    ColorRGB color;

} Plateforme;

typedef struct Camera {

    float x;
    float y;

} Camera;

Joueur creerJoueur(float x, float y, float largeur, float hauteur, ColorRGB color);

Camera creerCamera(float x, float y);

void updateCamera(Camera *camera, Joueur *joueur);

void afficherJoueur(Joueur joueur);

bool collision(Joueur joueur, Plateforme plateforme);

bool collisionX(Joueur joueur, Plateforme plateforme);

bool collisionHaut(Joueur joueur, Plateforme plateforme);

bool collisionBas(Joueur joueur, Plateforme plateforme);

void setVelocite(Joueur *joueur, float velocite);

void resetVelocite(Joueur *joueur, float step);

void deplacerJoueur(Joueur *joueur, float deltaTime);

void setCouleur(Joueur * joueur, ColorRGB color);

void gravite(Joueur *unJoueur, float deltaTme);

void checkCollision(Plateforme *plateforme, Joueur *joueur, float deltaTime);

void saut(Joueur *unJoueur, float deltaTime);

void updateJoueur(Joueur * joueur, Camera * camera, float deltaTime);

void setvelociteSaut(Joueur *joueur, bool * isJumping);

void respawn(Joueur *joueur);

void cameraTranslate(Camera camera);

#endif /* JOUEUR_H */