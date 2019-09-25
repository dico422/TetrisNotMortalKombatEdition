#include <GL/glut.h>

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();
	{
	
		
	}
	glPopMatrix();
	
	glFlush ();
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

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
}


void initGame(int argc, char** argv)
{

	glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (600, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Tetris: \"Nao eh mortal kombat\" Edition");
    glutFullScreen();
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	
}
