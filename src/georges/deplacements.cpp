
#include <SDL2/SDL.h>
#include "../fakesdlimage.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "fonctions.h"


void deplace(int *loop, double *x, double *y, double *z){

SDL_Event e;
while(SDL_PollEvent(&e)) 
{
    /* L'utilisateur ferme la fenetre : */
    if(e.type == SDL_QUIT) 
    {
        loop = 0;
        break;
    }

    if(e.type == SDL_KEYDOWN){

        switch(e.key.keysym.sym){
            case SDLK_ESCAPE:
                loop = 0;
                break;
            case SDLK_q:
                x--;
                break;
            case SDLK_d:
                x++;
                break;
            case SDLK_z:
                y++;
                break;
            default:
                break;
        }

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