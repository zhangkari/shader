/*******************************************
 * file name:	RealtimeRenderer.c
 * description:	implement real time renderer
 * author:		kari.zhang
 * date:		2016-4-29
 ******************************************/

#include "Bitmap.h"
#include "RealtimeRenderer.h"

#ifndef WIN_WIDTH
#define WIN_WIDTH 600
#endif

#ifndef WIN_HEIGHT
#define WIN_HEIGHT 600
#endif

RealtimeRenderer :: ~RealtimeRenderer() {

}

void RealtimeRenderer::draw(int numInstance) {

	if (mArtwork == NULL) {
		return;
	}

	gluOrtho2D(0, (GLdouble)mArtwork->getWidth() / 2, 0, (GLdouble)mArtwork->getHeight() / 2);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glRasterPos2i(0, 0);

	float imgRatio = mArtwork->getHeight() / mArtwork->getWidth();
	float winRatio = WIN_HEIGHT / WIN_WIDTH;

	int width, height;
	if (imgRatio >= winRatio) {
		height = WIN_HEIGHT;
		width = (int)(height / imgRatio);
	} else {
		width = WIN_WIDTH;
		height = width * imgRatio;
	}

	int left = (WIN_WIDTH - width) / 2;
	int top = (WIN_HEIGHT - height) / 2;
	glViewport(left, top, width, height);

	int fmt = GL_RGB;
	switch (mArtwork->getFmt()) {
		case RGBA32:
			fmt = GL_RGBA;
			break;
	}

	glDrawPixels(mArtwork->getWidth(), 
			mArtwork->getHeight(), 
			fmt, 
			GL_UNSIGNED_BYTE, 
			mArtwork->getBlock());

}
