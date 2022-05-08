#include <SDL2/SDL.h>

//#include <SDL2/SDL_image.h>
//#include "fakesdlimage.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <random>

#include "headers/plateforme.h"

#include "headers/joueur.h"
#include "headers/couleurs.h"
#include "headers/systeme.h"
#include "headers/quadtree.h"
#include "headers/arrive.h"
#include "headers/level.h"
#include "headers/background.h"





time_t rawtime;
struct tm* timeinfo;

float oldTimeSinceStart = 0;
float deltaTime = 0;

const int FPS = 60;
const int FRAMEDELAY = 1000 / FPS;

SDL_Surface *imageTitre = NULL;
SDL_Surface *windowSurface = NULL;


int main(int argc, char** argv)
{
    /* Initialisation de la SDL */




    SDL_Init(SDL_INIT_EVERYTHING);


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

    /*if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

    imageTitre = IMG_Load("textures/titre.png");

    if ( NULL == imageTitre )
    {
        printf("SDL could not load image! : %s\n", SDL_GetError());
    }*/

    windowSurface = SDL_GetWindowSurface( window );
    /* Boucle principale */



    int gameLoop = 1;

    int levelActif = 0;

    int nbLevel = 2;

    /*---------------------BACKGROUND----------------------------*/


    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> distWidth(0,WINDOW_WIDTH); 
    std::uniform_real_distribution<float> distHeight(0,WINDOW_HEIGHT);
    std::uniform_real_distribution<float> colorR(0,30); 
    std::uniform_real_distribution<float> colorV(0,10); 
    std::uniform_real_distribution<float> colorB(0,60); 
    std::uniform_real_distribution<float> radius(10,20); 

    int nbCercle = 100;
    Cercle listeCercle[nbCercle];

    for(int i = 0; i <= nbCercle; i++){

        ColorRGB colorCircle = createColor(colorR(rng)*0.01,colorV(rng)*0.01,colorB(rng)*0.01);

        Cercle cercle = createCercle(distWidth(rng),distHeight(rng), radius(rng), colorCircle);

        listeCercle[i] = cercle;

    }

    Background background = createBackground(nbCercle, listeCercle);


    /*-------------------LEVEL 1 --------------------------------*/

    ColorRGB couleurPlateforme = createColor(0.8,0.8,1);

    Joueur joueur = creerJoueur(WINDOW_WIDTH/2, 340,5,15, 1, createColor(0.7,0.4,0.2));

    Joueur joueur1 = creerJoueur(WINDOW_WIDTH/2-30, 210,15,15, 2, createColor(0.4,0.4,0.6));

    Joueur joueur2 = creerJoueur(WINDOW_WIDTH/2+30, 210,20,10, 3, createColor(0.1,0.8,0.4));

    Arrive arrive = creerArrive(WINDOW_WIDTH/2,520,joueur.largeur,joueur.hauteur,joueur.id,joueur.color);

    Arrive arrive1 = creerArrive(WINDOW_WIDTH/2-300,310,joueur1.largeur,joueur1.hauteur,joueur1.id,joueur1.color);

    Arrive arrive2 = creerArrive(WINDOW_WIDTH/2+300,307,joueur2.largeur,joueur2.hauteur,joueur2.id, joueur2.color);

    Camera camera = creerCamera(joueur.x, joueur.y);

    Plateforme plateforme = creerPlateforme(WINDOW_WIDTH/2, -100, 200,  WINDOW_HEIGHT, couleurPlateforme);

    Plateforme plateforme1 = creerPlateforme(WINDOW_WIDTH/2-300, 0, 150, WINDOW_HEIGHT, couleurPlateforme);

    Plateforme plateforme2 = creerPlateforme(WINDOW_WIDTH/2+300, 0, 150,  WINDOW_HEIGHT, couleurPlateforme);

    Plateforme plateforme3 = creerPlateforme(WINDOW_WIDTH/2, 490, 200,  40, couleurPlateforme);

    int tailleLvl1 = 4;

    int nbJoueurLvl1 = 3;

    Plateforme lvl1[tailleLvl1] = {plateforme1, plateforme, plateforme2, plateforme3};

    Joueur joueursLevel1[nbJoueurLvl1] = {joueur, joueur1, joueur2};

    Arrive arriveLevel1[nbJoueurLvl1] = {arrive, arrive1, arrive2};

    Level level1 = creerLevel(tailleLvl1, nbJoueurLvl1, lvl1, joueursLevel1, arriveLevel1, "Level 1");

    //printf("%s\n", level1.nom);

    /*----------------------LEVEL 2--------------------------------*/

    int tailleLvl2 = 1;

    int nbJoueurLvl2 = 3;

    ColorRGB couleurPlateformeLevel2 = createColor(0.8,0.8,1);

    Joueur joueurLevel2 = creerJoueur(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,5,15, 1, createColor(0.2,0.6,0.2));

    Joueur joueur1Level2 = creerJoueur(WINDOW_WIDTH/2-100,WINDOW_HEIGHT/2,15,15, 2, createColor(0.9,0.3,0.2));

    Joueur joueur2Level2 = creerJoueur(WINDOW_WIDTH/2-200,WINDOW_HEIGHT/2,20,10, 3, createColor(0.1,0.8,0.8));

    Joueur joueursLevel2[nbJoueurLvl2] = {joueurLevel2, joueur1Level2, joueur2Level2};

    Arrive arriveLevel2 = creerArrive(WINDOW_WIDTH/2-200,WINDOW_HEIGHT/2,joueurLevel2.largeur,joueurLevel2.hauteur,joueurLevel2.id,joueurLevel2.color);

    Arrive arrive1Level2 = creerArrive(WINDOW_WIDTH/2-300,WINDOW_HEIGHT/2,joueur1Level2.largeur,joueur1Level2.hauteur,joueur1Level2.id,joueur1Level2.color);

    Arrive arrive2Level2 = creerArrive(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,joueur2Level2.largeur,joueur2Level2.hauteur,joueur2Level2.id, joueur2Level2.color);

    Arrive listeArriveLevel2[nbJoueurLvl2] = {arriveLevel2, arrive1Level2, arrive2Level2};

    Plateforme plateformeLevel2 = creerPlateforme(WINDOW_WIDTH/2, WINDOW_HEIGHT/2-300, 600, 300, couleurPlateformeLevel2);

    Plateforme plateformesLevel2[tailleLvl2] = {plateformeLevel2};

    Level level2 = creerLevel(tailleLvl2, nbJoueurLvl2, plateformesLevel2, joueursLevel2, listeArriveLevel2, "Level 2");

    


    Level jeuxGeorges[nbLevel] = {level1, level2};
    
    /*Quad qt(Point(0, WINDOW_HEIGHT), Point(WINDOW_WIDTH, 0));

    qt.insert(&plateforme);
    qt.insert(&plateforme1);
    qt.insert(&plateforme2);*/

    //printf("Width : %i, height : %i \n", WINDOW_WIDTH, WINDOW_HEIGHT);

    while(gameLoop) 
    {

        float startTime = (float)SDL_GetTicks()/1000.f;

        deltaTime = startTime - oldTimeSinceStart;
        oldTimeSinceStart = startTime;

        if(FRAMEDELAY > deltaTime){
            SDL_Delay(FRAMEDELAY - deltaTime);
        }


        //printf("velocite y : %i, \n", level1.joueurs[0].id);

        //checkEvenements(&gameLoop, &joueur, &plateforme, deltaTime);

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


       /* if(qt.search(Point(joueur.x, joueur.y)) != NULL){
            cout << "Node a: " << qt.search(Point(0, 0))->y << "\n";
        }*/
       
        //SDL_RenderDrawRect(renderer, &rectangleTitre);

       //SDL_RenderCopy(renderer, texture, NULL, &rectangleTitre);

       glPushMatrix();
       
       cameraTranslate(camera);

       updateBackground(background, camera);

       for(int i = 0; i < jeuxGeorges[levelActif].taille; i++){
            
            afficherPlateforme(jeuxGeorges[levelActif].lvl[i]);
            updatePlateforme(&(jeuxGeorges[levelActif].lvl[i]), &(jeuxGeorges[levelActif].joueurs[0]), deltaTime);
            checkCollision(&(jeuxGeorges[levelActif].lvl[i]), &(jeuxGeorges[levelActif].joueurs[0]), deltaTime);
            //printf("velocite : %f\n", joueur.velocite);

        }

        
        checkEvenements(&gameLoop, &(jeuxGeorges[levelActif].joueurs[0]), jeuxGeorges[levelActif], deltaTime);

        for(int i = 0; i < jeuxGeorges[levelActif].nbJoueurs; i++){
            afficherJoueur(jeuxGeorges[levelActif].joueurs[i], jeuxGeorges[levelActif]);
        }

        updateJoueur(&(jeuxGeorges[levelActif].joueurs[0]), &camera, deltaTime);


        //on commence a 1 parcequ'on ne veut pas verifier que le joueur est en collision avec lui même
        for(int i = 1; i < jeuxGeorges[levelActif].nbJoueurs; i++){
            checkCollisionJoueur(&(jeuxGeorges[levelActif].joueurs[i]), &(jeuxGeorges[levelActif].joueurs[0]), deltaTime);
        }

        for(int i = 0; i < jeuxGeorges[levelActif].nbJoueurs; i++){
            afficherArrive(jeuxGeorges[levelActif].arrives[i]);
            updateArrive(&(jeuxGeorges[levelActif].arrives[i]), &(jeuxGeorges[levelActif].joueurs[0]), &jeuxGeorges[levelActif]);
        }

        if(verifieVictoire(jeuxGeorges[levelActif])){
            printf("victory\n");
            SDL_Delay(1000);
            levelActif++;
            //gameLoop = 0;
        }


        if(jeuxGeorges[levelActif].joueurs[0].y <= 0){
            respawn(&jeuxGeorges[levelActif].joueurs[0]);
        }

        glPopMatrix();
        //SDL_BlitSurface(imageTitre, NULL, windowSurface, NULL );

        SDL_GL_SwapWindow(window);

    }


    SDL_FreeSurface(imageTitre);
    /* Liberation des ressources associees a la SDL */ 
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

