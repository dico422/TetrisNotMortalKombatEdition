#include "Menu.h"

using namespace std;

#define GridSize 30

Menu menu;

#define LarguraInicial 10
#define AlturaInicial 20

const int possiveisRotacoes[] = {0,90,180,270};
Tetris jogo(LarguraInicial);
Tetris jogoComPecaCaindo(LarguraInicial);

int alturaPecaAtual=AlturaInicial;
char idPecaAtual;
int posicaoPecaAtual,rotacaoPecaAtual;

int ultimaTecla = -1;

int rotation = 0;


void QuadDraw(float x, float y, char piece_type)
{
    
    float r,g,b;
    r = g = b = 0.0;
    
    
    if(menu.Cor()==1){
        switch((int)piece_type){
            
            case (int)'J':
                r = 1;
                break;
            case (int)'L':
                g = 1;
                break;
            case (int)'Z':
                b = 1;
                break;
            case (int)'S':
                r = 1;
                b = 1;
                break;
            case (int)'I':
                r = 1;
                g = 1;
                break;
            case (int)'O':
                b = 1;
                g = 1;
                break;
            case (int)'T':
                r = 1;
                b = 1;
                g = 0.5;
                break;
            default:
                return;
        }
    }
    else if(menu.Cor()==2){
        switch((int)piece_type){
            
            case (int)'J':
            case (int)'L':
            case (int)'Z':
            case (int)'S':
            case (int)'I':
            case (int)'O':
            case (int)'T':
                g = 0.2;
                break;
            default:
                return;
        }
    }else {
        switch((int)piece_type){
            
            case (int)'J':
            case (int)'L':
            case (int)'Z':
            case (int)'S':
            case (int)'I':
            case (int)'O':
            case (int)'T':
                r = 1;
                b = 1;
                g = 1;
                break;
            default:
                return;
        }
    }
    
    glColor3f(r,g,b);
    glRectf(x+1,y+1,x+GridSize-1,y+GridSize-1);
    
}

void exibeJogo(const Tetris &jogoComPecaCaindo,int largura,int altura) {
    
    glClear (GL_COLOR_BUFFER_BIT);
    
    // Modo Bebado
    if(menu.Modo() == 2){
        rotation+=10;
        if(rotation>=360) rotation = 0;
        glRotatef(rotation,0,0,1);
    } else rotation = 0;
    
    // Desenha um fundo preto
    glColor3f(0,0,0);
    glRectf(1,1,largura*GridSize, altura*GridSize);
    
    // Desenha cada peça do jogo
	for(int i=0;i<largura;i++) {
		for(int j=0;j<altura;j++) {
			QuadDraw(i * GridSize, j * GridSize, jogoComPecaCaindo.get(i,j));
		}
	}
	
	glFlush ();
}

void RestartGame();

bool GameLoop()
{
    
//     if(menu.RestartGame())
//         RestartGame();
    
    usleep(menu.velocidade());
    
    jogoComPecaCaindo = jogo;
		
	if(ultimaTecla == GLUT_KEY_LEFT) { 			
		Tetris jogoTeste = jogoComPecaCaindo; 			
		if(jogoTeste.adicionaForma(posicaoPecaAtual-1,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
			posicaoPecaAtual--;
	} else if(ultimaTecla == GLUT_KEY_RIGHT){
		Tetris jogoTeste = jogoComPecaCaindo; 			
		if(jogoTeste.adicionaForma(posicaoPecaAtual+1,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
			posicaoPecaAtual++;
	} else if(ultimaTecla==' '){ //a tecla de espaco e' utilizada para rodar a peca...
		Tetris jogoTeste = jogoComPecaCaindo; 			
		if(jogoTeste.adicionaForma(posicaoPecaAtual,alturaPecaAtual,idPecaAtual, possiveisRotacoes[(rotacaoPecaAtual+1)%4]))
			rotacaoPecaAtual = (rotacaoPecaAtual+1)%4;
	} 

 		//Antes de diminuirmos a altura de uma peca, tentamos adiciona-la nessa nova altura
 		// Se a funcao retornar true --> significa que podemos diminuir
 		// Senao --> isso significa que apeca colidiria (ocuparia o mesmo espaco que) com alguma peca fixa --> a peca devera parar na altura anterior 
 		// e uma nova peca deve comecar a cair
    if(jogoComPecaCaindo.adicionaForma(posicaoPecaAtual,alturaPecaAtual-1,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual])) {
		alturaPecaAtual--;
	}
	else {
		//adiciona a peca a posicao onde ela ficara fixada
		jogo.adicionaForma(posicaoPecaAtual,alturaPecaAtual,idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]);
		jogoComPecaCaindo = jogo;
        
		//sorteia uma nova peca, define a altura como sendo o topo da tela, etc...
		idPecaAtual = "IJLOSTZ"[rand()%7];
		posicaoPecaAtual = menu.larguraJogo()/2-2;
		alturaPecaAtual = menu.alturaMaximaJogo();
		rotacaoPecaAtual = rand()%4;
		jogoComPecaCaindo.removeLinhasCompletas();	
		jogo = jogoComPecaCaindo;	
	}
	
	ultimaTecla = -1;

    exibeJogo(jogoComPecaCaindo,menu.larguraJogo(),menu.alturaMaximaJogo());
    
    return true;
}

void AppIdle()
{
    
    if(menu.is_open()){
        
        menu.Loop();
        return;
    }
    GameLoop();
    
}

void AppDisplay()
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT);
    
}

void AppReshape(int w, int h)
{
  
    if(menu.is_open()){
        
        menu.Reshape(w,h);
        return;
    }
    
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, (GLdouble) menu.larguraJogo()*GridSize, 0.0, (GLdouble) menu.alturaMaximaJogo()*GridSize);
    
}

void AppKeyboard(unsigned char key, int x, int y)
{
    
    if(menu.is_open()){
        
        menu.Key(key,x,y);
        return;
    }
    
    ultimaTecla = key;
    
    switch(key)
	{
		case 27: menu.set_state(true); break;
	}
	glutPostRedisplay();
    
}

void AppKeyboardSpecial(int key, int x, int y)
{
    
    if(menu.is_open()){
        
        menu.KeySpecial(key,x,y);
        return;
    }
    
    ultimaTecla = key;
    
}

void AppMouse(int key, int x, int y, int state)
{
    
    if(menu.is_open())
        menu.Mouse(key,x,y,state);
    
}

void initGame()
{
    
    menu.set_state(true);
    menu.set_velocidade(250000);
    menu.SetCor(1);
    menu.SetTamanho(1);
    menu.set_larguraJogo(LarguraInicial);
    menu.set_alturaMaximaJogo(AlturaInicial);
    
    idPecaAtual = "IJLOSTZ"[rand()%7];
	posicaoPecaAtual = menu.larguraJogo()/2-2;
	alturaPecaAtual = menu.alturaMaximaJogo();
	rotacaoPecaAtual = 0;
    
}

void RestartGame(){
    
    std::cout << "oi\n";
    Tetris NewJogo(menu.larguraJogo());
    jogo = NewJogo;
    jogoComPecaCaindo = jogo;
    
    initGame();
    
}

int main(int argc, char** argv)
{
    
    initGame();
    
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize (1000, 1000);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Tetris: \"Nao eh mortal kombat\" Edition");
	//glutFullScreen();
		
	glutMouseFunc(AppMouse);
	glutDisplayFunc(AppDisplay);
	glutReshapeFunc(AppReshape);
	glutKeyboardFunc(AppKeyboard);
    glutSpecialUpFunc(AppKeyboardSpecial);
	glutIdleFunc(AppIdle);
	
	glutMainLoop();
	
}
