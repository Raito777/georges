#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>
#include <vector>

#include "level.h"

typedef struct QuadTree {

    float x;
    float y;
    float largeur;
    float hauteur;
    QuadTree* nodes;
    Plateforme* plateformes;
    int nbPlateforme;
    int isLeaf;
    int nbMaxPlateformes;
    int id;

} QuadTree;

QuadTree creerQuadTree(float x, float y, float width, float height, Plateforme* listePlateformes, int nbPlateforme, int nbMaxPlateformes, int id);

void afficherQuadTree(QuadTree QuadTree);

void drawQuadTree(QuadTree quadtree);

void splitQuadTree(QuadTree* quadTree);

int checkQuadTreeCollision(float largeur, float hauteur, float x, float y, QuadTree quadTree);

bool estDansQuadTree(QuadTree quadtree, Plateforme plateforme);

bool contientJoueur(QuadTree quadtree, Joueur plateforme);

void insererNoeud(QuadTree* quadtree);

void insererPlateforme(QuadTree* quadtree, Plateforme plateforme, int index);

QuadTree *chercherPlateforme(QuadTree &quadtree, Joueur joueur);

#endif