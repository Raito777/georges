#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>
#include <vector>

#include "level.h"

#define MAX_CUBE_COUNT 100  
#define MAX_CUBE_COUNT_PER_NODE 4

typedef struct QuadTree {

    float x;
    float y;
    float largeur;
    float hauteur;
    QuadTree* nodes;
    Plateforme* plateformes;
    int nbPlateforme;
    int isLeaf;

} QuadTree;

QuadTree creerQuadTree(float x, float y, float width, float height, Plateforme* listePlateformes, int nbPlateforme);

void afficherQuadTree(QuadTree QuadTree);

void splitQuadTree(QuadTree* quadTree);

int checkQuadTreeCollision(float largeur, float hauteur, float x, float y, QuadTree quadTree);

void checkQuadtreeZone(QuadTree* quadTree, Joueur joueur);

void findPlayerQuadTree(QuadTree* quadTree, Joueur player, std::vector<QuadTree*> &playerQuadTree);

#endif