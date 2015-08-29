#include <GL/glut.h>
void draw()
{
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.36,0,0);//i
	glVertex3f(0.36,0,0.3);//j
	glVertex3f(0.15,0,0.6);//k
	glVertex3f(0,0,0.6);//b
	glVertex3f(0,0,0);//a
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0,0);//a
	glVertex3f(0,0,0.6);//b
	glVertex3f(0,0.16,0.6);//c
	glVertex3f(0,0.16,0.1);//d
	glVertex3f(0,0.5,0.1);//e
	glVertex3f(0,0.5,0);//f
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0.5,0);//f
	glVertex3f(0.21,0.3,0);//g
	glVertex3f(0.36,0.3,0);//h
	glVertex3f(0.36,0,0);//i
	glVertex3f(0,0,0);//a
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.15,0.16,0.6);//l
	glVertex3f(0,0.16,0.6);//c
	glVertex3f(0,0,0.6);//b
	glVertex3f(0.15,0,0.6);//k
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.15,0.16,0.6);//l
	glVertex3f(0.15,0,0.6);//k
	glVertex3f(0.36,0,0.3);//j
	glVertex3f(0.36,0.16,0.3);//m
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.36,0.16,0.3);//m
	glVertex3f(0.36,0,0.3);//j
	glVertex3f(0.36,0,0);//i
	glVertex3f(0.36,0.3,0);//h
	glVertex3f(0.36,0.3,0.1);//o
	glVertex3f(0.36,0.16,0.1);//n
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.36,0.3,0.1);//o
	glVertex3f(0.21,0.3,0.1);//p
	glVertex3f(0,0.5,0.1);//e
	glVertex3f(0,0.16,0.1);//d
	glVertex3f(0.36,0.16,0.1);//n
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0.16,0.1);//d
	glVertex3f(0,0.16,0.6);//c
	glVertex3f(0.15,0.16,0.6);//l
	glVertex3f(0.36,0.16,0.3);//m
	glVertex3f(0.36,0.16,0.1);//n
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0.5,0.1);//e
	glVertex3f(0.21,0.3,0.1);//p
	glVertex3f(0.21,0.3,0);//g
	glVertex3f(0,0.5,0);//f
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.21,0.3,0.1);//p
	glVertex3f(0.36,0.3,0.1);//o
	glVertex3f(0.36,0.3,0);//h
	glVertex3f(0.21,0.3,0);//g
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(500,0,500,500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(0,0.1,0,0.1,0,1000);
	glTranslatef(0,0,-1);
	draw();
	glViewport(0,0,500,500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-4,4);
	gluLookAt(2,2,2,0,0,0,0,1,0);
	draw();
	glutSwapBuffers();
}


void init()
{
	glClearColor(1,1,1,1);
	glColor3f(0,0,0);
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1000,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("立体图形轴视图与透视图");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
