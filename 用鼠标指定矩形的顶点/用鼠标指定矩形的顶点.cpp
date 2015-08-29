#include<GL/glut.h>
#include <iostream>

GLint x1=0,y1=0,x2=0,y2=0;
int ww,hh;
bool first=true;

void mymouse(int button,int state,int x,int y)
{
	if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON)
		exit(0);
	if(state==GLUT_DOWN && button==GLUT_RIGHT_BUTTON)
	{
		if(first)
		{
			x1=x;
			y1=hh-y;
			first=!first;
		}
		else
		{
			first=!first;
			x2=x;
			y2=hh-y;
		}
		glutPostRedisplay();
	}
}

void myReshape()
{

}
void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex2i(x1,y1);
	glVertex2i(x1,hh-y2);
	glVertex2i(x2,hh-y2);
	glVertex2i(x2,y1);
	glEnd();
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(300,400);
	glutCreateWindow("»­¾ØÐÎ");
	glutDisplayFunc(mydisplay);
	glutMouseFunc(mymouse);
	glutMainLoop();
	return 0;
}