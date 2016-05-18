/************************************
 * file name:	Effect.cpp
 * description:	define base effect
 * author:		kari.zhang
 * date:		2016-5-18
 ***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "Effect.h"

Effect :: Effect() {

}

Effect :: ~Effect() {

}

GLuint Effect :: createShader(ShaderType, const char* shaderSource) {
	if (NULL == shaderSource) {
		printf("Invalid shader source.\n");
		return 0;
	}

	GLuint shader = glCreateShader(GL_VERTEX_SHADER);
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
		printf("Failed compile shader.\n");
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}
