/*****************************************
 * file name:	RendererFactory.c
 * description:	implement renderer factory
 * author:		kari.zhang
 * date:		2016-4-29
 ****************************************/

#include "OfflineRenderer.h"
#include "RealtimeRenderer.h"
#include "RendererFactory.h"

Renderer* RendererFactory :: createRenderer(RendererType type) {
	if (type == TYPE_OFFLINE) {
		return new OfflineRenderer();
	} else if (type == TYPE_REALTIME) {
		return new RealtimeRenderer();
	} else {
		return NULL;
	}
}
