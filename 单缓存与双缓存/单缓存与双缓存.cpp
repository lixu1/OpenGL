#include <GL/glut.h>
#include <iostream>
#include <math.h>

int singleb,doubleb;
int id;
int theta=0;
#define DEG_TO_RAD 0.017453

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex2f(sin(DEG_TO_RAD*theta),cos(DEG_TO_RAD*theta));
	glVertex2f(-sin(DEG_TO_RAD*theta),cos(DEG_TO_RAD*theta));
	glVertex2f(-sin(DEG_TO_RAD*theta),-cos(DEG_TO_RAD*theta));
	glVertex2f(sin(DEG_TO_RAD*theta),-cos(DEG_TO_RAD*theta));
	glEnd();
	glutSwapBuffers();
}

void spinDisplay(void)
{
	theta+=2;
	if(theta>360)theta-=360;
	glutSetWindow(singleb);
	glutPostWindowRedisplay(singleb);

	glutSetWindow(doubleb);
	glutPostWindowRedisplay(doubleb);
}

void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		glutIdleFunc(spinDisplay);
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
		glutIdleFunc(NULL);
}

void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2,2,-2,2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void mykey(unsigned char key,int x,int y)
{
	if(key=='Q'||key=='q')
		exit(0);
}

void mymenu(int value)
{
	if(value==1) exit(0);
	if(value==2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
	}
}
void myinit()
{
	glClearColor(0,0,0,0);
	glColor3f(1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1,1,-1,1);
}
int main(int argc,char **argv)
{	
	glutInit( &argc ,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	singleb=glutCreateWindow("single buffered");
	myinit();
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutIdleFunc(spinDisplay);
	glutMouseFunc(mouse);
	glutKeyboardFunc(mykey);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(310,0);
	doubleb=glutCreateWindow("double buffered");
	myinit();
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutIdleFunc(spinDisplay);
	glutMouseFunc(mouse);
	id=glutCreateMenu(mymenu);
	glutAddMenuEntry("quit",1);
	glutAddMenuEntry("Clear Screen",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}


