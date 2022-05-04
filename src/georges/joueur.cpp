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

Joueur creerJoueur(float x, float y, float largeur, float hauteur, ColorRGB color){

    Joueur newJoueur = {x, y, x, y, x, y, largeur, hauteur, 0, 200, 0, 500, 0, 1, 0, color};

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

void updateJoueur(Joueur * joueur, Camera * camera, float deltaTime){

    deplacerJoueur(joueur, deltaTime);
    saut(joueur, deltaTime);
    gravite(joueur, deltaTime);
    updateCamera(camera, joueur);


}


Camera creerCamera(float x, float y){

    Camera camera = {x, y};

    return camera;

}

void updateCamera(Camera *camera, Joueur *joueur){

    (*camera).x = -((*joueur).x - (*joueur).originX);
    (*camera).y = -((*joueur).y - (*joueur).originY);

}

void cameraTranslate(Camera camera){

    glTranslated(camera.x, camera.y, 0);

}


bool collision(Joueur joueur, Plateforme plateforme){

    return joueur.x - joueur.largeur/2 < plateforme.x + plateforme.largeur/2 && joueur.x + joueur.largeur/2 > plateforme.x - plateforme.largeur/2 && joueur.y-joueur.hauteur/2 < plateforme.y+plateforme.hauteur/2 && joueur.y+joueur.hauteur/2 > plateforme.y-plateforme.hauteur/2;

}

bool collisionX(Joueur joueur, Plateforme plateforme){
    return joueur.x + joueur.largeur/2 > plateforme.x - plateforme.largeur/2 && joueur.y-joueur.hauteur/2 < plateforme.y+plateforme.hauteur/2 && joueur.y+joueur.hauteur/2 > plateforme.y-plateforme.hauteur/2;
}

bool collisionBas(Joueur joueur, Plateforme plateforme){
    return joueur.y-joueur.hauteur/2 <= plateforme.y+plateforme.hauteur/2 && joueur.y-joueur.hauteur/2 >= plateforme.y;
}

bool collisionHaut(Joueur joueur, Plateforme plateforme){
    return joueur.y+joueur.hauteur/2 >= plateforme.y-plateforme.hauteur/2;
}

void checkCollision(Plateforme *plateforme, Joueur *joueur, bool * isJumping, float deltaTime){

   if(collision(*joueur, *plateforme)){


       //printf("collision Partout\n");

    if(collisionBas(*joueur, *plateforme)){
        (*joueur).y += 200 * deltaTime;
        (*joueur).nbSaut = 0;
        (*isJumping) = false;
        (*joueur).velociteSaut = 0;
       //printf("collision Bas\n");
    } 
    if(collisionX(*joueur, *plateforme)){
        (*joueur).velocite = (*joueur).velocite*-1.01;
       // printf("collision X\n");
    }
    if(collisionHaut(*joueur, *plateforme)){
        (*isJumping) = false;
        (*joueur).y += -2*(*joueur).velociteSaut * deltaTime;
        //printf("collision X\n");
    }

    /*while(collision(*joueur, *plateforme)){
        
            (*joueur).y += 200 * deltaTime;
            (*joueur).velociteSaut = 0;
    }
*/
   }

}

float dist(float x1, float y1, float x2, float y2){

    return sqrtf((x2-x1)*(x2-x1)+(y2-y1)*y2-y1);

}

void setCouleur(Joueur * joueur, ColorRGB color){
    (*joueur).color = color;
}



void gravite(Joueur *joueur, float deltaTime){

   (*joueur).y -= 200 * deltaTime;

}

void saut(Joueur *joueur, float deltaTime){
    
    if((*joueur).nbSaut <= (*joueur).nbSautMax){
        (*joueur).y += (*joueur).velociteSaut * deltaTime;
    }
}

void setvelociteSaut(Joueur *joueur, bool * isJumping){
      
      if((*isJumping)){

        (*joueur).velociteSaut += 450;

        if((*joueur).velociteSaut >= (*joueur).hauteurSaut){
            (*isJumping) = false;
        }

      }else if(!(*isJumping)){

        (*joueur).velociteSaut = 0;

      }
        
}

void deplacerJoueur(Joueur *joueur, float deltaTime){

    (*joueur).x += -(*joueur).velocite * deltaTime;

}

void setVelocite(Joueur *joueur, float step){

    if(step < 0){
        if((*joueur).velocite <= -(*joueur).acceleration){
            (*joueur).velocite = -(*joueur).acceleration;
        }else{
            (*joueur).velocite += step;
        }
    }
    if(step > 0){
    if((*joueur).velocite >= (*joueur).acceleration){
            (*joueur).velocite = (*joueur).acceleration;
        }else{
            (*joueur).velocite += step;
        }
    }
 
}

void resetVelocite(Joueur *joueur, float step){

       /*  while((*plateforme).velocite > step || (*plateforme).velocite < -step){

            if((*plateforme).velocite < 0){
                (*plateforme).velocite *= 0.999;
            }

            if((*plateforme).velocite > 0){
                (*plateforme).velocite *= 0.999;
            }

            //printf("ralentit %f : \n", (*plateforme).velocite);

        }*/
        (*joueur).velocite = 0;

}




void respawn(Joueur *joueur){
    (*joueur).y = 500;
}