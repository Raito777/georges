#include <SDL2/SDL.h>
#include "../textures/fakesdlimage.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "headers/joueur.h"
#include "headers/plateforme.h"
#include "headers/couleurs.h"
#include "headers/systeme.h"

Joueur creerJoueur(float x, float y, float largeur, float hauteur, float velociteSaut, int aFini, ColorRGB color){

    Joueur newJoueur = {x, y, largeur, hauteur, 0, 500, 0, 1, aFini, color};

    return newJoueur;

}

void afficherJoueur(Joueur joueur){

        glPushMatrix();

            glTranslated(joueur.x,joueur.y,0);

            glScalef(joueur.largeur,joueur.hauteur,0);

            glColor3f(joueur.color.r,joueur.color.g,joueur.color.b);
            
            drawSquare(1);

        glPopMatrix();

}

void updateJoueur(Joueur * joueur, float deltaTime){

    saut(joueur, deltaTime);
    gravite(joueur, deltaTime);

}



bool collision(Joueur joueur, Plateforme plateforme){

    return joueur.x - joueur.largeur/2 < plateforme.x + plateforme.largeur/2 && joueur.x + joueur.largeur/2 > plateforme.x - plateforme.largeur/2 && joueur.y-joueur.hauteur/2 < plateforme.y+plateforme.hauteur/2 && joueur.y+joueur.hauteur/2 > plateforme.y-plateforme.hauteur/2;

}

float dist(float x1, float y1, float x2, float y2){

    return sqrtf((x2-x1)*(x2-x1)+(y2-y1)*y2-y1);

}

void setCouleur(Joueur * joueur, ColorRGB color){
    (*joueur).color = color;
}

void checkCollision(Plateforme *plateforme, Joueur *joueur, float deltaTime){

   if(collision(*joueur, *plateforme)){

      setVelocite(plateforme, 0);
      //(*joueur).velociteSaut = 0;
      (*joueur).nbSaut = 0;
      (*joueur).y += 150 * deltaTime;


   }

}

void gravite(Joueur *joueur, float deltaTime){

   (*joueur).y -= 150 * deltaTime;

}

void saut(Joueur *joueur, float deltaTime){

    if((*joueur).nbSaut <= (*joueur).nbSautMax){
        (*joueur).y += (*joueur).velociteSaut * deltaTime;
    }
}

void setvelociteSaut(Joueur *joueur){
    

        (*joueur).velociteSaut += 400;
                
        if((*joueur).velociteSaut > (*joueur).hauteurSaut){
            (*joueur).velociteSaut = 0;
            //printf("velocite 0");
        }
    
}