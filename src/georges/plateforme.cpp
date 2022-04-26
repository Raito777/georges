#include <SDL2/SDL.h>
#include "../textures/fakesdlimage.h"
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

Plateforme creerPlateforme(float x, float y, float largeur, float hauteur, float velocite, float acceleration, ColorRGB color){

    Plateforme newPlateformes = {x, y, largeur, hauteur, velocite, acceleration, color};

    return newPlateformes;

}

void updatePlateforme(Plateforme *plateforme){

    deplacerPlateforme(plateforme);

}

void afficherPlateforme(Plateforme plateforme){

        glPushMatrix();

            glTranslated(plateforme.x,plateforme.y,0);

            glScalef(plateforme.largeur,plateforme.hauteur,0);

            glColor3f(plateforme.color.r,plateforme.color.g,plateforme.color.b);
            
            drawSquare(1);

        glPopMatrix();

}

void deplacerPlateforme(Plateforme *plateforme){

    (*plateforme).x += (*plateforme).velocite;

}

void setVelocite(Plateforme *plateforme, float step){

    if(step < 0){
        if((*plateforme).velocite <= -(*plateforme).acceleration){
        (*plateforme).velocite = -(*plateforme).acceleration;
        }else{
            (*plateforme).velocite += step;
        }
    }
    if(step > 0){
    if((*plateforme).velocite >= (*plateforme).acceleration){
        (*plateforme).velocite = (*plateforme).acceleration;
        }else{
            (*plateforme).velocite += step;
        }
    }
 
}

void resetVelocite(Plateforme *plateforme, float step){

         while((*plateforme).velocite > step || (*plateforme).velocite < -step){

            if((*plateforme).velocite < 0){
                (*plateforme).velocite *= 0.999;
            }

            if((*plateforme).velocite > 0){
                (*plateforme).velocite *= 0.999;
            }

            //printf("ralentit %f : \n", (*plateforme).velocite);

        }

        (*plateforme).velocite = 0;

}