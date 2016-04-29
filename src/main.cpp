#include <GL/glut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>

#include "Renderer.h"
#include "RendererFactory.h"

Renderer *gRenderer = NULL;

#if 0
void glText(double x, double y, char *str) {
	glRasterPos2f(x, y);
	while(*str) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str++);
	}
}
#endif

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-5, 5, -5, 5, 5, 15);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	gRenderer = RendererFactory::createRenderer(TYPE_REALTIME);
	if (NULL == gRenderer) {
		printf("Failed create renderer.\n");
		exit(1);
	}
}

void onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0, 0);

	glutWireTeapot(3);

#if 0
	glText(-0.5, -0.2, "q(Q) -- exit");
	glText(-0.5, -0.1, "SPACE -- full screen");
#endif

	if (NULL != gRenderer) {
		gRenderer->render();
	}

	glFlush();
	return;
}

void onNormalKeyClicked(unsigned char key, int x, int y) {
	if (key == 'q' || key == 'Q') {
		exit(1);

	} else if (key == 'f') {
		glutFullScreen();
		glutPostRedisplay();

	} else if (key == 'e') {
		glutReshapeWindow(600, 600);
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Opengl View");
	init();
	glutDisplayFunc(onDisplay);
	glutKeyboardFunc(onNormalKeyClicked);
	glutMainLoop();
	return 0;
}
