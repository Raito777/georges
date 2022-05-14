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
#include "headers/level.h"
//#include "headers/menu.h"

void checkEvenements(int *gameLoop, Joueur *joueur, Level level, float deltaTime,bool *ismenu){

SDL_Event e;

float step = 10;
float stepSaut = 80;



/*const Uint8* keystate = SDL_GetKeyboardState(NULL);

if (keystate[SDL_SCANCODE_Z]) {
    
    (*joueur).nbSaut += 1;
    (*joueur).isJumping = true;
    printf("saut\n");
    setvelociteSaut(joueur, stepSaut);
}*/

const Uint8 *state = SDL_GetKeyboardState(NULL); 

if (state[SDL_SCANCODE_W]) { 
    (*joueur).nbSaut += 1;
    setvelociteSaut(joueur, stepSaut);
}
if (state[SDL_SCANCODE_A]) { 
    setVelocite(joueur, step);
}
if (state[SDL_SCANCODE_D]) { 
    setVelocite(joueur, -step);
}




while(SDL_PollEvent(&e)) 
{
    /* L'utilisateur ferme la fenetre : */
    if(e.type == SDL_QUIT) 
    {
        *gameLoop = 0;
        break;
    }

    if(e.type == SDL_KEYDOWN){

        switch(e.key.keysym.sym){
            case SDLK_ESCAPE:
                *gameLoop = 0;
                break;
            case SDLK_q:
                setVelocite(joueur, step);
                break;

            case SDLK_d:
                setVelocite(joueur, -step);
                break;
            case SDLK_TAB:
                switchJoueur(&level);
                break;
            case SDLK_z:

                //setvelociteSaut(joueur, stepSaut);
                break;

            case SDLK_s:
                break;

            case SDLK_p:
            printf("ah cest deja ca\n");
                    if(*(ismenu)==true){
                        *(ismenu) = false;
                    }
                    else{
                        *(ismenu) = true;
                    }
            break;
            default:
                break;

        }

       // printf("velocite %f : \n", (*plateforme).velocite);

    }

    if(e.type == SDL_KEYUP){
        
        switch(e.key.keysym.sym){
            case SDLK_ESCAPE:
                *gameLoop = 0;
                break;
            case SDLK_q:
                      resetVelocite(joueur, deltaTime);
                break;
            case SDLK_d:
                      resetVelocite(joueur, deltaTime);
                break;
            case SDLK_z:
                      (*joueur).isJumping = false;
                      (*joueur).velociteSaut = 0;
                break;
            case SDLK_s:
                break;
            default:
                break;
        }
        //resetVelocite(plateforme, step);

    }


    switch(e.type) 
    {
        case SDL_WINDOWEVENT:
            switch (e.window.event) 
            {
                /* Redimensionnement fenetre */
                case SDL_WINDOWEVENT_RESIZED:
                    onWindowResized(e.window.data1, e.window.data2);                
                    break;

                default:
                    break; 
            }
            break;

        /* Clic souris */
        case SDL_MOUSEBUTTONUP:
            printf("clic en (%d, %d)\n", e.button.x, e.button.y);

            break;
        
        /* Touche clavier */
        case SDL_KEYDOWN:
            ///printf("touche pressee (code = %d)\n", e.key.keysym.sym);
            break;

        default:
            break;
    }
}

}

