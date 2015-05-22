#include "object.h"

GObject init(GLfloat v[], GLfloat c[], GLushort i[]) {
  GObject new;
  
  GLfloat vertex[sizeof(v)];
  GLfloat color[sizeof(c)];
  GLushort index[sizeof(i)];
  
  memcpy(vertex, v, sizeof(v));
  memcpy(color, c, sizeof(c));
  memcpy(index, i, sizeof(i));
  
  new.vertex = v;
  new.color = c;
  new.index = i;
  
  return new;
};