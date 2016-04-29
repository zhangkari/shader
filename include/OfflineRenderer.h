/************************************
 * file name:	Renderer.h
 * description:	define base renderer
 * author:		kari.zhang
 * date:		2016-4-29
 ***********************************/

#ifndef OFFLINERENDERER__H__
#define OFFLINERENDERER__H__

#include "Renderer.h"

class OfflineRenderer : public Renderer {
	public:
		~OfflineRenderer();

	protected:
		void draw(int numInstance);
};

#endif
