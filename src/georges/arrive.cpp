#include <SDL2/SDL.h>
//#include "fakesdlimage.h"
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
#include "headers/arrive.h"

Arrive creerArrive(float x, float y, float largeur, float hauteur, int id, ColorRGB color){

    Arrive newArrive = {x, y, largeur, hauteur, id, false, color};

    return newArrive;

}

void afficherArrive(Arrive arrive){

        glPushMatrix();

            glTranslated(arrive.x,arrive.y,0);

            glScalef(arrive.largeur,arrive.hauteur,0);

            glColor3f(arrive.color.r,arrive.color.g,arrive.color.b);
            
            drawSquare(arrive.aFini);

        glPopMatrix();

}

void updateArrive(Arrive *arrive, Joueur *joueur, Level *level){

    verifierJoueur(arrive, joueur, level);

}

void verifierJoueur(Arrive *arrive, Joueur *joueur, Level *level){

    if(collisionArrive(*joueur, *arrive) && (*joueur).id == (*arrive).id && (*level).nbJoueurs > 0){
        (*arrive).aFini = true;
        (*joueur).aFini = true;
        (*joueur).x = (*arrive).x;
        (*joueur).y = (*arrive).y;
        supprimerJoueur(level);
    }

}

bool collisionArrive(Joueur joueur, Arrive arrive){

    return joueur.x - joueur.largeur/2 < arrive.x + arrive.largeur/2 && joueur.x + joueur.largeur/2 > arrive.x - arrive.largeur/2 && joueur.y-joueur.hauteur/2 < arrive.y+arrive.hauteur/2 && joueur.y+joueur.hauteur/2 > arrive.y-arrive.hauteur/2;

}