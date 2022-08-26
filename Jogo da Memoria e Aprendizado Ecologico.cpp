//Alunos: Paulo Cesar Pereira Gomes; Eduardo de Oliveira ; Aurelio Jose ; Joao Paulo Brites;

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include <math.h>


float translatex = 47;
float translatey = 2;
int auxiliar;
int current_view = 0;
int clicou = 0;
int auxRotate = 0;
const int VIEW_MENU = 0;
const int VIEW_GAME = 1;
const int VIEW_GAME_END = 2;
GLfloat win=0.0,win2=0.0;
GLfloat panX=0.0, panY=0.0;

//Controlador de qual tela o jogo vai mostrar
int controllerMenu = 0; 
//Vetores com as cores e indicação se as cartas estão viradas
int ordem[10];
float xStep = 10;
float BcolorR[] = {1.0, 0.0, 0.0, 1.0, 0.556900};
float BcolorG[] = {0.0, 0.5, 0.0, 0.5, 0.419600};
float BcolorB[] = {0.0, 0.0, 1.0, 0.0, 0.137300};
float ang[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float colorR[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float colorG[] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
float colorB[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
bool numShow[] = {true, true, true, true, true, true, true, true, true, true};
bool cardVirado[] = {false, false, false, false, false, false, false, false, false, false};
bool controllerText[] = {false, false, false, false, false}; 

//Declara??es das funções
void Inicializa(void);
void DesenhaTexto(void *font, char vidas);
void DesenhaObstaculo();
void DesenhaJogo();
void TeclasEspeciais(int key, int x, int y);
void Teclado (unsigned char key, int x, int y);
void Desenha();
void DesenhaMenu();
void Processamento();
void sortearOrdem();
void Anima(int value);
void AnimaReseta(int value);
void animaDelay(int value);
void drawCircle(int, int, int, int, int);
void drawTextStroke(void*, char*);
void EspecificaParametrosVisualizacao(void);
void DesenhaEcoBag();
void DesenhaSacoDeLixo();
void DesenhaTorneira();
void DesenhaPinheiro();
void DesenhaRaio();
void desenhaObjetos(int x);
void textosObjetos(int x);
void Desenhaendgame();

void Inicializa(void){
	sortearOrdem();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  // o uso deste comando garante que o zoom 
	                   // seja feito de forma absoluta e n�o relativa
	//gluOrtho2D (-win, win +200.0, -win+ 0.0, win+200.0);
	gluOrtho2D(0.0,200.0,0.0,200.0);
}



void DesenhaTexto(void *font, char vidas) 
{
	// Exibe caractere a caractere
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, vidas); 
}

void animaDelay(int delayValue)
{
	auxRotate += delayValue;
	if(auxRotate > 50){
		Processamento();
	} else {
		glutTimerFunc(100,animaDelay, delayValue);
	}
}

void Anima(int value)
{
	ang[value] += xStep;

	
	if(ang[value] >= 90 && auxiliar<2){
		colorR[value] = BcolorR[ordem[value]];
        colorG[value] = BcolorG[ordem[value]];
        colorB[value] = BcolorB[ordem[value]];
	} 
	if(ang[value] >= 180) {
		ang[value] = 180;
		if(clicou >= 2){
		animaDelay(5);
		}
	} else {
		glutTimerFunc(50,Anima, value);
	}
	glutPostRedisplay();
}

void AnimaReseta(int value)
{
	
	ang[value] -= xStep;

	
	if(ang[value] < 90){
		colorR[value] = 0.0;
        colorG[value] = 0.2;
        colorB[value] = 0.0;
	} 
	if(ang[value] <= 0) {
		ang[value] = 0;
	} else {
		glutTimerFunc(50,AnimaReseta, value);
	}
	glutPostRedisplay();
}

void sortearOrdem(){
	int complete = 0;
	int oneCount= 0;
	int twoCount= 0;
	int threeCount= 0;
	int fourCount= 0;
	int fiveCount= 0;
	int aux = 0;
	srand ( time(NULL) );
	while(complete < 10){
		aux = (rand() % 5) + 1;
		if(aux == 1){
			if(oneCount < 2){
				ordem[complete] = aux;
				complete++;
				oneCount++;
			}
			
		} else if(aux == 2){
			if(twoCount < 2){
				ordem[complete] = aux;
				complete++;
				twoCount++;
			}
		} else if(aux == 3){
			if(threeCount < 2){
				ordem[complete] = aux;
				complete++;
				threeCount++;
			}
		} else if(aux == 4){
			if(fourCount < 2){
				ordem[complete] = aux;
				complete++;
				fourCount++;
			}
		} else {
			if(fiveCount < 2){
				ordem[complete] = aux;
				complete++;
				fiveCount++;
			}
		}
		
	}
	
	//Vizualizando os valores sorteados
	for(int i = 0; i<10; i++){
		printf("Item[%d]: %d\n", i,ordem[i]);
	}
	
}

void DesenhaJogo(){
	current_view= VIEW_GAME;
	//pra ajudar na mudança da cor do plano de fundo
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();
	glBegin(GL_POINTS);
		glColor3f(1.0f, 5.0f, 0.0f);
		glVertex2f(55.0f,110.0f);              
	glEnd();
	
	//Primeira linha
	//7
	glPushMatrix();
	glPushMatrix();
		glTranslatef(55, 170, 0.0f);
		glRotatef(ang[7],0.0f,1.0f,0.0f);
		glTranslatef(-55, -170, 0.0f);
	glBegin(GL_QUADS);
		glColor3f(colorR[7], colorG[7], colorB[7]);
		glVertex2f(35.0f, 190.0f);	glVertex2f(75.0f, 190.0f);
		glVertex2f(75.0f, 150.0f); 	glVertex2f(35.0f, 150.0f);
	glEnd();
	glPopMatrix();
	//Desenho da carta 7:
	if(numShow[7]==false && ang[7] > 100){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180 + ang[7],0.0f,1.0f,0.0f);
		if(ordem[7] == 3){
			glTranslatef(50, 173, 0.0f);
		} else glTranslatef(52, 170, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		desenhaObjetos(ordem[7]);
		glPopMatrix();
	}
	//8
	glPushMatrix();
		glTranslatef(100, 170, 0.0f);
		glRotatef(ang[8],0.0f,1.0f,0.0f);
		glTranslatef(-100, -170, 0.0f);
	glBegin(GL_QUADS);	
		glColor3f(colorR[8], colorG[8], colorB[8]);
		glVertex2f(80.0f, 190.0f);	glVertex2f(120.0f, 190.0f);
		glVertex2f(120.0f, 150.0f);	glVertex2f(80.0f, 150.0f);
	glEnd();
	glPopMatrix();
	//Desenho da carta 8:
	if(numShow[8]==false && ang[8] > 100){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180 + ang[8],0.0f,1.0f,0.0f);
		if(ordem[8] == 3){
			glTranslatef(95, 173, 0.0f);
		} else glTranslatef(97, 170, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		desenhaObjetos(ordem[8]);
		glPopMatrix();
	}
	//9
	glPushMatrix();
		glTranslatef(145, 170, 0.0f);
		glRotatef(ang[9],0.0f,1.0f,0.0f);
		glTranslatef(-145, -170, 0.0f);
	glBegin(GL_QUADS);	
		glColor3f(colorR[9], colorG[9], colorB[9]);
		glVertex2f(125.0f, 190.0f);	glVertex2f(165.0f, 190.0f);
		glVertex2f(165.0f, 150.0f);	glVertex2f(125.0f, 150.0f);
	glEnd();
	glPopMatrix();
	//Desenho da carta 9:
	if(numShow[9]==false && ang[9] > 100){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180 + ang[9],0.0f,1.0f,0.0f);
		if(ordem[9] == 3){
			glTranslatef(140, 173, 0.0f);
		} else glTranslatef(142, 170, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		desenhaObjetos(ordem[9]);
		glPopMatrix();
	}
	//Segunda linha
	//4
	glPushMatrix();
		glTranslatef(55, 125, 0.0f);
		glRotatef(ang[4],0.0f,1.0f,0.0f);
		glTranslatef(-55, -125, 0.0f);
	glBegin(GL_QUADS);	
		glColor3f(colorR[4], colorG[4], colorB[4]);
		glVertex2f(35.0f, 145.0f);	glVertex2f(75.0f, 145.0f);
		glVertex2f(75.0f, 105.0f); 	glVertex2f(35.0f, 105.0f);
	glEnd();
	glPopMatrix();
	//Desenho da carta 4:
	if(numShow[4]==false && ang[4] > 100){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180 + ang[4],0.0f,1.0f,0.0f);
		if(ordem[4] == 3){
			glTranslatef(50, 128, 0.0f);
		} else glTranslatef(52, 125, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		desenhaObjetos(ordem[4]);
		glPopMatrix();
	}
	//5	
	glPushMatrix();
		glTranslatef(100, 125, 0.0f);
		glRotatef(ang[5],0.0f,1.0f,0.0f);
		glTranslatef(-100, -125, 0.0f);
	glBegin(GL_QUADS);	
		glColor3f(colorR[5], colorG[5], colorB[5]);
		glVertex2f(80.0f, 145.0f);	glVertex2f(120.0f, 145.0f);
		glVertex2f(120.0f, 105.0f); glVertex2f(80.0f, 105.0f);
	glEnd();
	glPopMatrix();
	//Desenho da carta 5:
	if(numShow[5]==false && ang[5] > 100){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180 + ang[5],0.0f,1.0f,0.0f);
		if(ordem[5] == 3){
			glTranslatef(95, 128, 0.0f);
		} else glTranslatef(97, 125, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		desenhaObjetos(ordem[5]);
		glPopMatrix();
	}
	//6
	glPushMatrix();
		glTranslatef(145, 125, 0.0f);	
		glRotatef(ang[6],0.0f,1.0f,0.0f);
		glTranslatef(-145, -125, 0.0f);
	glBegin(GL_QUADS);	
		glColor3f(colorR[6], colorG[6], colorB[6]);
		glVertex2f(125.0f, 145.0f);	glVertex2f(165.0f, 145.0f);
		glVertex2f(165.0f, 105.0f); glVertex2f(125.0f, 105.0f);
	glEnd();
	glPopMatrix();
	//Desenho da carta 6:
	if(numShow[6]==false && ang[6] > 100){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180 + ang[6],0.0f,1.0f,0.0f);
		if(ordem[6] == 3){
			glTranslatef(140, 128, 0.0f);
		} else glTranslatef(142, 125, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		desenhaObjetos(ordem[6]);
		glPopMatrix();
	}
	//Terceira linha
	//1	
	glPushMatrix();
		glTranslatef(55, 80, 0.0f);	
		glRotatef(ang[1],0.0f,1.0f,0.0f);
		glTranslatef(-55, -80, 0.0f);	
	glBegin(GL_QUADS);	
		glColor3f(colorR[1], colorG[1], colorB[1]);
		glVertex2f(35.0f, 100.0f);	glVertex2f(75.0f, 100.0f);
		glVertex2f(75.0f, 60.0f); 	glVertex2f(35.0f, 60.0f);
	glEnd();
	glPopMatrix();
	//Desenho da carta 1:
	if(numShow[1]==false && ang[1] > 100){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180 + ang[1],0.0f,1.0f,0.0f);
		if(ordem[1] == 3){
			glTranslatef(50, 83, 0.0f);
		} else glTranslatef(52, 80, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		desenhaObjetos(ordem[1]);
		glPopMatrix();
	}
	//2	
	glPushMatrix();
		glTranslatef(100, 80, 0.0f);
		glRotatef(ang[2],0.0f,1.0f,0.0f);
		glTranslatef(-100, -80, 0.0f);
	glBegin(GL_QUADS);	
		glColor3f(colorR[2], colorG[2], colorB[2]);
		glVertex2f(80.0f, 100.0f);	glVertex2f(120.0f, 100.0f);
		glVertex2f(120.0f, 60.0f); 	glVertex2f(80.0f, 60.0f);
	glEnd();
	glPopMatrix();
	//Desenho da carta 2:
	if(numShow[2]==false && ang[2] > 100){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180 + ang[2],0.0f,1.0f,0.0f);
		if(ordem[2] == 3){
			glTranslatef(95, 83, 0.0f);
		} else glTranslatef(97, 80, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		desenhaObjetos(ordem[2]);
		glPopMatrix();
	}
	
	//3
	glPushMatrix();
		glTranslatef(145, 80, 0.0f);
		glRotatef(ang[3],0.0f,1.0f,0.0f);
		glTranslatef(-145, -80, 0.0f);
	glBegin(GL_QUADS);	
		glColor3f(colorR[3], colorG[3], colorB[3]);
		glVertex2f(125.0f, 100.0f);	glVertex2f(165.0f, 100.0f);
		glVertex2f(165.0f, 60.0f); 	glVertex2f(125.0f, 60.0f);
	glEnd();
	glPopMatrix();
	//Desenho da carta 3:
	if(numShow[3]==false && ang[3] > 100){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180 + ang[3],0.0f,1.0f,0.0f);
		if(ordem[3] == 3){
			glTranslatef(140, 83, 0.0f);
		} else glTranslatef(142, 80, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		desenhaObjetos(ordem[3]);
		glPopMatrix();
	}
	//Quarta linha	
	//0
	glPushMatrix();
		glTranslatef(100, 35, 0.0f);
		glRotatef(ang[0],0.0f,1.0f,0.0f);
		glTranslatef(-100, -35, 0.0f);
	glBegin(GL_QUADS);	
		glColor3f(colorR[0], colorG[0], colorB[0]);
		glVertex2f(80.0f, 55.0f);	glVertex2f(120.0f, 55.0f);
		glVertex2f(120.0f, 15.0f); 	glVertex2f(80.0f, 15.0f);
	glEnd();
	glPopMatrix();
	//Desenho da carta 0:
	if(numShow[0]==false && ang[0] > 100){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180 + ang[0],0.0f,1.0f,0.0f);
		if(ordem[0] == 3){
			glTranslatef(95, 38, 0.0f);
		} else glTranslatef(97, 35, 0.0f);
		
		glScalef(1.0, 1.0, 1.0);
		desenhaObjetos(ordem[0]);
		glPopMatrix();
	}
	
	glColor3f(1.0f, 1.0f, 1.0f);

	if(numShow[0]){
		glRasterPos2f(97,32);
		DesenhaTexto(GLUT_BITMAP_9_BY_15, '0');
	}
	
	if(numShow[1]){
		glRasterPos2f(52,77);
		DesenhaTexto(GLUT_BITMAP_9_BY_15, '1');
	}
	
	if(numShow[2]){
		glRasterPos2f(97,77);
		DesenhaTexto(GLUT_BITMAP_9_BY_15, '2');
	}
	
	if(numShow[3]){
		glRasterPos2f(141,77);
		DesenhaTexto(GLUT_BITMAP_9_BY_15, '3');
	}
	
	if(numShow[4]){
		glRasterPos2f(52,122);
		DesenhaTexto(GLUT_BITMAP_9_BY_15, '4');
	}
	
	if(numShow[5]){
		glRasterPos2f(97,122);
		DesenhaTexto(GLUT_BITMAP_9_BY_15, '5');
	}

	if(numShow[6]){
		glRasterPos2f(141,122);
		DesenhaTexto(GLUT_BITMAP_9_BY_15, '6');
	}
	
	if(numShow[7]){
		glRasterPos2f(52,167);
		DesenhaTexto(GLUT_BITMAP_9_BY_15, '7');
	}
	
	if(numShow[8]){
		glRasterPos2f(97,167);
		DesenhaTexto(GLUT_BITMAP_9_BY_15, '8');
	}
	
	if(numShow[9]){
		glRasterPos2f(141,167);
		DesenhaTexto(GLUT_BITMAP_9_BY_15, '9');
	}
	
	//Textos que aparecem quando o usuário acerta uma dupla de cartas
	if(controllerText[0]){
		textosObjetos(1);
	}
	if(controllerText[1]){
		textosObjetos(2);
	}
	if(controllerText[2]){
		textosObjetos(3);
	}
	if(controllerText[3]){
		textosObjetos(4);
	}
	if(controllerText[4]){
		textosObjetos(5);
	}
	//Fim dos textos

	glPopMatrix();
	
	glTranslatef(translatex, translatey, 0.0f);
	glPopMatrix();
	
	
	glFlush();
}

void TeclasEspeciais(int key, int x, int y)
{
	if(current_view==VIEW_GAME)
   {
   		if(key == GLUT_KEY_UP) {
   	 	
   	 	   win -= 20;
   	 	   win2+=20;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D (-panX, panY+200, -win, win2+200);		
    	}
    	
    	if(key== GLUT_KEY_DOWN) {
     	  
     	  	
     	  	win += 20;
     	  	win2-=20;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D (-panX, panY+200, -win, win2+200);  
    	}
    	///poscionar o camera em cima da carta
    	if(key== GLUT_KEY_LEFT) {
     	  
     	  	panX += 20;
     	  	panY -= 20;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D (-panX, panY+200, -win, win2+200);
		   
           
    	} 
    	if(key== GLUT_KEY_RIGHT) {
     	  
     	  	panX-= 20;
     	  	panY += 20;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D (-panX, panY+200, -win, win2+200);
		   
           
    	} 
		
		 if(key== GLUT_KEY_PAGE_DOWN  ) {
     	  
     	  	panX+= 20;
     	  	panY += 20;
     	  	win+=20;
     	  	win2+=20;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D (-panX, panY+200, -win, win2+200);
		   
           
    	}   
    	
		if(key== GLUT_KEY_PAGE_UP ) {
     	  
     	  	panX -= 20;
     	  	panY -= 20;
     	  	win  -= 20;
     	  	win2 -=20;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D (-panX, panY+200, -win, win2+200);    
    	}
	}
	glutPostRedisplay();
}

void Processamento()
{
	auxiliar = 0;
	clicou = 0;
	int i,C;
	int aux1[2];
	for(i=0;i<10;i++)
	{
		if(!numShow[i] && (auxiliar < 2))
		{
			if(!cardVirado[i]){
				aux1[auxiliar] = i;
				auxiliar++;
			}	
		} 
	}
	
		if( !numShow[0] && !numShow[1]  && !numShow[2]   && !numShow[3]   && !numShow[4]  && !numShow[5]   
			&& !numShow[6]  && !numShow[7]  && !numShow[8]  && !numShow[9] )   //endgame
			{
	 				glutDisplayFunc(Desenhaendgame);
			}
		
	if(auxiliar==2)
	{
		auxiliar = 0;
		auxRotate = 0;
		if(ordem[aux1[0]] != ordem[aux1[1]]){
			for(i=0;i<2;i++)
			{
				glutTimerFunc(50,AnimaReseta, aux1[i]);
				numShow[aux1[i]]=true;	
			}
		} else {
			cardVirado[aux1[0]] = true;
			cardVirado[aux1[1]] = true;
			controllerText[ordem[aux1[0]]-1] = true;
		}
	}	
}

void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	switch(key){
		case 96:
		case 48:
			clicou++;
			numShow[0] = false;
			glutTimerFunc(150, Anima, 0);
        	break;
        case 97:
        case 49:
        	clicou++;
        	numShow[1] = false;
        	glutTimerFunc(150, Anima, 1);
  
        	break;
        case 98:
        case 50:
        	clicou++;
        	numShow[2] = false;
        	glutTimerFunc(150, Anima, 2);
        	break;
        case 99:
        case 51:
        	clicou++;
        	numShow[3] = false;
        	glutTimerFunc(150, Anima, 3);
        	break;	
        case 100:
        case 52:
        	clicou++;
        	numShow[4] = false;
        	glutTimerFunc(150, Anima, 4);
        	break;
        case 101:
        case 53:
        	clicou++;
        	numShow[5] = false;
        	glutTimerFunc(150, Anima, 5);
        	break;
        case 102:
        case 54:
        	clicou++;
        	numShow[6] = false;
        	glutTimerFunc(150, Anima, 6);
        	break;
        case 103:
        case 55:
        	clicou++;
        	numShow[7] = false;
        	glutTimerFunc(150, Anima, 7);
        	break;
        case 104:
        case 56:
        	clicou++;
        	numShow[8] = false;
        	glutTimerFunc(150, Anima, 8);
        	break;
        case 105:
        case 57:
        	clicou++;
        	numShow[9] = false;
        	glutTimerFunc(150, Anima, 9);
        	break;
       
       case 114:
       case  82:
       	   glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D(0.0,200.0,0.0,200.0);
           break;
           
       case 106:
	   case 74:
	       
	    	break;
        default:
        	break;
    }
	glutPostRedisplay();
}

void Desenhaendgame(){
	current_view =  VIEW_GAME_END; //2
	glClearColor(0.1, 0.1, 0.1, 1.000000);
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.309800, 0.184300, 0.309800, 0.000000);
	glPushMatrix();	
		glTranslatef(10, 150, 0);   //posiçao do texto na tela
		glScalef(0.09, 0.09, 0.09); // diminui o tamanho do fonte
		glLineWidth(2); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10,"  PARABENS VOCE GANHOU ");
	glPopMatrix();
	
	glPushMatrix();	
		glTranslatef(10, 130, 0);   //posiçao do texto na tela
		glScalef(0.09, 0.09, 0.09); // diminui o tamanho do fonte
		glLineWidth(2); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10,"  E APRENDEU MAIS SOBRE  ");
	glPopMatrix();
	
	glPushMatrix();	
		glTranslatef(10, 110, 0);   //posiçao do texto na tela
		glScalef(0.09, 0.09, 0.09); // diminui o tamanho do fonte
		glLineWidth(2); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10,"   O MEIO AMBIENTE!!! ");
	glPopMatrix();
	
	glPushMatrix();	
		glTranslatef(10, 40, 0);   //posiçao do texto na tela
		glScalef(0.05, 0.05, 0.05); // diminui o tamanho do fonte
		glLineWidth(1); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10," Esc para finalizar o game,");
	glPopMatrix();

	glPushMatrix();	
		glTranslatef(10, 30, 0);   //posiçao do texto na tela
		glScalef(0.05, 0.05, 0.05); // diminui o tamanho do fonte
		glLineWidth(1); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10,"botao direito do mouse para reiniciar");
	glPopMatrix();
  
	glFlush();	
}

void Desenha(){
	// Controlador de qual parte do jogo mostrar
	switch(controllerMenu){
		case 0: 
			DesenhaMenu();
			break;
		case 1:
			DesenhaJogo();
			break;
		case 2:
			Desenhaendgame();
			break;
		default:
			exit(0);
	}
	glutSwapBuffers();
}

void DesenhaMenu(){
	current_view = VIEW_MENU;
	glClearColor(0.1, 0.1, 0.1, 1.000000);
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.309800, 0.184300, 0.309800, 0.000000);
	glPushMatrix();	
		glTranslatef(10, 150, 0);   //posiçao do texto na tela
		glScalef(0.09, 0.09, 0.09); // diminui o tamanho do fonte
		glLineWidth(2); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10,"   JOGO DA MEMORIA E  ");
	glPopMatrix();
	
	glPushMatrix();	
		glTranslatef(10, 130, 0);   //posiçao do texto na tela
		glScalef(0.09, 0.09, 0.09); // diminui o tamanho do fonte
		glLineWidth(2); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10,"  APRENDIZADO ECOLOGICO ");
	glPopMatrix();
	
	glPushMatrix();	
		glTranslatef(10, 30, 0);   //posiçao do texto na tela
		glScalef(0.05, 0.05, 0.05); // diminui o tamanho do fonte
		glLineWidth(1); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10,"Utilize as teclas 1, 2, 3, 4, 5, 6, 7, 8, 9 para jogar");
	glPopMatrix();

	glPushMatrix();	
		glTranslatef(40, 40, 0);  //posiçao do texto na tela
		glScalef(0.08, 0.08, 0.08); // diminui o tamanho do fonte
		drawTextStroke(GLUT_STROKE_ROMAN,"  Click para iniciar");
	glPopMatrix();

	glFlush();
}

void MenuOpcoes(int op){
	int i;
	switch(op){
		case 0: glutDisplayFunc(DesenhaMenu);
				for(i=0;i<10;i++){
					AnimaReseta(i);
					numShow[i] = true;
					cardVirado[i] = false;
				}
				sortearOrdem();
			break;
	}
	glutPostRedisplay();
}

void MenuSecundario (){
	glutCreateMenu(MenuOpcoes);
	glutAddMenuEntry("Voltar ao menu principal",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawTextStroke(void *font, char *string) {  
	// Exibe caractere a caractere
	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++); 
}

void GerenciaMouse(int button, int state, int x, int y){
	if (current_view == VIEW_MENU) {
		if (button == GLUT_LEFT_BUTTON) {
			glutDisplayFunc(DesenhaJogo);  
		}
	}
	if (current_view == VIEW_GAME || current_view == VIEW_GAME_END) {
		if(button == GLUT_RIGHT_BUTTON){
			MenuSecundario();
		}
	}
	 glutPostRedisplay();	
	}

void DesenhaTorneira()
{
	//Pra desenhar o apoio da torneira na parede
	int i;
	float t;
	GLfloat x[4], y[4];
	GLfloat xt[200], yt[200];
	x[0] = 20; x[1] = 11; x[2]=11; x[3]=20;
	y[0] = -8; y[1] = -8; y[2]=2; y[3]=2;
	
	for(i=0, t=0;t<1;i++,t+=0.005){
		xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
		yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*pow(t,2)*(1-t)*y[2] + pow(t,3)*y[3];
	}
	
	glBegin(GL_POINTS);
		for(i=0;i<200;i++){
			glVertex2f(xt[i],yt[i]);
		}
	glEnd();
	
	//Desenhar primeira curva da saída da torneira
	x[0] = -10; x[1] = -10; x[2]=-15; x[3]=-15;
	y[0] = 0; y[1] = 0; y[2]=0; y[3]=-8;
	
	for(i=0, t=0;t<1;i++,t+=0.005){
		xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
		yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*pow(t,2)*(1-t)*y[2] + pow(t,3)*y[3];
	}
	
	glBegin(GL_POINTS);
		for(i=0;i<200;i++){
			glVertex2f(xt[i],yt[i]);
		}
	glEnd();
	
	//Desenhar segunda curva da saída da torneira
	x[0] = -10; x[1] = -10; x[2]=-11; x[3]=-11;
	y[0] = -5; y[1] = -5; y[2]=-5; y[3]=-8;
	
	for(i=0, t=0;t<1;i++,t+=0.005){
		xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
		yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*pow(t,2)*(1-t)*y[2] + pow(t,3)*y[3];
	}
	
	glBegin(GL_POINTS);
		for(i=0;i<200;i++){
			glVertex2f(xt[i],yt[i]);
		}
	glEnd();
	
	//final da "torneira"
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-15,-8);
		glVertex2f(-11,-8);
	glEnd();
	
	
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-10,-5);
		glVertex2f(15,-5);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		glVertex2f(-10,0);
		glVertex2f(15,0);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		glVertex2f(0,0);
		glVertex2f(0,5);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		glVertex2f(3,0);
		glVertex2f(3,5);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		glVertex2f(-4,5);
		glVertex2f(7,5);
		glVertex2f(7,8);
		glVertex2f(-4,8);
	glEnd();
	

	
	glBegin(GL_LINE_LOOP);
		glVertex2f(20,-8);
		glVertex2f(20,2);
	glEnd();
}

void DesenhaSacoDeLixo(){
	int i;
	float t;
	GLfloat x[4], y[4];
	GLfloat xt[1000], yt[1000];
	//Saco de lixo maior
	x[0] = 3; x[1] = 28; x[2]=-22; x[3]=3; 
	y[0] = 2; y[1] = -12; y[2]=-12; y[3]=3; 
	
	for(i=0, t=0;t<1;i++,t+=0.001){
		xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
		yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*pow(t,2)*(1-t)*y[2] + pow(t,3)*y[3];
	}
	
	glBegin(GL_POINTS);
		for(i=0;i<1000;i++){
			glVertex2f(xt[i],yt[i]);
		}
	glEnd();
	
	//Parte da direita do saco de lixo
	x[0] = 3; x[1] = 11; x[2]=7; x[3]=3;
	y[0] = 3; y[1] = 3; y[2]=8; y[3]=3;
	
	for(i=0, t=0;t<1;i++,t+=0.001){
		xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
		yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*pow(t,2)*(1-t)*y[2] + pow(t,3)*y[3];
	}
	
	glBegin(GL_POINTS);
		for(i=0;i<1000;i++){
			glVertex2f(xt[i],yt[i]);
		}
	glEnd();
	
	//Parte da esquerda do saco de lixo
	x[0] = 3; x[1] = -5; x[2]=-1; x[3]=3;
	y[0] = 3; y[1] = 3; y[2]=8; y[3]=3;
	
	for(i=0, t=0;t<1;i++,t+=0.001){
		xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
		yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*pow(t,2)*(1-t)*y[2] + pow(t,3)*y[3];
	}
	
	glBegin(GL_POINTS);
		for(i=0;i<1000;i++){
			glVertex2f(xt[i],yt[i]);
		}
	glEnd();
}

void DesenhaRaio(){
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(8,8);
		glVertex2f(0,-2);
		glVertex2f(5,-2);
		glVertex2f(0,-12);
		glVertex2f(10,0);
		glVertex2f(5,0);
		glVertex2f(8,8);
	glEnd();
}

void DesenhaPinheiro(){
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	//primeira metade
		glVertex2f(3,10);
		glVertex2f(0,5);
		glVertex2f(2,5);
		glVertex2f(-3,0);
		glVertex2f(2,0);
		glVertex2f(-6,-5);
		glVertex2f(2,-5);
		glVertex2f(2,-10);
		//intersec e segunda metade
		glVertex2f(4,-10);
		glVertex2f(4,-5);
		glVertex2f(12,-5);
		glVertex2f(4,0);
		glVertex2f(9,0);
		glVertex2f(4,5);
		glVertex2f(6,5);
	glEnd();
}

void DesenhaEcoBag(){
	int i;
	float t;
	GLfloat x[4], y[4];
	GLfloat xt[1000], yt[1000];
	//base da sacola
	glBegin(GL_LINE_LOOP);
		glVertex2f(-5.5,1.5);
		glVertex2f(9.5,1.5);
		glVertex2f(9.5,-13.5);
		glVertex2f(-5.5,-13.5);
	glEnd();
	
	//Desenho da alça da sacola
	x[0] = -3; x[1] = -3; x[2]=7; x[3]=7;
	y[0] = 1.5; y[1] = 12; y[2]=12; y[3]=1.5;
	
	for(i=0, t=0;t<1;i++,t+=0.001){
		xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
		yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*pow(t,2)*(1-t)*y[2] + pow(t,3)*y[3];
	}
	
	glBegin(GL_POINTS);
		for(i=0;i<1000;i++){
			glVertex2f(xt[i],yt[i]);
		}
	glEnd();
	
	//Desenho da parte superior da folha
	x[0] = -2; x[1] = -2; x[2]=1; x[3]=6;
	y[0] = -10; y[1] = -5; y[2]=-2; y[3]=-2;
	
	for(i=0, t=0;t<1;i++,t+=0.001){
		xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
		yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*pow(t,2)*(1-t)*y[2] + pow(t,3)*y[3];
	}
	
	glBegin(GL_POINTS);
		for(i=0;i<1000;i++){
			glVertex2f(xt[i],yt[i]);
		}
	glEnd();
	
	//Desenho da parte inferior da folha
	x[0] = -2; x[1] = 3; x[2]=6; x[3]=6;
	y[0] = -10; y[1] = -10; y[2]=-7; y[3]=-2;
	
	for(i=0, t=0;t<1;i++,t+=0.001){
		xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
		yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*pow(t,2)*(1-t)*y[2] + pow(t,3)*y[3];
	}
	
	glBegin(GL_POINTS);
		for(i=0;i<1000;i++){
			glVertex2f(xt[i],yt[i]);
		}
	glEnd();
	
	//Desenho da linha da folha
	x[0] = -2; x[1] = 0; x[2]=4; x[3]=6;
	y[0] = -10; y[1] = -5; y[2]=-7; y[3]=-2;
	
	for(i=0, t=0;t<1;i++,t+=0.001){
		xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
		yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*pow(t,2)*(1-t)*y[2] + pow(t,3)*y[3];
	}
	
	glBegin(GL_POINTS);
		for(i=0;i<1000;i++){
			glVertex2f(xt[i],yt[i]);
		}
	glEnd();
}

void desenhaObjetos(int x){
	switch(x){
		case 1:
			DesenhaTorneira();
			break;
		case 2:
			DesenhaSacoDeLixo();
			break;
		case 3:
			DesenhaRaio();
			break;
		case 4:
			DesenhaPinheiro();
			break;
		case 5:
			DesenhaEcoBag();
			break;
		default:
			printf("\nCaiu no default");
			break;
	}
	

}

void textosObjetos(int x){
	switch(x){
		case 1:
			glPushMatrix();	
				glTranslatef(180, 190, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"1) Uma torneira pingando uma gota de agua a cada 5 segundos");
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(180, 184, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"representa mais de 20 litros de agua desperdiçados em apenas um dia.");
			glPopMatrix();
			
			
			glPushMatrix();
				glTranslatef(180, 178, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"Feche bem a torneira apos seu uso.");
			glPopMatrix();
			
			break;
		case 2:
			glPushMatrix();	
				glTranslatef(180, 170, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"2) No Brasil, sao anualmente produzidos 82M de toneladas de lixo por ano.");
			glPopMatrix();
			
			glPushMatrix();	
				glTranslatef(180, 164, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"Reciclar e reutilizar o que puder e descartar somente os residuos nao");
			glPopMatrix();

			glPushMatrix();	
				glTranslatef(180, 158, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"reciclaveis eh uma otima forma de contribuir com o meio ambiente.");
			glPopMatrix();

			break;
		case 3:
			glPushMatrix();	
				glTranslatef(180, 150, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"3) Os dados do PROCEL apontam que, apenas no ambito residencial, o consumo ");
			glPopMatrix();

			glPushMatrix();	
				glTranslatef(180, 144, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"descenessário pode chegar a ate 40%.Procure ser consciente ");
			glPopMatrix();

			glPushMatrix();	
				glTranslatef(180, 138, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"com o consumo de eletricidade. Apague a luz ao sair do comodo.");
			glPopMatrix();
			
			break;
		case 4:
			glPushMatrix();	
				glTranslatef(180, 130, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"4) Foi calculado que somente as 14334 árvores do Parque Ibirapuera haviam armazenado 8740");
			glPopMatrix();

			glPushMatrix();	
				glTranslatef(180, 124, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"toneladas de carbono da atmosfera em 2011. Plantar uma árvore melhora significativamente");
			glPopMatrix();

			glPushMatrix();	
				glTranslatef(180, 118, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"a qualidade do ar do entorno do local em que ela foi plantada.");
			glPopMatrix();
			
			break;

		case 5:
			glPushMatrix();	
				glTranslatef(180, 110, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"5) O plastico demora cerca de 450 anos para ser totalmente decomposto, o que");
			glPopMatrix();

			glPushMatrix();	
				glTranslatef(180, 104, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"pode ser altamente prejudicial ao Ambiente. Uma das melhores formas de reduzir");
			glPopMatrix();

			glPushMatrix();	
				glTranslatef(180, 98, 0);
				glScalef(0.03, 0.03, 0.03);
				glLineWidth(1);
				drawTextStroke(GLUT_BITMAP_HELVETICA_10,"o uso de plastico eh substituindo as sacolas convencionais por sacolas de pano ou papel.");
			glPopMatrix();
			
			break;
		default:
			printf("\nCaiu no default");
			break;
	}
}

int main()
{ 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);     
	glutInitWindowSize(500,500);  
	glutInitWindowPosition(600,200);  
	glutCreateWindow("Jogo da memoria e aprendizado ecologico"); 
	
 	glutDisplayFunc(DesenhaMenu);   
	glutKeyboardFunc(Teclado);
	
	glutMouseFunc(GerenciaMouse);
	glutSpecialFunc(TeclasEspeciais);
	
	Inicializa(); 
	glutMainLoop();
	
	return 0;

}
