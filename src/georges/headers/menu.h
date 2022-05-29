#ifndef MENU_H_
#define MENU_H_

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_image.h> 
#include <time.h>
#include <iostream>
#include <random>



void Menu(SDL_Event e,int* gamestate,int* etat,int* gameLoop);
void AfficheMenu(int etat);
void AffichePause(int etat);
void Pause(SDL_Event e,int* gamestate,int* etat);
#endif