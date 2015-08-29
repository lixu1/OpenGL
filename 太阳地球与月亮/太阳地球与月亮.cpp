#include<GL/glut.h>

// ̫�������������
// ����ÿ���¶���30��
// һ��12���£�����360��
static int day = 200; // day�ı仯����0��359
void myDisplay(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 400000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);
	
	// ���ƺ�ɫ��"̫��"
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(69600000, 200000, 200000);
	// ������ɫ��"����"
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(150000000, 0.0f, 0.0f);
	glutSolidSphere(15945000, 200000, 200000);
	// ���ƻ�ɫ��"����"
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(38000000, 0.0f, 0.0f);
	glutSolidSphere(4345000, 200000, 200000);
	
	glFlush();
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("simple");
	glutDisplayFunc(myDisplay);
	init();
	glutMainLoop();
	return 0;
}