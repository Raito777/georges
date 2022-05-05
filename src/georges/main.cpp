#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include "fakesdlimage.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "headers/plateforme.h"

#include "headers/joueur.h"
#include "headers/couleurs.h"
#include "headers/systeme.h"


time_t rawtime;
struct tm* timeinfo;

float oldTimeSinceStart = 0;
float deltaTime = 0;

const int FPS = 60;
const int FRAMEDELAY = 1000 / FPS;

SDL_Surface *imageTitre = NULL;
SDL_Surface *windowSurface = NULL;


int main(int argc, char** argv) 
{
    /* Initialisation de la SDL */

    SDL_Init(SDL_INIT_EVERYTHING);


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

    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

    imageTitre = IMG_Load("titre.png");

    if ( NULL == imageTitre )
    {
        printf("SDL could not load image! : %s\n", SDL_GetError());
    }

    windowSurface = SDL_GetWindowSurface( window );
    /* Boucle principale */
    int gameLoop = 1;

    ColorRGB couleurPlateforme = createColor(0.8,0.8,1);

    ColorRGB couleurJoueur = createColor(0.7,0.4,0.2);

    Joueur joueur = creerJoueur(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,5,15,couleurJoueur);

    Camera camera = creerCamera(joueur.x, joueur.y);

    Plateforme plateforme = creerPlateforme(WINDOW_WIDTH/2, WINDOW_HEIGHT/2-300, 200, 60, couleurPlateforme);

    Plateforme plateforme1 = creerPlateforme(WINDOW_WIDTH/2-100, WINDOW_HEIGHT/2-200, 200, 60, couleurPlateforme);

    Plateforme plateforme2 = creerPlateforme(WINDOW_WIDTH/2-200, WINDOW_HEIGHT/2-100, 200, 60, couleurPlateforme);

    int tailleLvl1 = 3;

    Plateforme lvl1[tailleLvl1] = {plateforme1, plateforme, plateforme2};

    

    printf("Width : %i, height : %i \n", WINDOW_WIDTH, WINDOW_HEIGHT);

    while(gameLoop) 
    {

        float startTime = (float)SDL_GetTicks()/1000.f;

        deltaTime = startTime - oldTimeSinceStart;
        oldTimeSinceStart = startTime;

        if(FRAMEDELAY > deltaTime){
            SDL_Delay(FRAMEDELAY - deltaTime);
        }

       //printf("y : %f, \n", joueur.hauteurSaut);

       //printf("velocite y : %f, \n", joueur.velociteSaut);

        //checkEvenements(&gameLoop, &joueur, &plateforme, deltaTime);

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

       
        //SDL_RenderDrawRect(renderer, &rectangleTitre);

       //SDL_RenderCopy(renderer, texture, NULL, &rectangleTitre);
       
       cameraTranslate(camera);

       for(int i = 0; i < tailleLvl1; i++){
            
            afficherPlateforme(lvl1[i]);
            updatePlateforme(&(lvl1[i]), &joueur, deltaTime);
            checkCollision(&(lvl1[i]), &joueur, deltaTime);
            //printf("velocite : %f\n", joueur.velocite);

        }

        checkEvenements(&gameLoop, &joueur, deltaTime);

        updateJoueur(&joueur, &camera, deltaTime);
        afficherJoueur(joueur);

        if(joueur.y <= 0){
            respawn(&joueur);
        }

        SDL_BlitSurface(imageTitre, NULL, windowSurface, NULL );

        SDL_GL_SwapWindow(window);

    }
    SDL_FreeSurface(imageTitre);
    /* Liberation des ressources associees a la SDL */ 
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

