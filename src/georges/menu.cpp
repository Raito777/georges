#include "headers/menu.h"
#include "headers/background.h"

void Menu(SDL_Event e, int* etat, int* phase, int* gameLoop){

	int cours = 3;
	switch(e.type){
		case SDL_KEYDOWN :
			if(e.key.keysym.sym==1073741906){
				if(*phase == 1){
					*phase = cours;
				}
				else{
					*phase -= 1;
				}
			}
			if(e.key.keysym.sym == 1073741905){
				if(*phase==cours){
					*phase =1;
				}
				else{
					*phase +=1;
				}
			}
			if(e.key.keysym.sym == 13 || e.key.keysym.sym == 1073741912){
				if(*phase !=3){
					*etat = *phase;
					*phase =1;
				}
				else{
					*gameLoop = 0;
					break;
				}
			}
			break;
			case SDL_KEYUP:
				break;

			default: 
				break;
	}
}

void AfficheMenu(int phase){

	glColor3f(1,1,1);
	char *menui;
	if(phase==1){
		menui = "textures/MENU_jouer.png";
	}
	if(phase==2){
		menui = "textures/MENU_options.png";
	}
	if(phase==3){
		menui = "textures/MENU_quitter.png";
	}

	//drawTexture(3000,3000,0,0,menui);
	
	

	
}