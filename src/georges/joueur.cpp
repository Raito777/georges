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

Joueur creerJoueur(float x, float y, float largeur, float hauteur, float vitesse, int aFini, ColorRGB color){

    Joueur newJoueur = {x, y, largeur, hauteur, vitesse, aFini, color};

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

bool collision(Joueur joueur, Plateforme plateforme){
    
    if((joueur.x >= plateforme.x+plateforme.largeur)
    ||(joueur.x + joueur.largeur <= plateforme.x)
    ||(joueur.y >= plateforme.y+plateforme.hauteur)
    ||(joueur.y + joueur.hauteur <= plateforme.y)){
        return false;
    }else{
        return true;
    }

}

float dist(float x1, float y1, float x2, float y2){

    return sqrtf((x2-x1)*(x2-x1)+(y2-y1)*y2-y1);

}

void setCouleur(Joueur * joueur, ColorRGB color){
    (*joueur).color = color;
}