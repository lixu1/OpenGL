#include <GL/glut.h>

#include <math.h>

const int n = 100000;

const GLfloat Pi = 3.1415926536f;

void DrawCircle(float x,float y,float R)
{	
     int i;
     glBegin(GL_LINE_LOOP);
     for(i=0; i<n; ++i)
         glVertex2f(x+R*cos(2*Pi/n*i),y+R*sin(2*Pi/n*i));
     glEnd();
     glFlush();
}
void DrawLine(float x1,float y1,float x2,float y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glEnd();
	glFlush();
}
void DrawCircle2(float x,float y,float R,int p,int q)//p,q表示角度
{
	int i;
	glBegin(GL_POINTS);
	for(i=n*p/360; i<=n*q/360; ++i)
      glVertex2f(x+R*cos(2*Pi/n*i),y+R*sin(2*Pi/n*i));
	glEnd();
	glFlush();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
  DrawCircle(0.26,0.1,0.1);
  DrawCircle(0.26,0.1,0.06);
  DrawCircle(0.05,0.15,0.04);
  DrawCircle(0.05,0.05,0.04);
  DrawLine(0.05,0,0.26,0);
  DrawLine(0,0.05,0,0.15);
  DrawLine(0.05,0.2,0.26,0.2);
  DrawCircle2(0.05,0.05,0.05,180,270);
  DrawCircle2(0.05,0.15,0.05,90,180);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(700, 700);

    glutCreateWindow("11211126_李旭的作业：画一个特殊形状");
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}