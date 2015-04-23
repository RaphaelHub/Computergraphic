#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <stdio.h>
#include <string.h>

int openFile(char *path) {
    FILE *file = fopen(path, "r"); // opens the file with read rights
    if(file == NULL) {
        fprintf(stderr, "error while opening file: %s\n", path);
        return 0;
    }

    GLfloat *vertex_buffer;
    GLfloat *color_buffer;
    GLushort *index_buffer;
    
    
    
    while(1) {
        char lineH[256];
        // read the first word (word length should never exceed 256 char
        int res = fscanf(file, "/s", lineH);
        if(res == EOF) break; // stop if we hit End Of File
        
        if(strcmp(lineH, "v") {
            float x,y,z;
            fscanf(file, "%f %f %f\n", &x, &y, &z);
        }
    }

    fclose(file); // close the file
}

void extendBuffer(GLfloat *vb) {
    
}

#endif
