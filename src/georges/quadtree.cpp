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

QuadTree creerQuadTree(float x, float y, float width, float height, Plateforme* listePlateformes, int nbPlateforme, int nbMaxPlateforme, int id)
{
    QuadTree quadTree;
    (quadTree).x = x;
    (quadTree).y = y;
    (quadTree).largeur = width;
    (quadTree).hauteur = height;
    (quadTree).plateformes = listePlateformes;
    (quadTree).nbPlateforme = 0;
    (quadTree).isLeaf = 1;
    (quadTree).nbMaxPlateformes = nbMaxPlateforme;
    (quadTree).id = id;
    quadTree.nodes = nullptr;

    return quadTree;
}

void splitQuadTree(QuadTree* quadTree){

    int id = (*quadTree).id;

    float newLargeur = (*quadTree).largeur/2;
    float newHauteur = (*quadTree).hauteur/2;
    float demiLargeur = (*quadTree).largeur/4;
    float demiHauteur = (*quadTree).hauteur/4;

    id++;

    QuadTree hautGauche = creerQuadTree((*quadTree).x-demiLargeur, (*quadTree).y+demiHauteur, newLargeur, newHauteur, new Plateforme[(*quadTree).nbMaxPlateformes+20], 0, (*quadTree).nbMaxPlateformes, id);
    id++;
    QuadTree hautDroite = creerQuadTree((*quadTree).x+demiLargeur, (*quadTree).y+demiHauteur, newLargeur, newHauteur, new Plateforme[(*quadTree).nbMaxPlateformes+20], 0, (*quadTree).nbMaxPlateformes, id);
    id++;
    QuadTree basGauche = creerQuadTree((*quadTree).x-demiLargeur, (*quadTree).y-demiHauteur, newLargeur, newHauteur, new Plateforme[(*quadTree).nbMaxPlateformes+20], 0, (*quadTree).nbMaxPlateformes, id);
    id++;
    QuadTree basDroite = creerQuadTree((*quadTree).x+demiLargeur, (*quadTree).y-demiHauteur, newLargeur, newHauteur, new Plateforme[(*quadTree).nbMaxPlateformes+20], 0, (*quadTree).nbMaxPlateformes, id);
    id++;

    quadTree->nodes = new QuadTree[4];

    quadTree->nodes[0] = hautGauche;
    quadTree->nodes[1] = hautDroite;
    quadTree->nodes[2] = basGauche;
    quadTree->nodes[3] = basDroite;

    afficherQuadTree(hautGauche);
    afficherQuadTree(hautDroite);
    afficherQuadTree(basGauche);
    afficherQuadTree(basDroite);

};


void insererPlateforme(QuadTree* quadtree, Plateforme plateforme, int index){

    //Si la plateforme est dans le quadtree
    //printf("lezzzgooooo\n");
    if(estDansQuadTree(*quadtree, plateforme)){
           
        
        if(index <= 1){

            //on insere la plateforme dans le quadtree
            (*quadtree).plateformes[(*quadtree).nbPlateforme] = plateforme;

            // printf("plateforme x : %f  \n", (*quadtree).plateformes[(*quadtree).nbPlateforme].x);
            // printf("plateforme y : %f  \n", (*quadtree).plateformes[(*quadtree).nbPlateforme].y);

            (*quadtree).nbPlateforme++;
            //printf("nb Plateforme : %i\n", (*quadtree).nbPlateforme);


        //sinon
        }else{
            //si le quadtree est une feuille (pas d'enfant)
            if((*quadtree).isLeaf == 1){

                //printf("splitting\n");
                //on dit que ce n'est plus une feuille
                (*quadtree).isLeaf = 0;
                //on cr???? 4 enfant au quadtree
                splitQuadTree(quadtree);
            }

            //printf("index : %i\n", index);
    
            //on re-appelle la fonction pour ses 4 enfants
            if(estDansQuadTree((*quadtree).nodes[0], plateforme)){
                insererPlateforme(&(*quadtree).nodes[0], plateforme, index-1);
            }
            if(estDansQuadTree((*quadtree).nodes[1], plateforme)){
                insererPlateforme(&(*quadtree).nodes[1], plateforme, index-1);
            }
            if(estDansQuadTree((*quadtree).nodes[2], plateforme)){
                insererPlateforme(&(*quadtree).nodes[2], plateforme, index-1);
            }
            if(estDansQuadTree((*quadtree).nodes[3], plateforme)){
                insererPlateforme(&(*quadtree).nodes[3], plateforme, index-1);
            }

        }
    }

}

bool estDansQuadTree(QuadTree quadtree, Plateforme plateforme){

    bool contains = plateforme.x - plateforme.largeur/2 <= quadtree.x + quadtree.largeur/2 && plateforme.x + plateforme.largeur/2 >= quadtree.x - quadtree.largeur/2 && plateforme.y-plateforme.hauteur/2 <= quadtree.y+quadtree.hauteur/2 && plateforme.y+plateforme.hauteur/2 >= quadtree.y-quadtree.hauteur/2;

    if(contains){

        return true;

    }

    return false;
}

QuadTree* chercherPlateforme(QuadTree& quadtree, Joueur joueur){


    //si le quadtree est une feuille, on le retourne directement
        if(quadtree.isLeaf == 1){
            return &quadtree;
        }
        //si le quadtree n'est pas une feuille, on relance la fonction avec ses 4 enfants, jusqu'a qu'il soit une feuille
        //printf("nb plat : %i\n", quadtree.nbPlateforme);

        if(contientJoueur(quadtree.nodes[0], joueur)){
          return chercherPlateforme(quadtree.nodes[0],  joueur);
        }

        if(contientJoueur(quadtree.nodes[1], joueur)){
          return chercherPlateforme(quadtree.nodes[1],  joueur);
        }  
             
        if(contientJoueur(quadtree.nodes[2], joueur)){
          return chercherPlateforme(quadtree.nodes[2],  joueur);
        }

        if(contientJoueur(quadtree.nodes[3], joueur)){
          return chercherPlateforme(quadtree.nodes[3],  joueur);
        }

        return nullptr;


}


bool contientJoueur(QuadTree quadtree, Joueur joueur){

    bool contains = joueur.x - joueur.largeur/2 <= quadtree.x + quadtree.largeur/2 && joueur.x + joueur.largeur/2 >= quadtree.x - quadtree.largeur/2 && joueur.y-joueur.hauteur/2 <= quadtree.y+quadtree.hauteur/2 && joueur.y+joueur.hauteur/2 >= quadtree.y-quadtree.hauteur/2;

    if(contains){
        return true;
    }


    return false;
}




void drawQuadTree(QuadTree quadtree){

    
    afficherQuadTree(quadtree);
    
    if(quadtree.isLeaf == 0){

        drawQuadTree(quadtree.nodes[0]);
        drawQuadTree(quadtree.nodes[1]);
        drawQuadTree(quadtree.nodes[2]);
        drawQuadTree(quadtree.nodes[3]);

    }


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

