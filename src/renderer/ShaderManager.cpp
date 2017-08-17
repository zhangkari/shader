/************************************
 * file name:	ShaderManager.cpp
 * description:	manager shader
 * author:		kari.zhang
 * date:		2016-5-18
 ***********************************/

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "Log.h"
#include "ShaderManager.h"

ShaderManager* ShaderManager :: sInstance = NULL;

ShaderManager :: ~ShaderManager() {
	if (0 != mProgram) {
		glDeleteProgram(mProgram);
		mProgram = 0;
	}
}

ShaderManager :: ShaderManager() {
	mProgram = glCreateProgram();
	if (0 == mProgram) {
		Log::d("Failed create program\n");
		exit(1);
	}
}

ShaderManager* ShaderManager :: getInstance() {
	if (0 == sInstance) {
		sInstance = new ShaderManager();
	}

	return sInstance;
}

void ShaderManager :: useEffect(Effect *effect) {

	if (NULL == effect) {
		Log::d("effect is null \n");
		return;
	}

	if (effect->mVtxShader == 0 && effect->mFrgShader == 0) {
		Log::d("No valid shaders \n");
		return;
	}

	if (0 != effect->mVtxShader) {
		glDeleteShader(mCurVtxShader);	
		glAttachShader(mProgram, effect->mVtxShader);
	}

	if (0 != effect->mFrgShader) {
		glDeleteShader(mCurFrgShader);
		glAttachShader(mProgram, effect->mFrgShader);
	}

	glLinkProgram(mProgram);
	GLint linked;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &linked);
	if (!linked) {
		Log::d("Failed link shader program:\n");

		GLint log_cnt;
		glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &log_cnt);
		if (log_cnt <= 0) {
			Log::d("Invalid log length.\n");
		} else {
			char *buf = new char[log_cnt];
			GLsizei len;
			glGetProgramInfoLog(mProgram, log_cnt, &len, buf);
			Log::d("program info:%s\n", buf);
			delete []buf;
		}

		return;
	}

	GLint shdr_cnt;
	glGetProgramiv(mProgram, GL_ATTACHED_SHADERS, &shdr_cnt);
	Log::d("Attached %d shaders.\n", shdr_cnt);

    const GLubyte *version = glGetString(GL_VERSION);
    Log::d("version:%s\n", version);
    const GLubyte *vendor = glGetString(GL_VENDOR);
    Log::d("verdor:%s\n", vendor);
    const GLubyte *renderer = glGetString(GL_RENDERER);
    Log::d("renderer:%s\n", renderer);
    const GLubyte *slver = glGetString(GL_SHADING_LANGUAGE_VERSION);
    Log::d("shader version:%s\n", slver);

	effect->work();
	mCurVtxShader = effect->mVtxShader;
	mCurFrgShader = effect->mFrgShader;
}
