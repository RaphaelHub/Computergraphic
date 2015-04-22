#ifndef __OCTAGON_H__
#define __OCTAGON_H__

GLfloat vertex_octagon[] = {
       -2.0,  0.5,  2.0,
     0.0,  0.5,  3.0,
     2.0,  0.5,  2.0,
     3.0,  0.5,  0.0,
     2.0,  0.5, -2.0,
     0.0,  0.5, -3.0,
    -2.0,  0.5, -2.0,
    -3.0,  0.5,  0.0,
};   
  
  
GLushort index_octagon[] = {
   0, 1, 2,
    2, 3, 4,
    4, 5, 6,
    6, 7, 0,
    0,6,2,
    4,6,2,
};

#endif
