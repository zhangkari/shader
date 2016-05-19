/*******************************************
 * file name:	RealtimeRenderer.c
 * description:	implement real time renderer
 * author:		kari.zhang
 * date:		2016-4-29
 ******************************************/

#include "Bitmap.h"
#include "RealtimeRenderer.h"

RealtimeRenderer :: ~RealtimeRenderer() {

}

void RealtimeRenderer::draw(int numInstance) {

	if (mArtwork == NULL) {
		return;
	}

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
