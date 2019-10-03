//#ingure -clude <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cstring>
//using namespace std;

bool down,up,left,right =false;
int CurrLine =0;
int CurrRow = 0;
bool enter = false;
bool status [6][3] = {{0,0,0},
                     {0,0,1},
                     {0,0,1},
                     {0,0,1},
                     {0,1,1},
                     {0,0,0}};
bool *Iniciar = &status[0][1]; bool *Sair = &status[5][1];
bool *Turbo = &status[1][0];bool *Rapido = &status[1][1];bool *Normal = &status[1][2];
bool *Tam50x25 = &status[2][0];bool *Tam30x15 = &status[3][1];bool *Tam20x10 = &status[2][2]; 
bool *Cor3 = &status[2][0];bool *Cor2 = &status[3][1];bool *Cor1 = &status[2][2]; 
bool *Bebado = &status[2][0];bool *BebiNormal = &status[3][1]; 
void handle_key(unsigned char key, int mousex, int mousey)
{
  switch(key)
  {
    case 13: 
      //if (status[0][1]==1) 
        //começar jogo
      //if(status[5][1]==1) 
        //sair
			if(status[CurrLine][CurrRow+1]==0) { 
        for(int i=0;i<3;i++)
          status[CurrLine][i]= 0;
        if (CurrLine!=0&&CurrLine!=5)
          status[CurrLine][CurrRow+1]= 1; }
      if (CurrLine == 4 && CurrRow==1) status[4][1]= status[4][2];
      if (CurrLine == 4 && CurrRow==0) status[4][2]= status[4][1];
      break;
  }
  //Redesenha após atualizar valor da escala
  glutPostRedisplay();
}

void texto(const char* string,float x,float y) 
{  
 int j = strlen( string );
  glRasterPos2f( x, y );
  for( int i = 0; i < j; i++ ) {
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
  }
}

void SpecialKeys(int key, int x, int y)
{
  switch(key)
  {
    case GLUT_KEY_DOWN: down=true; CurrLine++; if(CurrLine==6) CurrLine=0; 
                        if(CurrLine==4&&CurrRow==1)CurrRow=0;break;
  
	case GLUT_KEY_UP: up=true; CurrLine--; if(CurrLine==-1) CurrLine=5; break;
				
	case GLUT_KEY_LEFT: left=true; CurrRow++; if(CurrRow==2) CurrRow=-1; if(CurrLine==4&&CurrRow==1)CurrRow=-1;
                      if(CurrLine==0||CurrLine==5&&CurrRow!=0)CurrRow=0; break;
	case GLUT_KEY_RIGHT: right=true; CurrRow--; if(CurrRow==-2) CurrRow=1; if(CurrLine==4&&CurrRow==1)CurrRow=0;
                      if(CurrLine==0||CurrLine==5&&CurrRow!=0)CurrRow=0; break;  
  }

  //Redesenha Caixa de select
  glutPostRedisplay();
}

void display(void)
{
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    double w = glutGet(GLUT_WINDOW_WIDTH);
	double h = glutGet(GLUT_WINDOW_HEIGHT);
	glColor3f(1,1,1);
	glRectf(-200,-h,200,h);//normal
    //Desenha Eixos
    glLineWidth(1);
    glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex2f(200,0);
        glVertex2f(-200,0);
        glVertex2f(0,-200);
        glVertex2f(0,200);
    glEnd();
    
    glPointSize (5.0);
    glPolygonMode (GL_FRONT, GL_FILL);

    glLineWidth(3); // Determina a espessura da linha que ser� desenhada
    
	glPushMatrix();
	{
	glScalef(1.5,1.5,1);
  glTranslatef(0,60,1);
	}
  //Ve cor em "status", desenha botoes
  int currRow=3;
  for (int i=0;i<3;i++){
    int currLine=0;
    currRow--;
    for (int j=0;j<6;j++){
      if (status[currLine][currRow] == 1 && j!=0 && j!=5)
        glColor3f(0,0,1);
      else glColor3f(0,1,0);
      currLine++;
      if ((i==0&&j==0)||(i==2&&j==0)||(i==0&&j==5)||(i==2&&j==5)||(i==0&&j==4)) continue; //nao desenhar 4 cantos e primeiro
      if(j==4&&i==1)                                                                      //da linha 4 que soh tem 2
        glRectf(-110+(80*i/2),50-(50*j),-50+(80*i/2),70-(50*j));
      else if(j==4&&i==2)
        glRectf(10,-150,70,-130);
      else glRectf(-110+(80*i),50-(50*j),-50+(80*i),70-(50*j));
    }
  }
  glColor3f(0,0,0);
                            texto("Iniciar",-20,55);
                            texto("Velocidade",-36,30);
    texto("Normal",-105,5); texto("Rapido",-23,5); texto("Turbo",60,5);
                            texto("Tamanho",-33,-20);
    texto("20x10",-102,-45); texto("30x15",-19,-45); texto("50x25",60,-45);
                            texto("Cores",-20,-70);
    texto("Cor A",-102,-95); texto("Cor B",-19,-95); texto("Cor C",60,-95);
                            texto("Modo",-20,-120);
              texto("Normal",-65,-145); texto("Bebado",16,-145);
                            texto("Sair",-12,-195);


	/*
    //Cor dependendo do status, botao, texto
    glColor3f(0,1,0);
    glRectf(-30,50,30,70);//iniciar
    glColor3f(1,1,1); texto("Iniciar",-30,50,100,100);
    int currRow=3;
    for (int i=0;i<3;i++){
      int currLine=1;
      currRow--;
      for (int j=1;j<4;j++){
        if (status[currLine][currRow] == 1 && j!=0 && j!=5)
          glColor3f(0,0,1);
        else glColor3f(0,1,0);
        currLine++;
        if(j!=5)
          glRectf(-110+(80*i),50-(50*j),-50+(80*i),70-(50*j));
      }
    }
    //Modo
    if (status[4][1] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(-70,-150,-10,-130); glColor3f(0,1,0);//Normal
    if (status[4][0] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(10,-150,70,-130);//Bebado
    //Sair
    glColor3f(0,1,0);
    glRectf(-30,-200,30,-180);//Sair
    */
    glPopMatrix();
    glLoadIdentity();
    glScalef(1.5,1.5,1);
    std::cout<<CurrLine<<" "<<CurrRow<<" "<<status[CurrLine][CurrRow+1]<<std::endl; //posicao da caixa de selecao
    //Translacao pra caixa de selecao
    if (CurrLine==0||CurrLine==5) 
		glTranslatef(80*-0,-CurrLine*50,1);
    if (CurrLine==1||CurrLine==2||CurrLine==3)
		glTranslatef(80*-CurrRow,-CurrLine*50,1);
    if (CurrLine==4){
		if (CurrRow ==1)
			glTranslatef(80*-CurrRow+40,-CurrLine*50,1);
		if (CurrRow !=1)
			glTranslatef(80*-CurrRow-40,-CurrLine*50,1);
    
	}
	//reseta teclas		
	down = false;
	up = false;
	left = false;
	right = false;
	enter = false;
	//desenho da caixa
  glBegin(GL_LINE_LOOP);
		glLineWidth(5);
		glColor3f(1,0,0);
		glVertex2f(-30, 110);
		glVertex2f(30, 110);
		glVertex2f(30, 130);
		glVertex2f(-30, 130);
	glEnd();

  glFlush ();
}

void reshape(GLsizei w, GLsizei h)
{					
	double width = glutGet(GLUT_WINDOW_WIDTH);
	double height = glutGet(GLUT_WINDOW_HEIGHT);
    // Evita a divisao por zero
    if(h == 0) h = 1;
    // Especifica as dimensões da Viewport
    glViewport (0, 0, (GLsizei) w, height);
    //glViewport(0, 0, w, h);
    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Estabelece a janela de seleção (left, right, bottom, top)
	//glOrtho(-w,w,-h,h,-1,1);
	glOrtho( -width/2.f, width/2.f, -height/2.f, height/2.f, -1, 1 );
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void init(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glShadeModel (GL_FLAT);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (350, 500);
    glutInitWindowPosition (glutGet(GLUT_SCREEN_WIDTH)/3,glutGet(GLUT_SCREEN_HEIGHT)/5);
    glutCreateWindow ("Transformacoes 2D");
    init ();
    glutKeyboardFunc(handle_key);
    glutSpecialUpFunc(SpecialKeys);//pegar arrow keys
    glutDisplayFunc(display);
	glutReshapeFunc(reshape); 
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}
