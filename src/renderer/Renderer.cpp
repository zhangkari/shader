/**************************************
 * file name:	Renderer.cpp
 * description:	implement base renderer
 * author:		kari.zhang
 * date:		2016-4-29
 *************************************/

#include "Renderer.h"

Renderer :: ~Renderer() {

}

Renderer :: Renderer() {

}

void Renderer :: render() {
	draw(mNumInstances);
}

void Renderer :: resize(int w, int h) {

}

void Renderer :: setArtwork(Bitmap *bitmap) {
	mArtwork = bitmap;
}
