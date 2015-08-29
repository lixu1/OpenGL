#include<GL/glut.h>
#include<math.h>

#define DEG_TO_RAD 0.017453
GLfloat jiaodu=0;

void myidle()
{
	jiaodu+=10;
	if(jiaodu>360)jiaodu-=360;
	glutPostRedisplay();
}


void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
		glVertex2f(sin(DEG_TO_RAD*jiaodu),cos(DEG_TO_RAD*jiaodu));
		glVertex2f(-sin(DEG_TO_RAD*jiaodu),cos(DEG_TO_RAD*jiaodu));
		glVertex2f(-sin(DEG_TO_RAD*jiaodu),-cos(DEG_TO_RAD*jiaodu));
		glVertex2f(sin(DEG_TO_RAD*jiaodu),-cos(DEG_TO_RAD*jiaodu));
	glEnd();
	//glFlush();
	glutSwapBuffers();
}

void init()
{
	glClearColor(0,0,0,0);
	glColor3f(1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1,0.5,-1,0.5);
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutIdleFunc(myidle);

	init();
	glutMainLoop();
	return 0;
}