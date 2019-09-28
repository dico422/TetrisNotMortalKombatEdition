//#ingure -clude <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cstring>
//using namespace std;


double scale = 1;
bool reflectX = 0;
bool reflectY = 0;
double offsetX = 0;
double offsetY = 0;
double rot=0;
bool O = 0;
bool E = 0;
bool down,up,left,right =false;
int CurrLine =0;
int CurrRow = 0;
bool enter = false;


//std::vector<std::vector<int> > status (6,std::vector<int>(3));
int status [6][3] = {{0,0,0},
                     {0,0,1},
                     {0,0,1},
                     {0,0,1},
                     {0,1,1},
                     {0,0,0}};

	
//std::vector<botao> botoes (13);

void handle_key(unsigned char key, int mousex, int mousey)
{
  switch(key)
  {
    case 'a': case 'A' : if(scale<10) scale*=1.1; break;
    case 'd': case 'D' : if(scale>1) scale/=1.1;break;
    case 'x': case 'X' : if(!reflectX) reflectX = true;
                         else reflectX = false;break;
    case 'y': case 'Y' : if (!reflectY) reflectY = true;
                         else reflectY = false; break;
    case 'r': case 'R':  rot+=90; break;
    case 13: 
			if(status[CurrLine][CurrRow+1]==0) { 
        for(int i=0;i<3;i++)
          status[CurrLine][i]= 0;
        status[CurrLine][CurrRow+1]= 1; }
      if (CurrLine == 4 && CurrRow==1) status[4][1]= status[4][2];
      if (CurrLine == 4 && CurrRow==0) status[4][2]= status[4][1];
           
      break;
  }

  //Redesenha após atualizar valor da escala
  glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
  switch(key)
  {
    case GLUT_KEY_DOWN: down=true; CurrLine++; if(CurrLine==6) CurrLine=0; break;
	
	case GLUT_KEY_UP: up=true; CurrLine--; if(CurrLine==-1) CurrLine=5; break;
				
	case GLUT_KEY_LEFT: left=true; CurrRow++; if(CurrRow==2) CurrRow=-1; if(CurrLine==4&&CurrRow==1)CurrRow=-1; break;
	case GLUT_KEY_RIGHT: right=true; CurrRow--; if(CurrRow==-2) CurrRow=1; if(CurrLine==4&&CurrRow==1)CurrRow=0;  break;
    
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
	glColor3f(0,0,0);
	glRectf(-200,-h,200,h);//normal
    //Desenha Eixos
    glLineWidth(1);
    glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex2f(100,0);
        glVertex2f(-100,0);
        glVertex2f(0,-100);
        glVertex2f(0,100);
    glEnd();
    
    glPointSize (5.0);
    glPolygonMode (GL_FRONT, GL_FILL);

    glLineWidth(3); // Determina a espessura da linha que ser� desenhada
     
    glRotatef(rot, 0, 0, 1);

    glScalef(scale,scale,1);

    if (reflectX) {
        glScalef(1, -1, 1);
    }
    if (reflectY){
        glScalef(-1, 1, 1);
    }

    if (E) {
        glScalef(-1, 1, 1);
        glTranslatef(25,25,0);
    }
    if (O) {
        glScalef(1, 1, 1);
        glTranslatef(0, 0, 0);
    }
    
	glPushMatrix();
	{
	glScalef(1.5,1.5,1);
	glTranslatef(0,60,1);
	}
    //botoes
  /*  
    for (int i=1;i<=3;i++){
      for (int j=1;j<=6;j++){
        if (status[CurrLine][CurrRow+1] == 1){
          glColor3f(0,0,1);}
        else glColor3f(0,1,0);
        if (j!=5){
          if(i==1){
            if(j==5||j==6)
              break;
            glRectf(-110,0-(50*j),-50,20-(50*j));
          }
          if(i==2){
            glRectf(-30,50-(50*j),30,70-(50*j));
          }
          if(i==3){
            if(j==5||j==6)
              break;
            glRectf(50,0-(50*j),110,20-(50*j));
          }
        }
        else if(j==5) {glRectf(-70,-150,-10,-130);//Normal
            glRectf(10,-150,70,-130);//Bebado
          }
      }
	}
	*/
    glColor3f(0,1,0);
    glRectf(-30,50,30,70);//iniciar
    //velocidade
    if (status[1][2] == 1) glColor3f(0,0,1); else glColor3f(0,1,0);
    glRectf(-110,0,-50,20); glColor3f(0,1,0);//normal
    if (status[1][1] == 1) glColor3f(0,0,1); else glColor3f(0,1,0);
    glRectf(-30,0,30,20); glColor3f(0,1,0);//rapido 
    if (status[1][0] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(50,0,110,20); glColor3f(0,1,0);//turbo
    //tamanho
    if (status[2][2] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(-110,-50,-50,-30); glColor3f(0,1,0);//20x10
    if (status[2][1] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(-30,-50,30,-30); glColor3f(0,1,0);//30x15
    if (status[2][0] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(50,-50,110,-30); glColor3f(0,1,0);//50x25
    //Cores
    if (status[3][2] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(-110,-100,-50,-80); glColor3f(0,1,0);//20x10
    if (status[3][1] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(-30,-100,30,-80); glColor3f(0,1,0);//30x15
    if (status[3][0] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(50,-100,110,-80); glColor3f(0,1,0);//50x25
    //Modo
    if (status[4][1] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(-70,-150,-10,-130); glColor3f(0,1,0);//Normal
    if (status[4][0] == 1) glColor3f(0,0,1); else glColor3f(0,1,0); 
    glRectf(10,-150,70,-130);//Bebado
    //Sair
    glColor3f(0,1,0);
    glRectf(-30,-200,30,-180);//Sair
    
    
    glPopMatrix();
    glLoadIdentity();
    glScalef(1.5,1.5,1);
    std::cout<<CurrLine<<" "<<CurrRow<<" "<<status[CurrLine][CurrRow+1]<<std::endl;
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
			
	down = false;
	up = false;
	left = false;
	right = false;
	enter = false;
	
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
