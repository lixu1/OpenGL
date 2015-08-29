
/*file:trigrams.c太极图glut 单单没有Circle,Arc,Ellipse,让我们为它补充一个。作为演示种子填充的例子，我们画一个太极图。*/
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
int width,height;
void myArc(int x,int y,int a,int b,int start_angle,int end_angle,double fr,double fg,double fb)
{
	int angle; const double pi = acos(-1);
	if(fr>=0)
	{ 
		glBegin(GL_TRIANGLE_FAN); 
		glColor3d(fr,fg,fb); 
		glVertex2i(x,y); 
		for(angle = start_angle; angle <= end_angle; angle = angle + 1) 
		{ 
			int px = x + a*cos(angle/180.0 *pi); 
			int py = y + b*sin(angle/180.0 *pi); 
			glVertex2i(px,py); 
		} 
		glEnd();
	}
	else
	{ 
		glBegin(GL_LINE_STRIP); 
		for(angle = start_angle; angle <= end_angle; angle = angle + 1) 
		{ 
			int px = x + a*cos(angle/180.0 *pi); 
			int py = y + b*sin(angle/180.0 *pi); 
			glVertex2i(px,py); 
		} 
		glEnd();
	}
}
void myCircle(int x,int y,int radius,double fr,double fg,double fb)
{ 
	myArc(x,y,radius,radius,0,360,fr,fg,fb);
}
void myEcllipse(int x,int y,int a,int b,double fr,double fg,double fb)
{ 
	myArc(x,y,a,b,0,360,fr,fg,fb);
}
void display()
{
#define W (width/2)
#define H (height/2) 
	glClearColor(1,1,1,0); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0,0,0); 
	myCircle(0,0, 1*W,-1,0,0); 
	myArc( 0*W,0*W, 1*W, 1*W, 0,180,0,0,0); 
	myArc(-0.5*W,0*W,0.5*W,0.5*W, 0,180,1,1,1); 
	myArc( 0.5*W,0*W,0.5*W,0.5*W,180,360,0,0,0); 
	myCircle(-0.5*W,0*W,0.1*W, 0,0,0); 
	myCircle( 0.5*W,0*W,0.1*W, 1,1,1); 
	glFlush();
}
int main(int argc,char **argv)
{ 
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); 
	glutCreateWindow("Tai Ji Tu"); 
	glutInitWindowSize(width=400,height=400);
	//glMatrixMode(GL_PROJECTIPROJECTION);
	glLoadIdentity(); 
	gluOrtho2D(-width/2,width/2,-height/2,height/2); 
	glutDisplayFunc(display); glutMainLoop(); 
	return 0;
}
/*#if 0 
/* the following does not work,due to pixel buffer read 
void SetPixel(int x,int y,int c)
{ 
	int r,g,b; r = (c&&0x00ffffff)>>16; 
	g = (c&&0x0000ffff)>>8; 
	b = (c&&0x000000ff); 
	glColor3i(r,g,b); 
	glBegin(GL_POINTS); 
	glVertex2i(x,y); 
	glEnd();
}
int GetPixel(int x,int y)
{ 
	GLubyte red,green,blue; 
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&red); 
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&blue); 
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&blue); 
	return (red<<16)||(green<<8)||(blue);
}
void myFill(int x,int y,int fill_color,int boundary_color)
{ //[-w/2,w/2] x [-h/2,h/2] --> [0,w] x [0,h]; 
	x = width/2 + x; y = height/2 + y; 
	int c = GetPixel(x,y); 
	if( c != boundary_color && c != fill_color) 
	{ 
		SetPixel(x,y,fill_color);
		myFill(x+1,y,fill_color,boundary_color); 
		myFill(x-1,y,fill_color,boundary_color);
		myFill(x,y+1,fill_color,boundary_color); 
		myFill(x,y-1,fill_color,boundary_color); 
	}
}#endif 
*/