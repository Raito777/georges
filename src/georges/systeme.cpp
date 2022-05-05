#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "headers/systeme.h"


void onWindowResized(unsigned int width, unsigned int height)
{ 
    float aspectRatio = width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // This will anchor the camera to the lower left corner of the screen
    // Camera will be centered on (screenWidth/2, screenHeight/2)
    glOrtho( 0, width, 0, height, -1, 1 );

    
    // This will anchor the camera to the center of the screen
    // Camera will be centered on (0,0)
    //glOrtho( -width/2.f, width/2.f, -height/2.f, height/2.f, -1, 1 );

   /* if( aspectRatio > 1) 
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
    } */
}
