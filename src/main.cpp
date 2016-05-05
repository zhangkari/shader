#include <GL/glut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>

#include "Bitmap.h"
#include "Renderer.h"
#include "RendererFactory.h"

Renderer *gRenderer = NULL;
Bitmap *gBitmap = NULL;

void init(int argc, char* argv[]) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gRenderer = RendererFactory::createRenderer(TYPE_REALTIME);
	if (NULL == gRenderer) {
		printf("Failed create renderer.\n");
		exit(1);
	}

	if (2 == argc) {
		gBitmap = Bitmap::load(argv[1]);
		if (NULL == gBitmap) {
			printf("Failed load %s\n", argv[1]);
		} else {
			gRenderer->setArtwork(gBitmap);
		}
	}
}

void onReshape(int w, int h) {
	printf("onReshape()\n");
	glViewport(0, 0, (GLsizei)w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0);
}

void onDisplay() {
	printf("onDisplay()\n");
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glutWireTeapot(1.5);
//	glutSolidTeapot(2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0);

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

void onSpecialKeyClicked(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		printf("up\n");
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Opengl View");
	init(argc, argv);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onNormalKeyClicked);
	glutSpecialFunc(onSpecialKeyClicked);
	glutMainLoop();
	return 0;
}
