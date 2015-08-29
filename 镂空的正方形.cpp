#include <GL/glut.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

void myDisplay(void)
{
	static GLubyte Mask[128];
	FILE *fp;
	fp = fopen("mask.bmp", "rb");
	if( !fp )
	exit(0);
	if( fseek(fp, -(int)sizeof(Mask), SEEK_END) )
	exit(0);
	if( !fread(Mask, sizeof(Mask), 1, fp) )
	exit(0);
	fclose(fp);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(Mask);
	glRectf(-0.5f, -0.5f, 0.0f, 0.0f); // �����·�����һ�����ο�Ч����������
	glDisable(GL_POLYGON_STIPPLE);
	glRectf(0.0f, 0.0f, 0.5f, 0.5f); // �����Ϸ�����һ�����ο�Ч����������
	glFlush();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("��һ��OpenGL����");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}
