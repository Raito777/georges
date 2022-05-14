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

Joueur creerJoueur(float x, float y, float largeur, float hauteur,int id, ColorRGB color){

    Joueur newJoueur = {x, y, x, y, x, y, largeur, hauteur, 0, 300, 0, 500, true, false, false, false, 0, 1, id, false, color};

    return newJoueur;

}

void afficherJoueur(Joueur joueur, Level level){



        glPushMatrix();

            glTranslated(joueur.x,joueur.y,0);

            glPushMatrix();

                glScalef(joueur.largeur,joueur.hauteur,0);

                glColor3f(joueur.color.r,joueur.color.g,joueur.color.b);
                
                drawSquare(1);
                
            glPopMatrix();

        if(joueur.id == level.joueurs[0].id){
            glPushMatrix();
                glScalef(7,7,0);

                glTranslated(0, 4,0);

                glColor3f(1,1,1);

                drawTriangle(1);

            glPopMatrix();
        }

        glPopMatrix();

}



void updateJoueur(Joueur * joueur, Camera * camera, float deltaTime){

    deplacerJoueur(joueur, deltaTime);
    saut(joueur, deltaTime);
    
    if(!(*joueur).isCollidingPlateforme && !(*joueur).isCollidingPlayer){
        gravite(joueur, deltaTime);
    }
    (*joueur).isCollidingPlateforme = false;
    (*joueur).isCollidingPlayer = false;
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

bool collisionJoueur(Joueur joueur1, Joueur joueur2){

    return joueur1.x - joueur1.largeur/2 < joueur2.x + joueur2.largeur/2 && joueur1.x + joueur1.largeur/2 > joueur2.x - joueur2.largeur/2 && joueur1.y-joueur1.hauteur/2 < joueur2.y+joueur2.hauteur/2 && joueur1.y+joueur1.hauteur/2 > joueur2.y-joueur2.hauteur/2;

}

bool collisionJoueurX(Joueur joueur, Joueur plateforme){
    return joueur.x + joueur.largeur/2 > plateforme.x - plateforme.largeur/2 && joueur.y-joueur.hauteur/2+5 < plateforme.y+plateforme.hauteur/2 && joueur.y+joueur.hauteur/2-5 > plateforme.y-plateforme.hauteur/2;
}

bool collisionJoueurBas(Joueur joueur, Joueur plateforme){
    return joueur.y-joueur.hauteur/2 <= plateforme.y+plateforme.hauteur/2 && joueur.y-joueur.hauteur/2 >= plateforme.y;
}

bool collisionJoueurHaut(Joueur joueur, Joueur plateforme){
    return joueur.y+joueur.hauteur/2 >= plateforme.y-plateforme.hauteur/2;
}

bool collisionX(Joueur joueur, Plateforme plateforme){
    return joueur.x + joueur.largeur/2 > plateforme.x - plateforme.largeur/2 && joueur.y-joueur.hauteur/2+5 < plateforme.y+plateforme.hauteur/2 && joueur.y+joueur.hauteur/2-5 > plateforme.y-plateforme.hauteur/2;
}

bool collisionBas(Joueur joueur, Plateforme plateforme){
    return joueur.y-joueur.hauteur/2 <= plateforme.y+plateforme.hauteur/2 && joueur.y-joueur.hauteur/2 >= plateforme.y;
}

bool collisionHaut(Joueur joueur, Plateforme plateforme){
    return joueur.y+joueur.hauteur/2 >= plateforme.y-plateforme.hauteur/2;
}

void checkCollision(Plateforme* plateforme, Joueur* joueur, int size, int nbJoueurs, float deltaTime){

    for(int i = 0; i < size; i++){

        if(collision(joueur[0], plateforme[i])){
            //printf("collision Partout\n");
            joueur[0].isCollidingPlateforme = true;

            if(collisionBas(joueur[0],  plateforme[i])){
                //(*level).joueurs[0].y += 200 * deltaTime;
                joueur[0].nbSaut = 0;
                joueur[0].isJumping = true;
                joueur[0].hauteurSaut = joueur[0].y + 100;
                joueur[0].velociteSaut = 0;
                
            //printf("collision Bas\n");
            } else 
            if(collisionHaut(joueur[0],  plateforme[i])){
                joueur[0].velociteSaut = joueur[0].velociteSaut *-1.01;
                
                //printf("collision X\n");
            }
            if(collisionX(joueur[0],  plateforme[i])){
                joueur[0].velocite = joueur[0].velocite*-1.1;
            // printf("collision X\n");
            }

        }

    }

    for(int i = 1; i < nbJoueurs; i++){

            //printf("collision Partout\n");
            if(collisionJoueur(joueur[0], joueur[i])){
                //printf("collision Partout\n");
                joueur[0].isCollidingPlayer = true;
                if(collisionJoueurBas(joueur[0], joueur[i])){
                    //(*level).joueurs[0].y += 200 * deltaTime;
                    joueur[0].nbSaut = 0;
                    joueur[0].isJumping = true;
                    joueur[0].hauteurSaut = joueur[0].y + 100;
                    joueur[0].velociteSaut = 0;
                //printf("collision Bas\n");
                }else
                if(collisionJoueurHaut(joueur[0], joueur[i])){
                    joueur[0].velociteSaut = joueur[0].velociteSaut *-1.01;
                    //printf("collision X\n");
                }
                if(collisionJoueurX(joueur[0], joueur[i])){
                    joueur[0].velocite = joueur[0].velocite*-1.1;
                // printf("collision X\n");
                }


            }

    }


}

/*void checkCollisionJoueur(Joueur *plateforme, Joueur *joueur, float deltaTime){

   if(collisionJoueur(*joueur, *plateforme)){
       //printf("collision Partout\n");

    if(collisionJoueurBas(*joueur, *plateforme)){
        (*joueur).y += 200 * deltaTime;
        (*joueur).nbSaut = 0;
        (*joueur).isJumping = true;
        (*joueur).hauteurSaut = (*joueur).y + 100;
        (*joueur).velociteSaut = 0;
       //printf("collision Bas\n");
    }
    if(collisionJoueurX(*joueur, *plateforme)){
        (*joueur).velocite = (*joueur).velocite*-1.01;
       // printf("collision X\n");
    }
    if(collisionJoueurHaut(*joueur, *plateforme)){
        (*joueur).y += -2*(*joueur).velociteSaut * deltaTime;
        //printf("collision X\n");
    }
   }
}*/

void setCouleur(Joueur * joueur, ColorRGB color){
    (*joueur).color = color;
}

void gravite(Joueur *joueur, float deltaTime){

   (*joueur).y -= 200 * deltaTime;

}

void saut(Joueur *joueur, float deltaTime){

    (*joueur).y += (*joueur).velociteSaut * deltaTime;

}

void setvelociteSaut(Joueur *joueur, float step){

    if((*joueur).y >= (*joueur).hauteurSaut){
        (*joueur).isJumping = false;
    } 

    if((*joueur).isJumping){

        (*joueur).velociteSaut += step;

    }else if((*joueur).isJumping == false){
        
        (*joueur).velociteSaut *= 0.90;

    }
        
}

void deplacerJoueur(Joueur *joueur, float deltaTime){

    (*joueur).x += -(*joueur).velocite * deltaTime;

    if(!(*joueur).isMooving){

        resetVelocite(joueur, deltaTime);
        
    }

}

void setVelocite(Joueur *joueur, float step){
    (*joueur).isMooving = true;
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

void resetVelocite(Joueur *joueur, float deltaTime){

    (*joueur).isMooving = false;

    if((*joueur).velocite != 0){

        (*joueur).velocite *= 0.95;

    }

    if((*joueur).velocite < 0.05 && (*joueur).velocite > 0.05){

        (*joueur).velocite = 0;

    }

}

void respawn(Joueur *joueur){
    (*joueur).x = (*joueur).originX;
    (*joueur).y = (*joueur).originY;
}