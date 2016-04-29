/**************************************
 * file name:	RendererFactory.h
 * description:	define renderer factory
 * author:		kari.zhang
 * date:		2016-4-29
 **************************************/

#ifndef RENDERERFACTORY__H__
#define RENDERERFACTORY__H__

#include "Renderer.h"

enum RendererType {
	TYPE_OFFLINE,
	TYPE_REALTIME
};

class RendererFactory {
	public:
		static Renderer* createRenderer(RendererType type);

	private:
		RendererFactory();
};

#endif
