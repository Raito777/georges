#include <SDL2/SDL.h>
#include "../fakesdlimage.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "fonctions.h"


/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "TD04 Minimal";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 150.;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

static const int CIRCLE_SUBDIVS = 2<<5;


time_t rawtime;
struct tm* timeinfo;

int  *loop;
double  *x = 0;
double  *y = 0;
double  *z = 0;
float color = 0;

void drawCircle(int filled);

void drawSquare(int filled);

void onWindowResized(unsigned int width, unsigned int height)
{ 
    float aspectRatio = width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1) 
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio, 
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }
}


int main(int argc, char** argv) 
{
    /* Initialisation de la SDL */

    *loop = 1;

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

    while(*loop) 
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glPushMatrix();

            glScalef(10.,15.,0);

            glColor3f(1,0.7,0);
            
            glTranslated(*x,*y,*z);

            drawSquare(1);

        glPopMatrix();


        deplace(loop, x,y,z);

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

void drawCircle(int filled) 
{
    int i = 0;

    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    for(i = 0; i < CIRCLE_SUBDIVS; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)), 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));
    }
    glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)), 
                sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));

    glEnd();
}

void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( 0.5 , -0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( -0.5 , 0.5);
    glVertex2f( -0.5 , -0.5);
    glVertex2f( 0.5 , -0.5);

    glEnd();
}