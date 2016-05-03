#include <GL/glut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>

#include "Bitmap.h"
#include "Renderer.h"
#include "RendererFactory.h"

Renderer *gRenderer = NULL;

void init(int argc, char* argv[]) {
	gRenderer = RendererFactory::createRenderer(TYPE_REALTIME);
	if (NULL == gRenderer) {
		printf("Failed create renderer.\n");
		exit(1);
	}

	if (2 == argc) {
		Bitmap *bmp = Bitmap::load(argv[1]);
		if (NULL == bmp) {
			printf("Failed load %s\n", argv[1]);
		} else {
			gRenderer->setArtwork(bmp);
		}
	}
}

void onDisplay() {
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
	init(argc, argv);
	glutDisplayFunc(onDisplay);
	glutKeyboardFunc(onNormalKeyClicked);
	glutMainLoop();
	return 0;
}
