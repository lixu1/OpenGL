#include<GL/glut.h>
#include "stdio.h"
#include <iostream>

#define MAX_CPTS 25
GLfloat cpts[MAX_CPTS][3];
int ncpts=0;
static int width=500,height=500;
void drawCurves()
{
	int i;
	for(i=0;i<ncpts-3;i=i+3)
	{
		glMap1f(GL_MAP1_VERTEX_3,0,1,3,4,cpts[i]);
		glMapGrid1f(30,0,1);
		glEvalMesh1(GL_LINE,0,30);
	}
	glFlush();
}

static void display()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for(i=0;i<ncpts;i++)
		glVertex3fv(cpts[i]);
	glEnd();
	glFlush();
}
static void mouse(int button,int state,int x,int y)
{
	float wx,wy;
	if(button!=GLUT_LEFT_BUTTON || state!=GLUT_DOWN)
		return;
	wx=(2*x)/(float)(width-1)-1;
	wy=(2*(height-y))/(float)(height)-1;

	if(ncpts==MAX_CPTS)return;

	cpts[ncpts][0]=wx;
	cpts[ncpts][1]=wy;
	cpts[ncpts][2]=0;
	ncpts++;

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(wx,wy,0);
	glEnd();
	glFlush();
}
void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'q':
	case 'Q':
		exit(1);
		break;
	case 'c':
	case 'C':
		ncpts=0;
		glutPostRedisplay();
		break;
	case 'e':
	case 'E':
		glutPostRedisplay();
		break;
	case 'b':
	case 'B':
		drawCurves();
		break;
	}
}

void reshape(int w,int h)
{
	width=w;
	height=h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,w,h);
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(width,height);
	glutCreateWindow("BEzier Curve");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glClearColor(1,1,1,1);
	glColor3f(0,0,0);
	glPointSize(5);
	glEnable(GL_MAP1_VERTEX_3);
	glutMainLoop();
	return 0;
}
