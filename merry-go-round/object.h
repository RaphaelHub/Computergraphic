#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <stdio.h> // TODO : remove if unused
#include <string.h>
#include <GL/glew.h>


typedef struct GObject {
  
  GLfloat *vertex;
  GLfloat *color;
  GLushort *index;
  
} GObject;

GObject init(GLfloat[], GLfloat[], GLushort[]);

#endif