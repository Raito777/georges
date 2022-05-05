#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "headers/joueur.h"
#include "headers/couleurs.h"
#include "headers/systeme.h"
#include "headers/plateforme.h"

Plateforme creerPlateforme(float x, float y, float largeur, float hauteur, ColorRGB color){

    Plateforme newPlateformes = {x, y, largeur, hauteur, color};

    return newPlateformes;

}

void updatePlateforme(Plateforme *plateforme, Joueur * joueur, float deltaTime){

    
      //  deplacerPlateforme(plateforme, joueur, deltaTime);
    
    //printf("updating %d\n", plateforme);

}

void afficherPlateforme(Plateforme plateforme){

        glPushMatrix();

            glTranslated(plateforme.x,plateforme.y,0);

            glScalef(plateforme.largeur,plateforme.hauteur,0);

            glColor3f(plateforme.color.r,plateforme.color.g,plateforme.color.b);
            
            drawSquare(1);

        glPopMatrix();

}




void deplacerPlateforme(Plateforme *plateforme, Joueur *joueur, float deltaTime){

    (*plateforme).x += (*joueur).velocite * deltaTime;

}


