//Alunos: Paulo Cesar Pereira Gomes; Eduardo de Oliveira 

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>


int vidas = 3;
float translatex = 47;
float translatey = 2;
int auxiliar;
int current_view = 0;
const int VIEW_MENU = 0;
const int VIEW_GAME = 1;
const int VIEW_GAME_END = 2;
GLfloat win=0.0;
GLfloat panX, panY;

// Vari?veis de tamanho e propor??o da janela, para interesse na detec??o do mouse
int width, height; 
float widX, heiY; 
//Controlador de qual tela o jogo vai mostrar
int controllerMenu = 0; 
// Vari?vel pros textos do jogo
char* genericText;
//Vetores com as cores e indica??o se as cartas est?o viradas
int ordem[10];
float xStep = 10;
float BcolorR[] = {1.0, 0.0, 0.0, 1.0, 0.556900};
float BcolorG[] = {0.0, 1.0, 0.0, 1.0, 0.419600};
float BcolorB[] = {0.0, 0.0, 1.0, 0.0, 0.137300};
float ang[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float colorR[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float colorG[] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
float colorB[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
bool numShow[] = {true, true, true, true, true, true, true, true, true, true};

//Declara??es das fun??es
void Inicializa(void);
void DesenhaTexto(void *font, char vidas);
void DesenhaTextoStroke(void *font, char *string);
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
void drawCircle(int, int, int, int, int);
void drawTextStroke(void*, char*);
void EspecificaParametrosVisualizacao(void);


void Inicializa(void){
	sortearOrdem();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  // o uso deste comando garante que o zoom 
	                   // seja feito de forma absoluta e não relativa
	//gluOrtho2D (-win, win +200.0, -win+ 0.0, win+200.0);
	gluOrtho2D(0.0,200.0,0.0,200.0);

	
	
}



void DesenhaTexto(void *font, char vidas) 
{
	// Exibe caractere a caractere
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, vidas); 
}

void DesenhaTextoStroke(void *font, char *string) 
{  
	// Exibe caractere a caractere
	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++); 
}

/*void DesenhaObstaculo(){
	
	glBegin(GL_QUADS);
	//Primeira linha
		//7
		glColor3f(colorR[7], colorG[7], colorB[7]);
		glVertex2f(35.0f, 190.0f);	glVertex2f(75.0f, 190.0f);
		glVertex2f(75.0f, 150.0f); 	glVertex2f(35.0f, 150.0f);
		
		
		//8
		glColor3f(colorR[8], colorG[8], colorB[8]);
		glVertex2f(80.0f, 190.0f);	glVertex2f(120.0f, 190.0f);
		glVertex2f(120.0f, 150.0f);	glVertex2f(80.0f, 150.0f);
		
		
		//9
		glColor3f(colorR[9], colorG[9], colorB[9]);
		glVertex2f(125.0f, 190.0f);	glVertex2f(165.0f, 190.0f);
		glVertex2f(165.0f, 150.0f);	glVertex2f(125.0f, 150.0f);
		
	//Segunda linha
		//4
		glColor3f(colorR[4], colorG[4], colorB[4]);
		glVertex2f(35.0f, 145.0f);	glVertex2f(75.0f, 145.0f);
		glVertex2f(75.0f, 105.0f); 	glVertex2f(35.0f, 105.0f);
		
		
		//5
		glColor3f(colorR[5], colorG[5], colorB[5]);
		glVertex2f(80.0f, 145.0f);	glVertex2f(120.0f, 145.0f);
		glVertex2f(120.0f, 105.0f); glVertex2f(80.0f, 105.0f);
		
		//6
		glColor3f(colorR[6], colorG[6], colorB[6]);
		glVertex2f(125.0f, 145.0f);	glVertex2f(165.0f, 145.0f);
		glVertex2f(165.0f, 105.0f); glVertex2f(125.0f, 105.0f);
		
	//Terceira linha
		//1
		glColor3f(colorR[1], colorG[1], colorB[1]);
		glVertex2f(35.0f, 100.0f);	glVertex2f(75.0f, 100.0f);
		glVertex2f(75.0f, 60.0f); 	glVertex2f(35.0f, 60.0f);
		
		
		//2
		glColor3f(colorR[2], colorG[2], colorB[2]);
		glVertex2f(80.0f, 100.0f);	glVertex2f(120.0f, 100.0f);
		glVertex2f(120.0f, 60.0f); 	glVertex2f(80.0f, 60.0f);
		
		
		//3
		glColor3f(colorR[3], colorG[3], colorB[3]);
		glVertex2f(125.0f, 100.0f);	glVertex2f(165.0f, 100.0f);
		glVertex2f(165.0f, 60.0f); 	glVertex2f(125.0f, 60.0f);
		
	//Quarta linha	
		//0
		glColor3f(colorR[0], colorG[0], colorB[0]);
		glVertex2f(80.0f, 55.0f);	glVertex2f(120.0f, 55.0f);
		glVertex2f(120.0f, 15.0f); 	glVertex2f(80.0f, 15.0f);
	glEnd();	
	
}*/
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
		Processamento();
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
	//pra ajudar na mudan?a da cor do plano de fundo
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	//sortearOrdem();
	glPushMatrix();
	//DesenhaObstaculo();
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
	
	glPopMatrix();
	
	glTranslatef(translatex, translatey, 0.0f);
	glPopMatrix();
	
	
	glFlush();
}

void TeclasEspeciais(int key, int x, int y)
{
	if(current_view==VIEW_GAME)
   {
   
   	 if(key == GLUT_KEY_UP ) {
   	 	if(win > -40)
   	 	{
   	 	   win -= 20;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D (-win, win+200, -win, win+200);
		}
           
           
    	}
     if(key== GLUT_KEY_DOWN   ) {
     	  if (win < 40)
     	  {
     	  	win += 20;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D (-win, win+200, -win, win+200);
		   }
           
    	}
   		
	}
	glutPostRedisplay();
}
void Processamento()
{
	auxiliar = 0;
	int i;
	int aux1[3];
	for(i=0;i<10;i++)
	{
		if(!numShow[i] && (auxiliar < 3))
		{
			aux1[auxiliar] = i;
			//printf("aux:%d\n", aux1[auxiliar]);
			auxiliar++;
		} 
	}
	if(auxiliar==3)
	{
		for(i=0;i<3;i++)
		{
			glutTimerFunc(50,AnimaReseta, aux1[i]);
			//ang[aux1[i]] = 0;
			numShow[aux1[i]]=true;
			//colorR[aux1[i]]=0.0;
			//colorG[aux1[i]]=0.2;
			//colorB[aux1[i]]=0.0;	
		}
		auxiliar = 0;
	}
	
}
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
		switch(key){
		case 96:
		case 48:
			numShow[0] = false;
			glutTimerFunc(150, Anima, 0);
        	break;
        case 97:
        case 49:
        	numShow[1] = false;
        	glutTimerFunc(150, Anima, 1);
  
        	break;
        case 98:
        case 50:
        	numShow[2] = false;
        	glutTimerFunc(150, Anima, 2);
        	break;
        case 99:
        case 51:
        	numShow[3] = false;
        	glutTimerFunc(150, Anima, 3);
        	break;	
        case 100:
        case 52:
        	numShow[4] = false;
        	glutTimerFunc(150, Anima, 4);
        	break;
        case 101:
        case 53:
        	numShow[5] = false;
        	glutTimerFunc(150, Anima, 5);
        	break;
        case 102:
        case 54:
        	numShow[6] = false;
        	glutTimerFunc(150, Anima, 6);
        	break;
        case 103:
        case 55:
        	numShow[7] = false;
        	glutTimerFunc(150, Anima, 7);
        	break;
        case 104:
        case 56:
        	numShow[8] = false;
        	glutTimerFunc(150, Anima, 8);
        	break;
        case 105:
        case 57:
        	numShow[9] = false;
        	glutTimerFunc(150, Anima, 9);
        	break;
        default:
        	break;
    }
	glutPostRedisplay();
}



void Desenha(){
	// Pegando os valores do tamanho da janela (?til caso mude de tamanho)
	width = glutGet(GLUT_WINDOW_WIDTH); height = glutGet(GLUT_WINDOW_HEIGHT);
	widX = width/100.0f; heiY = (height/100.0f);
	// Controlador de qual parte do jogo mostrar
	switch(controllerMenu){
		case 0: 
			DesenhaMenu();
			break;
		case 1:
			DesenhaJogo();
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
	
	
	//glColor3f(0.137300, 0.419600, 0.556900);
	

	glClearColor(0.309800, 0.184300, 0.309800, 0.000000);
	glPushMatrix();	
		glTranslatef(10, 150, 0);   //posiçao do texto na tela
		glScalef(0.09, 0.09, 0.09); // diminui o tamanho do fonte
		//glRotatef(180, 1,0,0); // rotaciona o texto
		glLineWidth(2); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10,"   JOGO DA MEMORIA E  ");
	glPopMatrix();
	
	glPushMatrix();	
		glTranslatef(10, 130, 0);   //posiçao do texto na tela
		glScalef(0.09, 0.09, 0.09); // diminui o tamanho do fonte
		//glRotatef(180, 1,0,0); // rotaciona o texto
		glLineWidth(2); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10,"  APRENDIZADO ECOLOGICO ");
	glPopMatrix();
	
	glPushMatrix();	
		glTranslatef(10, 30, 0);   //posiçao do texto na tela
		glScalef(0.05, 0.05, 0.05); // diminui o tamanho do fonte
		//glRotatef(180, 1,0,0); // rotaciona o texto
		glLineWidth(1); // define a espessura da linha
		drawTextStroke(GLUT_BITMAP_HELVETICA_10,"Utilize as telas 1, 2, 3, 4, 5, 6, 7, 8, 9 para jogar");
	glPopMatrix();
	 

	
	//glColor3f(0.137300, 0.419600, 0.556900);
	glPushMatrix();	
		glTranslatef(40, 40, 0);  //posiçao do texto na tela
		glScalef(0.08, 0.08, 0.08); // diminui o tamanho do fonte
		//glRotatef(180, 1,0,0); // rotaciona o texto
		//glLineWidth(2); // define a espessura da linha
		drawTextStroke(GLUT_STROKE_ROMAN,"  Click para iniciar");
	glPopMatrix();

	glFlush();
	
	
	
}

void MenuOpcoes(int op){
	switch(op){
		case 0: glutDisplayFunc(DesenhaMenu);
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

/*
void GerenciaMouse(int button, int state, int x, int y)
{        
    if (button == GLUT_LEFT_BUTTON)
         if (state == GLUT_DOWN){
         	//printf("%d %d %d\n", width,x,y);
         	
         	//Colis?o Quadrado superior direito
         	if(x>70*widX && x<90*widX && y<height-66*heiY && y>height-86*heiY){ // muda cor quadrado superior direito
         		alteraCorObjeto(3);
		  	} else if(x>5*widX && x<45*widX && y<height-20*heiY && y>height-28*heiY) { // muda cor retangulo inferior
		  		alteraCorObjeto(0);
			} else if(x>8*widX && x<25*widX && y<height-70*heiY && y>height-90*heiY) { //muda cor quadrado superior esquerdo
		  		alteraCorObjeto(1);
			} else if(x>40*widX && x<80*widX && y<height-42*heiY && y>height-50*heiY) { //muda cor retangulo meio
		  		alteraCorObjeto(2);
			} else if(x>(translatex)*widX && x<(translatex + wJogador)*widX && 
				y<height-(translatey)*heiY && y>height-(translatey + wJogador)*heiY){
					alteraCorObjeto(4);
					alteraCorObjeto(5);
					alteraCorObjeto(6);
					alteraCorJogador();
				} else 
				alteraCorBackground();
					
		 }
         
    glutPostRedisplay();
}
*/
void GerenciaMouse(int button, int state, int x, int y){
	if (current_view == VIEW_MENU) {
		if (button == GLUT_LEFT_BUTTON) {
			glutDisplayFunc(DesenhaJogo);  
			
		}
}
	if (current_view == VIEW_GAME) {
		if(button == GLUT_RIGHT_BUTTON){
			MenuSecundario();
		}
	
}
	 glutPostRedisplay();	
	}

   	
   
 
	
   




int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);     
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
	glutInitWindowSize(500,500);  
	glutInitWindowPosition(600,200);  
	glutCreateWindow("Jogo da memoria e aprendizado ecologico"); 
	
	glutDisplayFunc(DesenhaMenu);  
	glutKeyboardFunc(Teclado);
	
	glutMouseFunc(GerenciaMouse);
	glutSpecialFunc(TeclasEspeciais);
	
	//Declara??o inicial dos tamanhos da janela, ?til para fun??o do mouse
	//width = glutGet(GLUT_WINDOW_WIDTH); height = glutGet(GLUT_WINDOW_HEIGHT);
	//widX = width/100.0f; heiY = (height/100.0f);
	
	Inicializa(); 
	glutMainLoop();
	
	return 0;

}
