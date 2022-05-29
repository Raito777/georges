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
#include "headers/menu.h"


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
    
    bool ismenu =false;

    int levelActif = 0;


    int menu = 0;

    bool isQuadTreeCreated = false;

    bool isTransitionFinished = false;

    GLuint textureID[360];

    

    /*---------------------BACKGROUND----------------------------*/


    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> distWidth(-800,WINDOW_WIDTH+800); 
    std::uniform_real_distribution<float> distHeight(-800,WINDOW_HEIGHT+800);
    std::uniform_real_distribution<float> colorR(80,100); 
    std::uniform_real_distribution<float> colorV(80,100); 
    std::uniform_real_distribution<float> colorB(80,100); 
    std::uniform_real_distribution<float> radius(5,15); 
    std::uniform_real_distribution<float> z(30,60);


    int nbCercle = 200;
    Cercle listeCercle[nbCercle];

    for(int i = 0; i <= nbCercle; i++){

        ColorRGB colorCircle = createColor(colorR(rng)*0.01,colorV(rng)*0.01,colorB(rng)*0.01);

        Cercle cercle = createCercle(distWidth(rng),distHeight(rng), radius(rng), colorCircle, z(rng));

        listeCercle[i] = cercle;

    }

    Background background = createBackground(nbCercle, listeCercle);

        std::random_device dev2;
    std::mt19937 rng2(dev());
    std::uniform_real_distribution<float> distWidth2(-300,WINDOW_WIDTH+300); 
    std::uniform_real_distribution<float> distHeight2(-300,WINDOW_HEIGHT+300);
    std::uniform_real_distribution<float> colorR2(0,20); 
    std::uniform_real_distribution<float> colorV2(0,20); 
    std::uniform_real_distribution<float> colorB2(0,20); 
    std::uniform_real_distribution<float> radius2(3,8);
    std::uniform_real_distribution<float> z2(30,60);

    int nbCercle2 = 200;
    Cercle listeCercle2[nbCercle2];

    for(int i = 0; i <= nbCercle; i++){

        ColorRGB colorCircle2 = createColor(colorR2(rng2)*0.01,colorV2(rng2)*0.01,colorB2(rng2)*0.01);

        Cercle cercle2 = createCercle(distWidth2(rng2),distHeight2(rng2), radius2(rng2), colorCircle2, -z2(rng2));

        listeCercle2[i] = cercle2;

    }

    Background background2 = createBackground(nbCercle2, listeCercle2);


    /*-------------------LEVEL 1 --------------------------------*/

    ColorRGB couleurPlateforme = createColor(0.05,0.05,0.05);

    Joueur joueur = creerJoueur(WINDOW_WIDTH/2+60, 400,10,30, 1, createColor(0.7,0.4,0.2));

    Joueur joueur1 = creerJoueur(WINDOW_WIDTH/2-30, 380,30,30, 2, createColor(0.4,0.4,0.6));

    Joueur joueur2 = creerJoueur(WINDOW_WIDTH/2+30, 380,40,20, 3, createColor(0.1,0.8,0.4));

    Arrive arrive = creerArrive(WINDOW_WIDTH/2+400, 525,joueur.largeur,joueur.hauteur,joueur.id,joueur.color);

    Arrive arrive1 = creerArrive(WINDOW_WIDTH/2+600, 377,joueur1.largeur,joueur1.hauteur,joueur1.id,joueur1.color);

    Arrive arrive2 = creerArrive(WINDOW_WIDTH/2+800, 520,joueur2.largeur,joueur2.hauteur,joueur2.id, joueur2.color);

    Camera camera = creerCamera(joueur.x, joueur.y);

    Plateforme plateforme = creerPlateforme(WINDOW_WIDTH/2, 1350, 5000,  WINDOW_HEIGHT*2, couleurPlateforme);

    Plateforme plateforme1 = creerPlateforme(WINDOW_WIDTH/2-300, 0, 3000, WINDOW_HEIGHT, couleurPlateforme);

    Plateforme plateforme2 = creerPlateforme(WINDOW_WIDTH/2-600, 500, 800,  WINDOW_HEIGHT, couleurPlateforme);

    Plateforme plateforme3 = creerPlateforme(WINDOW_WIDTH/2+400, 490, 200,  40, couleurPlateforme);

    Plateforme plateforme4 = creerPlateforme(WINDOW_WIDTH/2+800, 490, 200,  40, couleurPlateforme);

    Plateforme plateforme5 = creerPlateforme(WINDOW_WIDTH/2+2000, 500, 2000,  WINDOW_HEIGHT*3, couleurPlateforme);

    int tailleLvl1 = 6;

    int nbJoueurLvl1 = 3;

    Plateforme lvl1[tailleLvl1] = {plateforme1, plateforme, plateforme2, plateforme3, plateforme4, plateforme5};

    Joueur joueursLevel1[nbJoueurLvl1] = {joueur, joueur1, joueur2};

    Arrive arriveLevel1[nbJoueurLvl1] = {arrive, arrive1, arrive2};

    ColorRGB couleurBackgroundLevel1 = createColor(0.2,0.2,0.2);


    Level level1 = creerLevel(tailleLvl1, nbJoueurLvl1, lvl1, joueursLevel1, arriveLevel1, "Level 1", couleurBackgroundLevel1, 1);

    //printf("%s\n", level1.nom);

    /*----------------------LEVEL 2--------------------------------*/
    int tailleLvl2 = 5;

    int nbJoueurLvl2 = 3;

    ColorRGB couleurPlateformeLevel2 = createColor(0.05,0.05,0.05);

    Joueur joueurLevel2 = creerJoueur(WINDOW_WIDTH/2-300,310,15,25, 1, createColor(0.2,0.6,0.2));

    Joueur joueur1Level2 = creerJoueur(WINDOW_WIDTH/2-250,310,25,25, 2, createColor(0.9,0.3,0.2));

    Joueur joueur2Level2 = creerJoueur(WINDOW_WIDTH/2-350,310,50,10, 4, createColor(0.5,0.8,0.4));

    Joueur joueursLevel2[nbJoueurLvl2] = {joueurLevel2, joueur1Level2, joueur2Level2};

    Arrive arriveLevel2 = creerArrive(WINDOW_WIDTH/2+300,615,joueurLevel2.largeur,joueurLevel2.hauteur,joueurLevel2.id,joueurLevel2.color);

    Arrive arrive1Level2 = creerArrive(WINDOW_WIDTH/2+100,470,joueur1Level2.largeur,joueur1Level2.hauteur,joueur1Level2.id,joueur1Level2.color);

    Arrive arrive2Level2 = creerArrive(WINDOW_WIDTH/2+100,140,joueur2Level2.largeur,joueur2Level2.hauteur,joueur2Level2.id, joueur2Level2.color);

    Arrive listeArriveLevel2[nbJoueurLvl2] = {arriveLevel2, arrive1Level2, arrive2Level2};

    Plateforme plateformeLevel2 = creerPlateforme(WINDOW_WIDTH/2-300, 0, 150, 300, couleurPlateforme);

    Plateforme plateforme1Level2 = creerPlateforme(WINDOW_WIDTH/2, WINDOW_HEIGHT/2-50, 300, 100, couleurPlateformeLevel2);
    
    Plateforme plateforme2Level2 = creerPlateforme(WINDOW_WIDTH/2-50,WINDOW_HEIGHT/2-150,200, 150, couleurPlateformeLevel2);

    Plateforme plateforme3Level2 = creerPlateforme(WINDOW_WIDTH/2, WINDOW_HEIGHT/2-300, 300, 150, couleurPlateformeLevel2);

    Plateforme plateforme4Level2 = creerPlateforme(WINDOW_WIDTH/2+300, 0, 150, 1200, couleurPlateformeLevel2);

    ColorRGB couleurBackgroundLevel2 = createColor(0.2,0.2,0.2);

    Plateforme plateformesLevel2[tailleLvl2] = {plateformeLevel2,plateforme1Level2,plateforme2Level2,plateforme3Level2,plateforme4Level2};

    Level level2 = creerLevel(tailleLvl2, nbJoueurLvl2, plateformesLevel2, joueursLevel2, listeArriveLevel2, "Level 2", couleurBackgroundLevel2, 0.8);
    

    /*------------------LEVEL 3 --------------------------------------*/

    int tailleLvl0 = 100;

    int nbJoueurLvl0 = 1;


    Joueur joueurlevel0 = creerJoueur(WINDOW_WIDTH/2-200,110,10,30, 1, createColor(0.7,0.4,0.2));

    Arrive arrivelevel0 = creerArrive(WINDOW_WIDTH/2,940,joueurlevel0.largeur,joueurlevel0.hauteur,joueurlevel0.id,joueurlevel0.color);

    Plateforme plateformelevel0 = creerPlateforme(WINDOW_WIDTH/2-200,-100,200,WINDOW_HEIGHT/4,couleurPlateforme);

    Plateforme plateforme1level0 = creerPlateforme(WINDOW_WIDTH/2-400,0,200,WINDOW_HEIGHT*2,couleurPlateforme);

    Plateforme plateforme2level0 = creerPlateforme(WINDOW_WIDTH/2,-25,200,WINDOW_HEIGHT/2,couleurPlateforme);

    Plateforme plateforme3level0 = creerPlateforme(WINDOW_WIDTH/2+200,50,200,WINDOW_HEIGHT/2+WINDOW_HEIGHT/4,couleurPlateforme);

    Plateforme plateforme4level0 = creerPlateforme(WINDOW_WIDTH/2+400,150,200,WINDOW_HEIGHT,couleurPlateforme);

    Plateforme plateforme5level0 = creerPlateforme(WINDOW_WIDTH/2+600,200,200,WINDOW_HEIGHT*3,couleurPlateforme);

    Plateforme plateforme6level0 = creerPlateforme(WINDOW_WIDTH/2+470,720,60,60,couleurPlateforme);

    Plateforme plateforme7level0 = creerPlateforme(WINDOW_WIDTH/2-200,750,800,WINDOW_HEIGHT/2,couleurPlateforme);

    Plateforme plateforme8level0 = creerPlateforme(WINDOW_WIDTH/2+240,625,100,50,couleurPlateforme);

    Plateforme plateforme9level0 = creerPlateforme(WINDOW_WIDTH/2+240,875,100,50,couleurPlateforme);


    Plateforme plateformesLevel0[tailleLvl0] = {plateformelevel0,plateforme1level0,plateforme2level0,plateforme3level0,plateforme4level0,plateforme5level0,plateforme6level0,plateforme7level0,plateforme8level0,plateforme9level0};

    Joueur joueursLevel0[nbJoueurLvl0] = {joueurlevel0};

    Arrive arriveLevel0[nbJoueurLvl0] = {arrivelevel0};

    Level level3 = creerLevel(tailleLvl0, nbJoueurLvl0, plateformesLevel0, joueursLevel0, arriveLevel0, "Level 0", couleurBackgroundLevel2, 0.8);

    /*---------------------------------------- LEVEL 4 ------------------------------------------------*/

    int tailleLvl4 = 100;

    int nbJoueurLvl4 = 1;

    Joueur joueurlevel4 = creerJoueur(WINDOW_WIDTH/2,210,10,30, 1, createColor(0.7,0.4,0.2));

    Arrive arrivelevel4 = creerArrive(WINDOW_WIDTH/2+400,760,joueurlevel4.largeur,joueurlevel4.hauteur,joueurlevel4.id,joueurlevel4.color);

    Plateforme plateformelevel4 = creerPlateforme(WINDOW_WIDTH/2,-100,100,100,couleurPlateforme);

    Plateforme plateforme1level4 = creerPlateforme(WINDOW_WIDTH/2-200,100,80,70,couleurPlateforme);

    Plateforme plateforme2level4 = creerPlateforme(WINDOW_WIDTH/2-400,200,80,70,couleurPlateforme);

    Plateforme plateforme3level4 = creerPlateforme(WINDOW_WIDTH/2-250,360,80,70,couleurPlateforme);

    Plateforme plateforme4level4 = creerPlateforme(WINDOW_WIDTH/2-400,520,80,70,couleurPlateforme);

    Plateforme plateforme5level4 = creerPlateforme(WINDOW_WIDTH/2-200,690,80,70,couleurPlateforme);

    Plateforme plateforme6level4 = creerPlateforme(WINDOW_WIDTH/2,560,80,70,couleurPlateforme);

    Plateforme plateforme7level4 = creerPlateforme(WINDOW_WIDTH/2+100,350,80,70,couleurPlateforme);

    Plateforme plateforme8level4 = creerPlateforme(WINDOW_WIDTH/2+280,190,80,70,couleurPlateforme);

    Plateforme plateforme9level4 = creerPlateforme(WINDOW_WIDTH/2+450,345,80,70,couleurPlateforme);

    Plateforme plateforme10level4 = creerPlateforme(WINDOW_WIDTH/2+530,550,80,70,couleurPlateforme);

    Plateforme plateforme11level4 = creerPlateforme(WINDOW_WIDTH/2+400,690,80,70,couleurPlateforme);

    Plateforme plateformesLevel4[tailleLvl4] = {plateformelevel4,plateforme1level4,plateforme2level4,plateforme3level4,plateforme4level4,plateforme5level4,plateforme6level4,plateforme7level4,plateforme8level4,plateforme9level4,plateforme10level4,plateforme11level4};

    Joueur joueursLevel4[nbJoueurLvl4] = {joueurlevel4};

    Arrive arriveslevel4[nbJoueurLvl4] = {arrivelevel4};

    Level level4 = creerLevel(tailleLvl4, nbJoueurLvl4, plateformesLevel4, joueursLevel4, arriveslevel4, "Level 3", couleurBackgroundLevel2, 1);

    /*---------------------------LEVEL FIN---------------------------------------------*/

    int tailleLvlFin = 100;

    int nbJoueurLvlFin = 1;

    ColorRGB couleurPlateformeFin = createColor(0.2,0.8,0.2);
    ColorRGB couleurPlateformeFin1 = createColor(0.8,0.8,0.2);
    ColorRGB couleurPlateformeFin2 = createColor(0.8,0.2,0.2);


    Joueur joueurlevelFin = creerJoueur(WINDOW_WIDTH/2-200,500,10,30, 1, createColor(0.7,0.4,0.2));

    Arrive arrivelevelFin = creerArrive(WINDOW_WIDTH/2,940,joueurlevel0.largeur,joueurlevel0.hauteur,joueurlevel0.id,joueurlevel0.color);

    Plateforme plateforme0levelFin = creerPlateforme(WINDOW_WIDTH/2-200,WINDOW_HEIGHT/2,200,50,couleurPlateformeFin);
    Plateforme plateforme1levelFin = creerPlateforme(WINDOW_WIDTH/2-300,WINDOW_HEIGHT/2-175,50,400,couleurPlateformeFin);
    Plateforme plateforme2levelFin = creerPlateforme(WINDOW_WIDTH/2-200,WINDOW_HEIGHT/2-150,200,50,couleurPlateformeFin);
    Plateforme plateforme3levelFin = creerPlateforme(WINDOW_WIDTH/2,WINDOW_HEIGHT/2-175,50,400,couleurPlateformeFin1);
    Plateforme plateforme4levelFin = creerPlateforme(WINDOW_WIDTH/2+125,WINDOW_HEIGHT/2-175,50,400,couleurPlateformeFin2);
    Plateforme plateforme5levelFin = creerPlateforme(WINDOW_WIDTH/2+250,WINDOW_HEIGHT/2,250,50,couleurPlateformeFin2);
    Plateforme plateforme6levelFin = creerPlateforme(WINDOW_WIDTH/2+350,WINDOW_HEIGHT/2-175,50,400,couleurPlateformeFin2);


    Plateforme plateformesLevelFin[tailleLvl0] = {plateforme0levelFin, plateforme1levelFin, plateforme2levelFin, plateforme3levelFin, plateforme4levelFin, plateforme5levelFin, plateforme6levelFin};

    Joueur joueursLevelFin[nbJoueurLvlFin] = {joueurlevelFin};

    Arrive arrivesLevelFin[nbJoueurLvlFin] = {arrivelevelFin};

    ColorRGB couleurBackgroundFin = createColor(0.3,0.5,0.8);


    Level levelFin = creerLevel(tailleLvlFin, nbJoueurLvlFin, plateformesLevelFin, joueursLevelFin, arrivesLevelFin, "Level FIn", couleurBackgroundFin, 1);

    /*-----------------------------------*/


    int nbLevel = 5;


    Level jeuxGeorges[nbLevel] = {level1, level2, level3, level4, levelFin};


    QuadTree qt;

    QuadTree* result;

    while(gameLoop) 
    {
     
        //printf("ca marche\n");

        if(!isQuadTreeCreated){
            
            qt = creerQuadTree((WINDOW_WIDTH)/2,  (WINDOW_HEIGHT)/2, WINDOW_WIDTH+2000, WINDOW_HEIGHT+2000, new Plateforme[jeuxGeorges[levelActif].taille], jeuxGeorges[levelActif].taille, jeuxGeorges[levelActif].taille,  0);
            
            result = nullptr;

            for(int i = 0; i < jeuxGeorges[levelActif].taille; i++){
                //printf("le rect bg : %f\n", jeuxGeorges[0].lvl[i].x);
                insererPlateforme(&qt, jeuxGeorges[levelActif].lvl[i], 3);

            }
            isQuadTreeCreated = true;
        }



        
        float startTime = (float)SDL_GetTicks()/1000.f;

        deltaTime = startTime - oldTimeSinceStart;
        oldTimeSinceStart = startTime;

        if(FRAMEDELAY > deltaTime){
            SDL_Delay(FRAMEDELAY - deltaTime);
        }
        

        //printf("rectangle : %i, \n", donnerZoneQuadTree(qt,plateforme3));

        //checkEvenements(&gameLoop, &joueur, &plateforme, deltaTime);

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        

        result = chercherPlateforme(qt, jeuxGeorges[levelActif].joueurs[0]);

        if(result){

            //printf("quadTree nb : %i\n", result->nbPlateforme);   

            checkCollision(result->plateformes, jeuxGeorges[levelActif].joueurs, result->nbPlateforme, jeuxGeorges[levelActif].nbJoueurs, deltaTime); 
        
        }



        

       glScalef(jeuxGeorges[levelActif].scale,jeuxGeorges[levelActif].scale,0);

       afficherBackground(jeuxGeorges[levelActif], WINDOW_WIDTH, WINDOW_HEIGHT);

        updateBackground(background2, camera);

    
       glPushMatrix();
       
       cameraTranslate(camera);

       //updateBackground(background, camera);

        for(int i = 0; i < jeuxGeorges[levelActif].nbJoueurs; i++){
            afficherJoueur(jeuxGeorges[levelActif].joueurs[i], jeuxGeorges[levelActif]);
        }

        for(int i = 0; i < jeuxGeorges[levelActif].nbJoueurs; i++){
            afficherArrive(jeuxGeorges[levelActif].arrives[i]);
            updateArrive(&(jeuxGeorges[levelActif].arrives[i]), &(jeuxGeorges[levelActif].joueurs[0]), &jeuxGeorges[levelActif]);
        }

       for(int i = 0; i < jeuxGeorges[levelActif].taille; i++){
            
            afficherPlateforme(jeuxGeorges[levelActif].lvl[i]);
            updatePlateforme(&(jeuxGeorges[levelActif].lvl[i]), &(jeuxGeorges[levelActif].joueurs[0]), deltaTime);
            //printf("velocite : %f\n", joueur.velocite);

        }

        
        checkEvenements(&gameLoop, &(jeuxGeorges[levelActif].joueurs[0]), jeuxGeorges[levelActif], deltaTime,&ismenu);

        updateJoueur(&(jeuxGeorges[levelActif].joueurs[0]), &camera, deltaTime);


        if(jeuxGeorges[levelActif].joueurs[0].y <= -200){
            respawn(&jeuxGeorges[levelActif].joueurs[0]);
        }

        //j'affiche la quadTree
        
        /*drawQuadTree(qt);
         if(result){
               
        //Je colore en rouge les plateformes pour lesquels je calcule les collisions
            for(int i = 0; i < result->nbPlateforme; i++){
     
                result->plateformes[i].color = createColor(1,0,0);
                afficherPlateforme(result->plateformes[i]);

            }
         }*/

        updateBackground(background, camera);


        if(verifieVictoire(jeuxGeorges[levelActif])){
            //printf("victory\n");
            //SDL_Delay(1000);
            
            //gameLoop = 0;
            isTransitionFinished = false;

            isQuadTreeCreated = false;

            if(jeuxGeorges[levelActif].transitionY < WINDOW_HEIGHT-300){
                afficherTransitionIn(WINDOW_WIDTH, WINDOW_HEIGHT, &jeuxGeorges[levelActif], deltaTime);
                jeuxGeorges[levelActif].transitionY += 1200*deltaTime;
            }else{
                levelActif++;
            }
        }

        if(isTransitionFinished == false && jeuxGeorges[levelActif-1].transitionY >= WINDOW_HEIGHT-300){
            afficherTransitionIn(WINDOW_WIDTH, WINDOW_HEIGHT, &jeuxGeorges[levelActif-1], deltaTime);
            jeuxGeorges[levelActif-1].transitionY += 1200*deltaTime;
            
            if(jeuxGeorges[levelActif-1].transitionY >= WINDOW_HEIGHT+600){
                
                isTransitionFinished = true;
            }

        }

        glPopMatrix();

        SDL_GL_SwapWindow(window);

    

    } 


    SDL_FreeSurface(imageTitre);
    /* Liberation des ressources associees a la SDL */ 
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

