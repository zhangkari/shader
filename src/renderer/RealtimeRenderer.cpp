/*******************************************
 * file name:	RealtimeRenderer.c
 * description:	implement real time renderer
 * author:		kari.zhang
 * date:		2016-4-29
 ******************************************/
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include "Bitmap.h"
#include "ShaderManager.h"
#include "RealtimeRenderer.h"
#include "System.h"

#ifndef WIN_WIDTH
#define WIN_WIDTH 600
#endif

#ifndef WIN_HEIGHT
#define WIN_HEIGHT 600
#endif

#include <stdlib.h>

RealtimeRenderer :: ~RealtimeRenderer() {

}

static float rand(float min, float max) {
    srand(System::moment());
    float val = rand();
    float ret = max - (RAND_MAX - val) * (max - min) / RAND_MAX;
    return ret;
}

#define RND_POS (rand(-1.0, 1.0))
#define RND_CLR (rand(0.0, 1.0))

void RealtimeRenderer::draw(int numInstance) {
    if (mArtwork == NULL) {
        return;
    }

    const GLfloat vertex[] = {
        RND_POS, RND_POS, 0.0,
        RND_POS, RND_POS, 0.0,
        RND_POS, RND_POS, 0.0
    };

    const GLfloat color[] = {
        RND_CLR, RND_CLR, RND_CLR, 1.0,
        RND_CLR, RND_CLR, RND_CLR, 1.0,
        RND_CLR, RND_CLR, RND_CLR, 1.0
    };

    GLuint vbo[2];
    glGenBuffers(2, vbo);
    GLuint vertexVbo = vbo[0];
    GLuint colorVbo = vbo[1];

    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint program = ShaderManager::getInstance()->getProgram();
    GLint aVert = glGetAttribLocation(program, "aVert");
    GLint aColor = glGetAttribLocation(program, "aColor");

    glEnableVertexAttribArray(aVert);
    glEnableVertexAttribArray(aColor);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glVertexAttribPointer(aVert , 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glVertexAttribPointer(aColor , 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glutSwapBuffers();
}
