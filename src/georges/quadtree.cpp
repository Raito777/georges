#include <SDL2/SDL.h>
//#include "fakesdlimage.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <random>

#include "headers/couleurs.h"
#include "headers/systeme.h"
#include "headers/background.h"

#include "headers/quadtree.h"

QuadTree creerQuadTree(float x, float y, float width, float height, Plateforme* listePlateformes, int nbPlateforme)
{
    QuadTree quadTree;
    (quadTree).x = x;
    (quadTree).y = y;
    (quadTree).largeur = width;
    (quadTree).hauteur = height;
    (quadTree).plateformes = listePlateformes;
    (quadTree).nbPlateforme = nbPlateforme;
    (quadTree).isLeaf = 1;

    return quadTree;
}

void splitQuadTree(QuadTree* quadTree){
    float newLargeur = (*quadTree).largeur/2;
    float newHauteur = (*quadTree).hauteur/2;

    QuadTree hautGauche = creerQuadTree((*quadTree).x-(*quadTree).x/2, (*quadTree).y+(*quadTree).y/2, newLargeur, newHauteur, (*quadTree).plateformes, (*quadTree).nbPlateforme);
    QuadTree hautDroite = creerQuadTree((*quadTree).x+(*quadTree).x/2, (*quadTree).y+(*quadTree).y/2, newLargeur, newHauteur, (*quadTree).plateformes, (*quadTree).nbPlateforme);
    QuadTree basGauche = creerQuadTree((*quadTree).x-(*quadTree).x/2, (*quadTree).y-(*quadTree).y/2, newLargeur, newHauteur, (*quadTree).plateformes, (*quadTree).nbPlateforme);
    QuadTree basDroite = creerQuadTree((*quadTree).x+(*quadTree).x/2, (*quadTree).y-(*quadTree).y/2, newLargeur, newHauteur, (*quadTree).plateformes, (*quadTree).nbPlateforme);

    QuadTree nodes[4] = {hautGauche, hautDroite, basGauche, basDroite};
    
    afficherQuadTree(hautGauche);
    afficherQuadTree(hautDroite);
    afficherQuadTree(basGauche);
    afficherQuadTree(basDroite);

};

void checkQuadtreeZone(QuadTree* quadTree, Joueur joueur){

    

}



void afficherQuadTree(QuadTree quadTree){


            glPushMatrix();

                glTranslated(quadTree.x,quadTree.y,0);

                glPushMatrix();

                    glScalef(quadTree.largeur,quadTree.hauteur,0);

                    glColor3f(0.5,0.5,0.5);
                    
                    drawSquare(0);
                    
                glPopMatrix();

            glPopMatrix();
        



}

