#ifndef __PYRAMID_H__
#define __PYRAMID_H__

GLfloat vertex_pyramid[] = {
   -1.5, 4.0, -1.5,
1.5, 4.0, -1.5,
-1.5, 4.0, 1.5,
1.5, 4.0, 1.5,
0.0, 5.0, 0.0,
};   

GLfloat color_pyramid[] = { 
	1.0, 0.0, 0.0,
1.0, 0.0, 0.0,
1.0, 0.0, 0.0,
1.0, 0.0, 0.0,
0.0, 1.0, 0.0,
};
  
  
GLushort index_pyramid[] = {
 16, 17, 18,
18, 19, 17,
16, 17, 20,
17, 19, 20,
18, 19, 20,
18, 20, 16,
};

#endif
