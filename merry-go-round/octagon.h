#ifndef __OCTAGON_H__
#define __OCTAGON_H__

GLfloat vertex_octagon[] = {
    /*first octagon*/
    -2.0,  0.5,  2.0,
     0.0,  0.5,  3.0,
     2.0,  0.5,  2.0,
     3.0,  0.5,  0.0,
     2.0,  0.5, -2.0,
     0.0,  0.5, -3.0,
    -2.0,  0.5, -2.0,
    -3.0,  0.5,  0.0,
    
	/*second octagon*/
    -2.0, 1.0,  2.0,
     0.0,  1.0,  3.0,
     2.0,  1.0,  2.0,
     3.0,  1.0,  0.0,
     2.0,  1.0, -2.0,
     0.0,  1.0, -3.0,
    -2.0,  1.0, -2.0,
    -3.0,  1.0,  0.0,
};   

GLfloat color_octagon[] = { 
	/*first octagon*/
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    
    /*second octagon*/
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
};
  
  
GLushort index_octagon[] = {
  /*first octagon*/
    0, 1, 2,
    2, 3, 4,
    4, 5, 6,
    6, 7, 0,
    0,6,2,
    4,6,2,
    
    /*second octagon*/
    8, 9, 10,
    10, 11, 12,
    12, 13, 14,
    14, 15, 8,
    8,14,10,
    12,14,10,
    
/*triangels between first and second*/
0,1,8,
1,2,9,
2,3,10,
3,4,11,
4,5,12,
5,6,13,
6,7,14,
7,0,15,
/*triangels between second and first*/
8,9,1,
9,10,2,
10,11,3,
11,12,4,
12,13,5,
13,14,6,
14,15,7,
15,8,0,
};

#endif