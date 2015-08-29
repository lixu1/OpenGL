#include<GL/glut.h>

void Shape()
{
	glBegin(GL_POLYGON);
	glVertex2f(0.1,0);
	glVertex2f(0.1,0.05);
	glVertex2f(0.15,0.1);
	glVertex2f(0.2,0.05);
	glVertex2f(0.2,0);
	glEnd();
	glFlush();
}

void display()
{
	glMatrixMode(GL_PROJECTION);
	glClear(GL_COLOR_BUFFER_BIT);
	for(int jiao=0;jiao<360;jiao++)
	{
		glLoadIdentity();
		glRotatef(jiao,0,0,1);
		Shape();
		jiao+=40;
	}
}



int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("第二次作业");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}