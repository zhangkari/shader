/************************************
 * file name:	Effect.h
 * description:	define base effect
 * author:		kari.zhang
 * date:		2016-5-18
 ***********************************/

#ifndef EFFECT__H__
#define EFFECT__H__

#include <GL/gl.h>

enum ShaderType {
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRGMNT_SHADER = GL_FRAGMENT_SHADER
};

class Effect {

	friend class ShaderManager;

	public:
		Effect();
		virtual ~Effect();
		bool setVertexSource(const char* source);
		bool setFragmentSource(const char* source);

	protected:
		virtual void work() = 0;

		/*
		 * create a spcecified type and specified source shader 
		 * return:
		 *		0 if error occurs, otherwise ok
		 */
		GLuint createShader(ShaderType type, const char* shaderSource);

	protected:
		GLuint mVbo;
		GLuint mVtxShader;
		GLuint mFrgShader;
};

#endif
