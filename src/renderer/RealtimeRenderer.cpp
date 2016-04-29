/*******************************************
 * file name:	RealtimeRenderer.c
 * description:	implement real time renderer
 * author:		kari.zhang
 * date:		2016-4-29
 ******************************************/

#include "RealtimeRenderer.h"

RealtimeRenderer :: ~RealtimeRenderer() {

}

void RealtimeRenderer::draw(int numInstance) {
	glBegin(GL_TRIANGLES);	
	{
		glColor3f(1.0f, 0.0f, 0.0f);	
		glVertex2f(0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);	
		glVertex2f(1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);	
		glVertex2f(0.5f, 1.0f);
	}
	glEnd();
}
