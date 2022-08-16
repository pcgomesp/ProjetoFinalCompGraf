//Alunos: Paulo Cesar Pereira Gomes; Eduardo de Oliveira 

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float translatex = 47;
float translatey = 2; 
float ang1 = 0, ang2 = 0;
int wJogador = 6;
int velocidade = 2;
int vidas = 3;
int auxCorObj = 1; //Auxiliar pra fun��o de cor dos objetos
int auxCorBcg = 1; //Auxiliar pra fun��o de cor do background
char aux[5];

int width, height; // Variaveis pra pegar os tamanhos da janela atual
float widX, heiY; //Pegar propor��o dos tamanhos da janela atual com os valores definidos no plano

//Variaveis das cores
//De colorX[0] at� colorX[6] s�o as cores dos obst�culos.
//ColorX[7] � a cor do background, e colorX[8] a cor do objeto jogador
float BcolorR[] = {1.0, 0.0, 0.0, 1.0, 0.556900};
float BcolorG[] = {0.0, 1.0, 0.0, 1.0, 0.419600};
float BcolorB[] = {0.0, 0.0, 1.0, 0.0, 0.137300};

float colorR[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float colorG[] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
float colorB[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
bool numShow[] = {true, true, true, true, true, true, true, true, true, true};

void Inicializa(void){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glColor3f(colorR[7], colorG[7], colorB[7]);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,200.0);
	printf("Criado por: Eduardo de Oliveira e Paulo Cesar\n");
	printf("Setas do teclado para se movimentar\n");
	printf("clicar nos quadrilateros alteram suas cores\nclicar no jogador altera a cor dos demais obstaculos\nclicar no cenario altera a cor de fundo\n");
	printf("Chegue ate o final (linha vermelha) para ganhar!\n");
}

void colisaoVidas(){
	vidas--;
	if(vidas==0){
		printf("PERDEU! TENTE NOVAMENTE!");
		exit(0);
	}
	printf("VIDAS RESTANTES %d\n", vidas);
}

void DesenhaTexto(void *font, char vidas) 
{
	// Exibe caractere a caractere
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, vidas); 
}

void DesenhaObstaculo(){
	
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
		glVertex2f(120.0f, 105.0f); 	glVertex2f(80.0f, 105.0f);
		
		//6
		glColor3f(colorR[6], colorG[6], colorB[6]);
		glVertex2f(125.0f, 145.0f);	glVertex2f(165.0f, 145.0f);
		glVertex2f(165.0f, 105.0f); 	glVertex2f(125.0f, 105.0f);
		
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
	
}



void Desenha(){
	//Caso os tamanhos da janela mudem, eu posso facilmente adaptar os valores aqui
	sprintf(aux, "%d", vidas);
	width = glutGet(GLUT_WINDOW_WIDTH); height = glutGet(GLUT_WINDOW_HEIGHT);
	widX = width/100.0f; heiY = (height/100.0f);
	
	//pra ajudar na mudan�a da cor do plano de fundo
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	//desenha texto das vidas
	
	glPushMatrix();
	DesenhaObstaculo();
	
	glPushMatrix();
	
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
	// Move o corpo
	if(key == GLUT_KEY_LEFT)	{
		translatex-=velocidade;
		if ( translatex < 0 )
			translatex = 0; 
	}
	if(key == GLUT_KEY_RIGHT){
		translatex+=velocidade;
		if ( translatex > 94 )
			translatex = 94; 
	} 
	
	// Rotaciona antebra�o
	if(key == GLUT_KEY_DOWN){
		translatey-=velocidade;
		if ( translatey < 0 )
			translatey = 0;
	}
	if(key == GLUT_KEY_UP)
		translatey+=velocidade;    
		if ( translatey > 94 )
			translatey = 94; 
			
	//ganhar o jogo
	if((translatey + wJogador)>99){
		printf("GANHOU!");
		exit(0);
	}
	
	glutPostRedisplay();
}

void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	switch(key){
		case 96:
		case 48:
			numShow[0] = false;
			colorR[0] = BcolorR[0];
        	colorG[0] = BcolorG[0];
        	colorB[0] = BcolorB[0];
        	break;
        case 97:
        case 49:
        	numShow[1] = false;
        	colorR[1] = BcolorR[1];
        	colorG[1] = BcolorG[1];
        	colorB[1] = BcolorB[1];
        	break;
        case 98:
        case 50:
        	numShow[2] = false;
        	colorR[2] = BcolorR[1];
        	colorG[2] = BcolorG[1];
        	colorB[2] = BcolorB[1];
        	break;
        case 99:
        case 51:
        	numShow[3] = false;
        	colorR[3] = BcolorR[2];
        	colorG[3] = BcolorG[2];
        	colorB[3] = BcolorB[2];
        	break;	
        case 100:
        case 52:
        	numShow[4] = false;
        	colorR[4] = BcolorR[3];
        	colorG[4] = BcolorG[3];
        	colorB[4] = BcolorB[3];
        	break;
        case 101:
        case 53:
        	numShow[5] = false;
        	colorR[5] = BcolorR[4];
        	colorG[5] = BcolorG[4];
        	colorB[5] = BcolorB[4];
        	break;
        case 102:
        case 54:
        	numShow[6] = false;
        	colorR[6] = BcolorR[3];
        	colorG[6] = BcolorG[3];
        	colorB[6] = BcolorB[3];
        	break;
        case 103:
        case 55:
        	numShow[7] = false;
        	colorR[7] = BcolorR[0];
        	colorG[7] = BcolorG[0];
        	colorB[7] = BcolorB[0];
        	break;
        case 104:
        case 56:
        	numShow[8] = false;
        	colorR[8] = BcolorR[4];
        	colorG[8] = BcolorG[4];
        	colorB[8] = BcolorB[4];
        	break;
        case 105:
        case 57:
        	numShow[9] = false;
        	colorR[9] = BcolorR[2];
        	colorG[9] = BcolorG[2];
        	colorB[9] = BcolorB[2];
        	break;
        default:
        	break;
    }
	glutPostRedisplay();
}

void alteraCorJogador(){
	if(colorR[8] == 1.0f){
		colorR[8] = 0.0;
        colorG[8] = 1.0;
        colorB[8] = 0.0;
	} else if(colorG[8] == 1.0f){
		colorR[8] = 0.0;
        colorG[8] = 0.0;
        colorB[8] = 1.0;
	} else {
		colorR[8] = 1.0;
        colorG[8] = 0.0;
        colorB[8] = 0.0;
	}
}

void alteraCorBackground(){
	switch(auxCorBcg){
		case 1:
			colorR[7] = 0.847059;
         	colorG[7] = 0.847059;
         	colorB[7] = 0.74902;
			auxCorBcg++;
			break;
		case 2:
			colorR[7] = 0.81;
         	colorG[7] = 0.71;
         	colorB[7] = 0.23;
			auxCorBcg++;
			break;
		case 3: 
			colorR[7] = 0.2;
         	colorG[7] = 0.2;
         	colorB[7] = 0.2;
			auxCorBcg=1;
			break;
	}
}
/*
void GerenciaMouse(int button, int state, int x, int y)
{        
    if (button == GLUT_LEFT_BUTTON)
         if (state == GLUT_DOWN){
         	//printf("%d %d %d\n", width,x,y);
         	
         	//Colis�o Quadrado superior direito
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
int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);     
	glutInitWindowSize(400,400);  
	glutInitWindowPosition(600,200);  
	glutCreateWindow("Desenho de objeto modelado com transforma��es hier�rquicas"); 
	glutDisplayFunc(Desenha);  
	glutKeyboardFunc(Teclado);
//	glutMouseFunc(GerenciaMouse);
//	glutSpecialFunc(TeclasEspeciais);
	
	//Declara��o inicial dos tamanhos da janela, necess�rio para fun��es de mudan�a de cor
	width = glutGet(GLUT_WINDOW_WIDTH); height = glutGet(GLUT_WINDOW_HEIGHT);
	widX = width/100.0f; heiY = (height/100.0f);
	
	
	Inicializa(); 
	glutMainLoop();
	
	return 0;

}