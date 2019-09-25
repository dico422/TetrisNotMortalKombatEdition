#include <iostream>
#include <cstdlib>
//#include <ncurses.h>
#include <unistd.h>

#include "init.cpp"
#include "Tetris.h"


void handle_key(unsigned char key, int mousex, int mousey)
{

	switch(key)
	{
		case 27: exit(0); break;
	}
	glutPostRedisplay();
}

void draw_block(int x, int y, int size)
{

	
	
}


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
		
		glutKeyboardFunc(handle_key);
		
		
		glutMainLoop();
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
	*/
}
