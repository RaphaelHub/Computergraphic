#ifndef __CUBE_H__
#define __CUBE_H__

// vertex buffer for the cube
GLfloat vertex_cube[] = {
    -0.5, -0.5, -0.5,
     0.5, -0.5, -0.5,
     0.5,  0.5, -0.5,
    -0.5,  0.5, -0.5,
    -0.5, -0.5,  0.5,
     0.5, -0.5,  0.5,
     0.5,  0.5,  0.5,
    -0.5,  0.5,  0.5
};

// cube color buffer
GLfloat color_cube[] = {
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5
};

GLushort index_cube[] = {
    // ground face
    0,1,2,
    0,3,2,
    // back face
    0,1,5,
    0,4,5,
    // left face
    0,3,7,
    0,4,7,
    // front face
    6,2,3,
    6,7,3,
    // right face
    6,2,1,
    6,5,1,
    // top face
    6,5,4,
    6,7,4
};

#endif
