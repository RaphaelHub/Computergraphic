#ifndef _GOBJECT_H_
#define _GOBJECT_H_

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include "Matrix.h"

typedef struct {
    GLuint VBO;
    GLuint CBO;
    GLuint IBO;
    GLfloat *vbd;
    GLfloat *cbd;
    GLushort *ibd;
} GObj;

void _setupDataBuffers(GObj,GLfloat*,GLfloat*,GLushort*);
void _display(GObj*,int,int,float*,float*,float*,GLuint*);
#endif
