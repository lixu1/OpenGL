#include <iostream>
using namespace std;

#include <GL/glut.h>

float x1,y1,x2,y2;

void Draw(float x1,float y1,float x2,float y2)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(x1, y1, x2, y2);
	glFlush();

}
void myDisplay()
{
	Draw(x1,y1,x2,y2);	
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("��һ��OpenGL����");
	cout<<"���볤���ζԽǵĶ�������"<<endl;
	cin>>x1>>y1>>x2>>y2;
	
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	
	return 0;
}
