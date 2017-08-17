/************************************
 * file name:	Effect.cpp
 * description:	define base effect
 * author:		kari.zhang
 * date:		2016-5-18
 ***********************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "Effect.h"
#include "Log.h"

Effect :: Effect() {
	mVbo = 0;
	mVtxShader = 0;
	mFrgShader = 0;
}

Effect :: ~Effect() {

}

GLuint Effect :: createShader(ShaderType type, const char* shaderSource) {
	if (NULL == shaderSource) {
		printf("Invalid shader source.\n");
		return 0;
	}

	GLuint shader = glCreateShader(type);
	if (0 == shader) {
		printf("Failed create shader\n");
		return 0;
	}
	
	int len = strlen(shaderSource);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {

#ifdef DEBUG
        char info[1024] = {0};
        glGetInfoLogARB(shader, sizeof(info), NULL, info);
        Log::d("Failed compile %s:[ %s].\n", Effect::getShaderTypeName(type), info);
#endif
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

bool Effect :: setVertexSource(const char* source) {
	assert (0 != source);
	mVtxShader = createShader(VERTEX_SHADER, source);
	return mVtxShader == 0;
}

bool Effect :: setFragmentSource(const char* source) {
	assert (0 != source);
	mFrgShader = createShader(FRGMNT_SHADER, source);
	return mFrgShader == 0;
}

