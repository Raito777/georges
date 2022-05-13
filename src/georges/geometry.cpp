#include <SDL2/SDL.h>
//#include "../fakesdlimage.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "headers/systeme.h"

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

void drawSquare2(int Filled, float r, float g, float b , float positionX, float positionY,float tailleX, float tailleY ){
  glColor3ub(r, g, b);
  if(Filled==1) { 
    glBegin(GL_QUADS);
  }
  else glBegin(GL_LINE_LOOP);
    glVertex2f(positionX, positionY);
    glVertex2f(positionX+tailleX, positionY);
    glVertex2f(positionX+tailleX, positionY+tailleY);
    glVertex2f(positionX, positionY+tailleY);
  glEnd();
}

void drawTriangle(int filled) 
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

    glVertex2f( 0 , -0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0, -0.5);


    glEnd();
}