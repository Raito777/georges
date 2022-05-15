#include <SDL2/SDL.h>
//#include "fakesdlimage.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "headers/joueur.h"
#include "headers/plateforme.h"
#include "headers/couleurs.h"
#include "headers/systeme.h"
#include "headers/level.h"

Level creerLevel(int taille, int nbJoueurs, Plateforme plateforme[], Joueur joueurs[], Arrive arrives[], char *nom){

    Level newLevel = {taille, nbJoueurs, plateforme, joueurs, arrives, nom};

    return newLevel;

};

void switchJoueur(Level * level){

 
    Joueur saveLast = (*level).joueurs[(*level).nbJoueurs-1];

    for(int i = 1; i<(*level).nbJoueurs-1; i++){
        Joueur saveFirst = (*level).joueurs[i];
        (*level).joueurs[i] = (*level).joueurs[i-1];
        (*level).joueurs[i+1] = saveFirst;
    }

    (*level).joueurs[0] = saveLast;

    if((*level).joueurs[0].aFini){
        switchJoueur(level);
    }
}

void supprimerJoueur(Level * level){

    if(!verifieVictoire(*level)){
        switchJoueur(level);
    }
    
}

bool verifieVictoire(Level level){

    for(int i = 0; i < level.nbJoueurs; i++){
        if(level.joueurs[i].aFini == false){
            return false;
        }
    }
    
    return true;

}