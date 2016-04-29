/****************************************
 * file name:	RealtimeRenderer.h
 * description:	define real time renderer
 * author:		kari.zhang
 * date:		2016-4-29
 ****************************************/

#ifndef RTRENDERER__H__
#define RTRENDERER__H__

#include "Renderer.h"

class RealtimeRenderer : public Renderer {

	public:
		~RealtimeRenderer();

	protected:
		void draw(int numInstance);

};

#endif
