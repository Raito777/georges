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

} QuadTree;

QuadTree creerQuadTree(float x, float y, float width, float height, Plateforme* listePlateformes, int nbPlateforme);

void afficherQuadTree(QuadTree QuadTree);

void splitQuadTree(QuadTree* quadTree);

int checkQuadTreeCollision(float largeur, float hauteur, float x, float y, QuadTree quadTree);

int donnerZoneQuadTree(QuadTree quadtree, Plateforme plateforme);

bool estFeuille(QuadTree quadTree);

void insererQuadTree(QuadTree* quadtree);

void insererPlateforme(QuadTree* quadtree);

void findPlayerQuadTree(QuadTree* quadTree, Joueur player, std::vector<QuadTree*> &playerQuadTree);

#endif