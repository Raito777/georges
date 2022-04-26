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


time_t rawtime;
struct tm* timeinfo;




int main(int argc, char** argv) 
{
    /* Initialisation de la SDL */

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        const char* error = SDL_GetError();
        fprintf(
            stderr, 
            "Erreur lors de l'intialisation de la SDL : %s\n", error);

        SDL_Quit();
        return EXIT_FAILURE;
    }
	
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */

    SDL_Window* window;
    {
        window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(NULL == window) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation de la fenetre : %s\n", error);

            SDL_Quit();
            return EXIT_FAILURE;
        }
    }
    
    SDL_GLContext context;
    {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        context = SDL_GL_CreateContext(window);
    
        if(NULL == context) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation du contexte OpenGL : %s\n", error);

            SDL_DestroyWindow(window);
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }    
  
    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);

  
    /* Boucle principale */
    int gameLoop = 1;

    ColorRGB couleurPlateforme = createColor(0.8,0.8,1);

    ColorRGB couleurJoueur = createColor(0.7,0.4,0.2);

    Joueur joueur = creerJoueur(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,5,15,1,0,couleurJoueur);


    Plateforme plateforme = creerPlateforme(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 20, 40, 0, 0.15, couleurPlateforme);

    Plateforme hitbox = creerPlateforme(plateforme.y+plateforme.hauteur, plateforme.x+plateforme.largeur, plateforme.largeur, plateforme.hauteur, 0, 0.15, createColor(0,1,0));


    printf("Width : %i, height : %i \n", WINDOW_WIDTH, WINDOW_HEIGHT);

    while(gameLoop) 
    {

        checkEvenements(&gameLoop, &joueur, &plateforme);

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        afficherPlateforme(plateforme);

        afficherPlateforme(hitbox);

        afficherJoueur(joueur);


        printf("Width : %f, height : %f \n", joueur.largeur, joueur.hauteur);


        if(collision(joueur, plateforme)){
            setCouleur(&joueur, createColor(1,0.,0.));
        }else{
            setCouleur(&joueur, createColor(0.7,0.4,0.2));
        }

        updatePlateforme(&plateforme);

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        
        /* Boucle traitant les evenements */
 

        /* Calcul du temps ecoule 
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        Si trop peu de temps s'est ecoule, on met en pause le programme
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }*/
    }

    /* Liberation des ressources associees a la SDL */ 
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

