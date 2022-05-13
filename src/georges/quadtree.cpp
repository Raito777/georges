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
    (quadTree).plateformes = new Plateforme[200];
    (quadTree).nbPlateforme = 0;
    (quadTree).isLeaf = 1;
    (quadTree).nbMaxPlateformes = 4;


    return quadTree;
}

void splitQuadTree(QuadTree* quadTree){
    float newLargeur = (*quadTree).largeur/2;
    float newHauteur = (*quadTree).hauteur/2;
    float demiLargeur = (*quadTree).x/2;
    float demiHauteur = (*quadTree).y/2;

    printf("nb plateformes %d", (*quadTree).nbPlateforme);

    QuadTree hautGauche = creerQuadTree((*quadTree).x-demiLargeur, (*quadTree).y+demiHauteur, newLargeur, newHauteur, new Plateforme[(*quadTree).nbPlateforme], 0);
    QuadTree hautDroite = creerQuadTree((*quadTree).x+demiLargeur, (*quadTree).y+demiHauteur, newLargeur, newHauteur, new Plateforme[(*quadTree).nbPlateforme], 0);
    QuadTree basGauche = creerQuadTree((*quadTree).x-demiLargeur, (*quadTree).y-demiHauteur, newLargeur, newHauteur, new Plateforme[(*quadTree).nbPlateforme], 0);
    QuadTree basDroite = creerQuadTree((*quadTree).x+demiLargeur, (*quadTree).y-demiHauteur, newLargeur, newHauteur, new Plateforme[(*quadTree).nbPlateforme], 0);

    printf("%f\n", &quadTree->nodes[0].x);

    quadTree->nodes = new QuadTree[4];
    quadTree->nodes[0] = hautGauche;
        printf("ça passe\n");

    quadTree->nodes[1] = hautDroite;
            printf("ça passe\n");

    quadTree->nodes[2] = basGauche;
            printf("ça passe\n");

    quadTree->nodes[3] = basDroite;
            printf("ça passe\n");


    afficherQuadTree(hautGauche);
    afficherQuadTree(hautDroite);
    afficherQuadTree(basGauche);
    afficherQuadTree(basDroite);

};

int donnerZoneQuadTree(QuadTree quadtree, Plateforme plateforme){
    int index = -1;

    bool partieHaut = plateforme.y - plateforme.hauteur/2 > quadtree.y;
    bool partieBasse = plateforme.y + plateforme.hauteur/2 < quadtree.y;
    bool partieGauche = plateforme.x - plateforme.largeur/2 < quadtree.x;
    bool partieDroite = plateforme.x + plateforme.largeur/2 > quadtree.x;

    if(partieHaut){
        if(partieGauche){
            index = 0;
        }else if(partieDroite){
            index = 1;
        }
    }

    if(partieBasse){
        if(partieGauche){
            index = 2;
        }else if(partieDroite){
            index = 3;
        }
    }


    return index;
}

int donnerZoneQuadTreeJoueur(QuadTree quadtree, Joueur plateforme){
    int index = -1;

    bool partieHaut = plateforme.y - plateforme.hauteur/2 > quadtree.y;
    bool partieBasse = plateforme.y + plateforme.hauteur/2 < quadtree.y;
    bool partieGauche = plateforme.x - plateforme.largeur/2 < quadtree.x;
    bool partieDroite = plateforme.x + plateforme.largeur/2 > quadtree.x;

    if(partieHaut){
        if(partieGauche){
            index = 0;
        }else if(partieDroite){
            index = 1;
        }
    }

    if(partieBasse){
        if(partieGauche){
            index = 2;
        }else if(partieDroite){
            index = 3;
        }
    }


    return index;
}


bool estFeuille(QuadTree quadtree){

    if(quadtree.nodes[0].x == NULL){

        return true;
    }

    return false;

}

void insererPlateforme(QuadTree* quadtree, Plateforme plateforme){

    int index = donnerZoneQuadTree(*quadtree, plateforme);

    if(index != -1){

        if((*quadtree).nbPlateforme >= (*quadtree).nbMaxPlateformes){
            
            (*quadtree).isLeaf = 0;
            splitQuadTree(quadtree);
            insererPlateforme(&(*quadtree).nodes[index], plateforme);

        }else{

            (*quadtree).plateformes[(*quadtree).nbPlateforme] = plateforme;
            (*quadtree).nbPlateforme++;
        }

    }

}

void drawQuadTree(QuadTree quadtree){

    
        afficherQuadTree(quadtree);
    


    //drawQuadTree(quadtree.nodes[0]);

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

