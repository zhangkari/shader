/************************************
 * file name:	Renderer.h
 * description:	define base renderer
 * author:		kari.zhang
 * date:		2016-4-29
 ***********************************/

#ifndef RENDERER__H__
#define RENDERER__H__

#include <GL/gl.h>
#include <GL/glext.h>

#include "Bitmap.h"

#define MAX_INSTANCES_PER_SIDE 16
#define MAX_INSTANCES (MAX_INSTANCES_PER_SIDE * MAX_INSTANCES_PER_SIDE)

struct Vertex {
	GLfloat pos[2];
	GLubyte rgba[4];
};

class Renderer {
	public:
		virtual ~Renderer();
		void resize(int w, int h);
		void render();
		void setArtwork(Bitmap* bitmap);

	protected:
		Renderer();
		virtual void draw(int numInstances) = 0;

	protected:
		float mScale[2];
		int mNumInstances;
		float mAngles[MAX_INSTANCES];
		Bitmap *mArtwork;
};

#endif
