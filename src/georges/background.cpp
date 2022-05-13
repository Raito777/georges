#include <SDL2/SDL.h>
//#include "fakesdlimage.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <random>

#include "headers/couleurs.h"
#include "headers/systeme.h"
#include "headers/background.h"

Cercle createCercle(float x, float y, float radius, ColorRGB color){

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> z(30,60); // distribution in range [1, 6]


    Cercle newCercle = {x, y, z(rng), radius, color};

    return newCercle;

}

Background createBackground(int nbElements, Cercle *cercles){

    Background newBackground = {nbElements, cercles};

    return newBackground;

}

void afficherCercle(Cercle cercle, Camera camera){

        glPushMatrix();

            glTranslated(cercle.x+camera.x*-0.1*(cercle.z*0.1),cercle.y+camera.y*-0.1*(cercle.z*0.1),0);

            glScalef(cercle.radius,cercle.radius,0);

            glColor3f(cercle.color.r,cercle.color.g,cercle.color.b);
            
            drawCircle(1);

        glPopMatrix();

}

void updateBackground(Background background, Camera camera){
    for(int i=0; i < background.nbElements; i++){
        afficherCercle(background.cercles[i], camera);
    }
}

void loadTexture(const char* filename, GLuint textureID[10], int numTexture){
  
  SDL_Surface* image;
  image = IMG_Load(filename);

  if(image == NULL){
    printf("Error : image not found : %s\n", filename);
  }

  glGenTextures(1, textureID);
  glBindTexture(GL_TEXTURE_2D, numTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  // TODO : Supprimer les texture lors de la fermeture du prog
  //glDeleteTextures(10, &textureID);
  SDL_FreeSurface(image);
}