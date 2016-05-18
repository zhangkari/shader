#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Bitmap.h"
#include "NormalEffect.h"
#include "Renderer.h"
#include "RendererFactory.h"
#include "ShaderManager.h"
#include "System.h"

Renderer *gRenderer = NULL;
Bitmap *gBitmap = NULL;
ShaderManager *gShaderMgr;

#define VERTEX_SHADER_SOURCE 	"								\
	void main() {												\
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;	\
}"

#define FRAGMENT_SHADER_SOURCE  "								\
	void main() {												\
		gl_FragColor = vec4(1.0, 0.0, 0.0, 0.9);				\
}"

void init(int argc, char* argv[]) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gRenderer = RendererFactory::createRenderer(TYPE_REALTIME);
	if (NULL == gRenderer) {
		printf("Failed create renderer.\n");
		exit(1);
	}

	if (2 == argc) {
		uint64_t t1 = System :: current();
		gBitmap = Bitmap::load(argv[1]);
		uint64_t t2 = System :: current();
		printf("Load %s cost %lu ms\n", argv[1], t2 - t1);
		if (NULL == gBitmap) {
			printf("Failed load %s\n", argv[1]);
			exit(1);
		} else {
			gRenderer->setArtwork(gBitmap);
		}
	}

	gShaderMgr = ShaderManager :: getInstance();
	gShaderMgr->useEffect(new NormalEffect);
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
