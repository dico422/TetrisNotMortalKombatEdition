#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <GL/glut.h>

#include "Tetris.h"

Tetris Game(20);

void AppRender()
{
	Game.Render();
}

void AppReshape(int w, int h)
{
	Game.Reshape(w,h);
}

void AppKeyUp(unsigned char key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,false);
}

void AppKeyDown(unsigned char key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,true);
}

void AppMouse(int button, int state, int x, int y)
{
	Game.ReadMouse(button,state,x,y);
}

void AppIdle()
{
	if(!Game.Loop()) exit(0);
}

void init (void)
{
/*  select clearing (background) color       */
    glClearColor (1.0, 1.0, 1.0, 0.0);

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}

int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize (600, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Tetris: \"Nao eh mortal kombat\" Edition");
	glutFullScreen();
		
	init();
	
	glutMouseFunc(AppMouse);
	glutDisplayFunc(AppRender);
	glutReshapeFunc(AppReshape);
	glutKeyboardFunc(AppKeyDown);
	glutKeyboardUpFunc(AppKeyUp);
	glutIdleFunc(AppIdle);
	
	
	Game.Init();
	
	glutMainLoop();
	
}

/*
int main(int argc, char** argv) {

	const int possiveisRotacoes[] = {0,90,180,270};
	const int larguraJogo = 16;
	const int alturaMaximaJogo = 20;
	Tetris jogo(larguraJogo);
	Tetris jogoComPecaCaindo(larguraJogo);
	
	int alturaPecaAtual=alturaMaximaJogo;
	char idPecaAtual;
	int posicaoPecaAtual,rotacaoPecaAtual;
	
	int ultimaTecla = -1;

	idPecaAtual = "IJLOSTZ"[rand()%7];
	posicaoPecaAtual = larguraJogo/2-2;
	alturaPecaAtual = alturaMaximaJogo;
	rotacaoPecaAtual = 0;
	
	{
		
		initGame(argc,argv);
		
		drawScreen();
		
		updateScreen();
	}
	
	/*
	
	while(true) {		
		jogoComPecaCaindo = jogo;

		if(jogoComPecaCaindo.adicionaForma(posicaoPecaAtual,alturaPecaAtual-1,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual])) {
			alturaPecaAtual--;
		}
		else {
			//adiciona a peca a posicao onde ela ficara fixada
			jogo.adicionaForma(posicaoPecaAtual,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]);
			jogoComPecaCaindo = jogo;

			//sorteia uma nova peca, define a altura como sendo o topo da tela, etc...
			idPecaAtual = "IJLOSTZ"[rand()%7];
			posicaoPecaAtual = larguraJogo/2-2;
			alturaPecaAtual = alturaMaximaJogo;
			rotacaoPecaAtual = rand()%4;
			jogoComPecaCaindo.removeLinhasCompletas();	
			jogo = jogoComPecaCaindo;	
		}

		//exibeJogo(jogoComPecaCaindo,larguraJogo,alturaMaximaJogo);
		
 		//ultimaTecla = getch();
 		halfdelay(5);

 		
 		//refresh();
	}
	//endwin();
	
}
*/
