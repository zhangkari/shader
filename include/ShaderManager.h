/************************************
 * file name:	ShaderManager.h
 * description:	manager shader
 * author:		kari.zhang
 * date:		2016-5-18
 ***********************************/

#ifndef SHADERMANAGER__H__
#define SHADERMANAGER__H__

#include <GL/gl.h>
#include "Effect.h"

class ShaderManager {
	public:
		virtual ~ShaderManager();
		void useEffect(Effect *effect);
		static ShaderManager* getInstance();

	protected:
		ShaderManager();

	protected:
		GLuint mCurVtxShader;
		GLuint mCurFrgShader;
		GLuint mProgram;
		static ShaderManager* sInstance;
};

#endif
