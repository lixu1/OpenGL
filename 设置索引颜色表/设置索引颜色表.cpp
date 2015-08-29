#include <windows.h>
#include <GL/gl.h>
#include <GL/glaux.h>

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glaux.lib")

#include <math.h>
const GLdouble Pi = 3.1415926536;
void myDisplay(void)
{
	int i;
	for(i=0; i<8; ++i)
		auxSetOneColor(i, (float)(i&0x04), (float)(i&0x02), (float)(i&0x01));
	glShadeModel(GL_FLAT);
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for(i=0; i<=8; ++i)
	{
		glIndexi(i);
		glVertex2f( (float)cos(i*Pi/4), (float)sin(i*Pi/4));
	}
	glEnd();
	glFlush();
}

int main(void)
{
	auxInitDisplayMode(AUX_SINGLE|AUX_INDEX);
	auxInitPosition(0, 0, 400, 400);
	auxInitWindow("L");
	myDisplay();
	system("pause");
	Sleep(10 * 1000);
	return 0;
}
