#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Bitmap.h"
#include "Log.h"
#include "NormalEffect.h"
#include "Renderer.h"
#include "RendererFactory.h"
#include "ShaderManager.h"
#include "System.h"

#define WIN_WIDTH 600
#define WIN_HEIGHT 600

#define INTERVAL 50

Renderer *gRenderer = NULL;
Bitmap *gBitmap = NULL;
ShaderManager *gShaderMgr;

void init(int argc, char* argv[]) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gRenderer = RendererFactory::createRenderer(TYPE_REALTIME);
	if (NULL == gRenderer) {
        Log::d("Failed create renderer.\n");
		exit(1);
	}

	if (2 == argc) {
		uint64_t t1 = System :: current();
		gBitmap = Bitmap::load(argv[1]);
		uint64_t t2 = System :: current();
        Log::d("Load %s cost %lu ms\n", argv[1], t2 - t1);
		if (NULL == gBitmap) {
            Log::d("Failed load %s\n", argv[1]);
			exit(1);
		} else {
			gRenderer->setArtwork(gBitmap);
		}
	}

	gShaderMgr = ShaderManager :: getInstance();

	Effect *normalEffect = new NormalEffect;
    char *vert = System::loadTextFile("vert.shr");
    char *frag = System::loadTextFile("frag.shr");
	normalEffect->setVertexSource(vert);
	normalEffect->setFragmentSource(frag);
    free (vert);
    free (frag);
	gShaderMgr->useEffect(normalEffect);
}

void onReshape(int w, int h) {
	Log::d("onReshape()\n");
}

void onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

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
    switch (key) {
        case GLUT_KEY_UP:
            Log::d("up\n");
            break;

        case GLUT_KEY_LEFT:
            Log::d("left\n");
            break;

        case GLUT_KEY_RIGHT:
            Log::d("right\n");
            break;

        case GLUT_KEY_DOWN:
            Log::d("down\n");
            break;
    }
}

void onTimer(int id) {
    glutPostRedisplay();
    glutTimerFunc(INTERVAL, onTimer, 1);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow(argv[1]);
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		Log::d("Error:%s\n", glewGetErrorString(err));
		return -1;
	}
	init(argc, argv);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
    glutTimerFunc(INTERVAL, onTimer, 1);
	glutKeyboardFunc(onNormalKeyClicked);
	glutSpecialFunc(onSpecialKeyClicked);
	glutMainLoop();
	return 0;
}
