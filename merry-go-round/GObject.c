#include "GObject.h"

#include <string.h>

float color_arr[9][4] = {
    {1.0, 0.0, 0.0, 1.0},   //red
    {0.0, 1.0, 0.0, 1.0},   //green
    {0.0, 0.0, 1.0, 1.0},   //blu
    {1.0, 1.0, 0.0, 1.0},   //yellow
    {0.0, 1.0, 1.0, 1.0},   //cyan
    {1.0, 0.0, 1.0, 1.0},   //magenta
    {0.0, 0.6, 1.0, 1.0},   //light blue
    {0.0, 0.0, 0.0, 1.0},   //black
    {1.0, 0.5, 0.0, 1.0}    //orange
};


/**
 * Setup all buffers for the grafical object
 *
 * @param self  the grafical object, which should be initialized
 * @param vb    the vertex buffer array used by the grafical object
 * @param cb    the color buffer array used by the grafical object
 * @param ib    the index buffer array used by the grafical object
 */
void _setupDataBuffers(GObj self, GLfloat *vb, GLfloat *cb, GLushort *ib) {
    printf("test\n");

    //memcpy(self.vbd, vb, sizeof(*vb));
    self.vbd = vb;
    //memcpy(self.cbd, cb, sizeof(*cb));
    self.cbd = cb;
    //memcpy(self.ibd, ib, sizeof(*ib));
    self.ibd = ib;

    glGenBuffers(1, &(self.VBO));
    glBindBuffer(GL_ARRAY_BUFFER, self.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(self.vbd), self.vbd,
        GL_STATIC_DRAW);
    
    glGenBuffers(1, &(self.IBO));
    glBindBuffer(GL_ARRAY_BUFFER, self.IBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(self.ibd), self.ibd,
        GL_STATIC_DRAW);

    glGenBuffers(1, &(self.CBO));
    glBindBuffer(GL_ARRAY_BUFFER, self.CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(self.cbd), self.cbd,
        GL_STATIC_DRAW);
}

void _display(GObj *self, int vPosition, int vColor, float *ProjectionMatrix,
    float *ViewMatrix, float *ModelMatrix, GLuint *ShaderProgram) {
    glEnableVertexAttribArray(vPosition);
    glBindBuffer(GL_ARRAY_BUFFER, self->VBO);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(vColor);
    glBindBuffer(GL_ARRAY_BUFFER, self->CBO);
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->IBO);
    GLint size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    GLint pUniform = glGetUniformLocation(*ShaderProgram, "ProjectionMatrix");
    if(pUniform == -1) {
        fprintf(stderr, "Couldn't bind to ProjectionMatrix\n");
        exit(-1);
    }
    glUniformMatrix4fv(pUniform, 1, GL_TRUE, ProjectionMatrix);

    GLint vUniform = glGetUniformLocation(*ShaderProgram, "ViewMatrix");
    if(vUniform == -1) {
        fprintf(stderr, "Couldn't bind to ViewMatrix\n");
        exit(-1);
    }
    glUniformMatrix4fv(vUniform, 1, GL_TRUE, ViewMatrix);

    GLint rUniform = glGetUniformLocation(*ShaderProgram, "ModelMatrix");
    if(rUniform == -1){
        fprintf(stderr, "Couldn't bind to ModelMatrix\n");
        exit(-1);
    }
    glUniformMatrix4fv(rUniform, 1, GL_TRUE, ModelMatrix);

    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(vPosition);
    glDisableVertexAttribArray(vColor);
}
