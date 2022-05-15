#include "headers/menu.h"
#include "headers/systeme.h"

void DrawMenu(int menu,GLuint textureID[380],int windowWidth, int windowHeight){
	int r1,r2,r3,v1,v2,v3,b1,b2,b3;
	drawSquare2(1, 255,  255, 255 , -500, -500.,1000., 1000. );
	drawSquare2(0, r1,  v1, b1 , -130., -40.,80., 80. );
	drawSquare2(0, r2,  v2, b2 , -40., -40.,80., 80. );
	drawSquare2(0, r3,  v3, b3 , 50., -40.,80, 80 );
		if(menu<5){
		
		//CASE 1//

		//P//
		drawSquare2(1,r1,v1,b1,-122,-60+52,3,18);
		drawSquare2(1,r1,v1,b1,-119,-60+58,6,3);
		drawSquare2(1,r1,v1,b1,-119,-60+67,6,3);
		drawSquare2(1,r1,v1,b1,-113,-60+61,3,6);
		//L//
		drawSquare2(1,r1,v1,b1,-104,-60+52,3,18);
		drawSquare2(1,r1,v1,b1,-101,-60+52,9,3);
		//A//
		drawSquare2(1,r1,v1,b1,-86,-60+52,3,18);
		drawSquare2(1,r1,v1,b1,-83,-60+67,6,3);
		drawSquare2(1,r1,v1,b1,-83,-60+58,6,3);
		drawSquare2(1,r1,v1,b1,-78,-60+52,3,18);
		//Y//
		drawSquare2(1,r1,v1,b1,-69,-60+67,3,3);
		drawSquare2(1,r1,v1,b1,-66.5,-60+64,3,3);
		drawSquare2(1,r1,v1,b1,-63.5,-60+64,3,3);
		drawSquare2(1,r1,v1,b1,-62,-60+67,3,3);
		drawSquare2(1,r1,v1,b1,-65,-60+52,3,12);
	

		//CASE 2//
	

		//L//
		drawSquare2(1,r2,v2,b2,-39,-60+52,3,18);
		drawSquare2(1,r2,v2,b2,-36,-60+52,9,3);
		//E//
		drawSquare2(1,r2,v2,b2,-26,-60+52,3,18);
		drawSquare2(1,r2,v2,b2,-23,-60+52,9,3);
		drawSquare2(1,r2,v2,b2,-23,-60+67,9,3);
		drawSquare2(1,r2,v2,b2,-23,-60+59.5,6,3);
		//V//
		drawSquare2(1,r2,v2,b2,-13,-60+58,3,12);
		drawSquare2(1,r2,v2,b2,-11.5,-60+55,3,3);
		drawSquare2(1,r2,v2,b2,-8.5,-60+52,3,3);
		drawSquare2(1,r2,v2,b2,-5.5,-60+55,3,3);
		drawSquare2(1,r2,v2,b2,-4,-60+58,3,12);
		//E//
		drawSquare2(1,r2,v2,b2,0,-60+52,3,18);
		drawSquare2(1,r2,v2,b2,3,-60+52,9,3);
		drawSquare2(1,r2,v2,b2,3,-60+67,9,3);
		drawSquare2(1,r2,v2,b2,3,-60+59.5,6,3);
		//L//
		drawSquare2(1,r2,v2,b2,13,-60+52,3,18);
		drawSquare2(1,r2,v2,b2,16,-60+52,9,3);

		//S//
		drawSquare2(1,r2,v2,b2,26,-60+52,12,3);
		drawSquare2(1,r2,v2,b2,35,-60+55,3,4.5);
		drawSquare2(1,r2,v2,b2,26,-60+59.5,12,3);
		drawSquare2(1,r2,v2,b2,26,-60+62.5,3,4.5);
		drawSquare2(1,r2,v2,b2,26,-60+67,12,3);

	
		//CASE 3//

		//C//
		drawSquare2(1,r3,v3,b3,51,-60+58,3,6);
		drawSquare2(1,r3,v3,b3,54,-60+55,3,3);
		drawSquare2(1,r3,v3,b3,54,-60+64,3,3);
		drawSquare2(1,r3,v3,b3,57,-60+67,6,3);
		drawSquare2(1,r3,v3,b3,57,-60+52,6,3);
		//R//
		drawSquare2(1,r3,v3,b3,64,-60+52,3,18);
		drawSquare2(1,r3,v3,b3,67,-60+67,6,3);
		drawSquare2(1,r3,v3,b3,67,-60+58,6,3);
		drawSquare2(1,r3,v3,b3,73,-60+61,3,6);
		drawSquare2(1,r3,v3,b3,73,-60+52,3,6);
		//E//
		drawSquare2(1,r3,v3,b3,77,-60+52,3,18);
		drawSquare2(1,r3,v3,b3,80,-60+52,9,3);
		drawSquare2(1,r3,v3,b3,80,-60+67,9,3);
		drawSquare2(1,r3,v3,b3,80,-60+59.5,6,3);
		//D//
		drawSquare2(1,r3,v3,b3,90,-60+52,3,18);
		drawSquare2(1,r3,v3,b3,93,-60+52,3,3);
		drawSquare2(1,r3,v3,b3,96,-60+55,3,3);
		drawSquare2(1,r3,v3,b3,99,-60+58,3,6);
		drawSquare2(1,r3,v3,b3,96,-60+64,3,3);
		drawSquare2(1,r3,v3,b3,93,-60+67,3,3);
		//I//
		drawSquare2(1,r3,v3,b3,103,-60+67,12,3);
		drawSquare2(1,r3,v3,b3,103,-60+52,12,3);
		drawSquare2(1,r3,v3,b3,107.5,-60+55,3,12);
		//T//
		drawSquare2(1,r3,v3,b3,116,-60+67,12,3);
		drawSquare2(1,r3,v3,b3,120.5,-60+52,3,18);
	}
}


void DrawIntro(int * img, int * intro){
	
	//carrée pour tout effacer 
	glEnable(GL_TEXTURE_2D);
    // FIXME : Bind texture
    /* Dessin du quad */
    glColor3ub(50,50,50);
    glBindTexture(GL_TEXTURE_2D, *img);
    glBegin(GL_QUADS);
      glColor3f(1,1,1);

      glTexCoord2f(0, 1);
      glVertex2f(-150, -100);

      glTexCoord2f(1, 1);
      glVertex2f(150, -100);

      glTexCoord2f(1, 0);
      glVertex2f(150, 100);

      glTexCoord2f(0, 0);
      glVertex2f(-150, 100);

    glEnd();


  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_TEXTURE_2D);
  *img=*img+1;
  
if (*img==371)
{
	*intro=*intro+4;

}

}

void DrawIntrolvl(int * img){
	
	//carrée pour tout effacer 
	glEnable(GL_TEXTURE_2D);
    // FIXME : Bind texture
    /* Dessin du quad */
    glColor3ub(50,50,50);
    glBindTexture(GL_TEXTURE_2D, *img);
    glBegin(GL_QUADS);
      glColor3f(1,1,1);

      glTexCoord2f(0, 1);
      glVertex2f(-150, -100);

      glTexCoord2f(1, 1);
      glVertex2f(150, -100);

      glTexCoord2f(1, 0);
      glVertex2f(150, 100);

      glTexCoord2f(0, 0);
      glVertex2f(-150, 100);

    glEnd();


  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_TEXTURE_2D);
  *img=*img+1;
  
}