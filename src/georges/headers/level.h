#ifndef LEVEL_H
#define LEVEL_H

#include "couleurs.h"
#include "joueur.h"

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
    bool isJumping;
    bool isMooving;
    bool isCollidingPlateforme;
    bool isCollidingPlayer;
    int nbSaut;
    int nbSautMax;
    int id;
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

typedef struct Arrive {
    
    float x;
    float y;
    float largeur;
    float hauteur;
    int id;
    bool aFini;
    ColorRGB color;

} Arrive;

typedef struct Level {
    
    int taille;
    int nbJoueurs;
    Plateforme* lvl;
    Joueur* joueurs;
    Arrive* arrives;
    char *nom;
    ColorRGB backgroundColor;
    float scale;
    float transitionY;


} Level;

Level creerLevel(int taille, int nbJoueurs, Plateforme plateforme[], Joueur joueurs[], Arrive arrives[], char *nom, ColorRGB backgroundColor, float scale);

void switchJoueur(Level * level);

void supprimerJoueur(Level * level);

bool verifieVictoire(Level level);

void afficherBackground(Level level, int width, int height);

void afficherTransitionIn(int width, int height, Level* level, float deltaTime);

#endif /* LEVEL_H */