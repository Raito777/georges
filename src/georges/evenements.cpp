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


void checkEvenements(int *gameLoop, Joueur *joueur, Plateforme *plateforme, float deltaTime){

SDL_Event e;

float step = 30;


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
                setVelocite(plateforme, step);
                break;
            case SDLK_d:
                setVelocite(plateforme, -step);
                
                break;
            case SDLK_z:
                setvelociteSaut(joueur);
                

                break;
            case SDLK_s:
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
                resetVelocite(plateforme, step);
                break;
            case SDLK_d:
                resetVelocite(plateforme, step);
                break;
            case SDLK_z:
                (*joueur).nbSaut += 1;
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
            printf("touche pressee (code = %d)\n", e.key.keysym.sym);
            break;
            
        default:
            break;
    }
}

}