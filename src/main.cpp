#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Bitmap.h"
#include "Renderer.h"
#include "RendererFactory.h"

Renderer *gRenderer = NULL;
Bitmap *gBitmap = NULL;

/**
 * Used for shader program
 */
GLuint gVbo;
GLuint gProgram;
GLuint gVtxShader;
GLuint gFrgShader;

#define VERTEX_SHADER_SOURCE 	"	\
	void main() {					\
									\
}"									

const char* FRAGMENT_SHADER_SOURCE = "";

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
			exit(2);
		} else {
			gRenderer->setArtwork(gBitmap);
		}
	}

	glGenBuffers(1, &gVbo);
	gProgram = glCreateProgram();
	if (0 == gProgram) {
		printf("Failed create program\n");
		exit(3);
	}
	gVtxShader = glCreateShader(GL_VERTEX_SHADER);
	if (0 == gVtxShader) {
		printf("Failed create vertex shader\n");
		exit(4);
	}
	gFrgShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (0 == gFrgShader) {
		printf("Failed create fragment shader\n");
		exit(5);
	}


	printf("strlen vertex shader source length:%lu\n", strlen(VERTEX_SHADER_SOURCE));

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
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		printf("Error:%s\n", glewGetErrorString(err));
		return -1;
	}
	init(argc, argv);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onNormalKeyClicked);
	glutSpecialFunc(onSpecialKeyClicked);
	glutMainLoop();
	return 0;
}
