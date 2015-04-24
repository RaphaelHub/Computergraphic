/******************************************************************
*
* merry-go-around.c
*
* Description: 
*
* Authors: Raphael Gruber, Patrick Franz
* 
* Computer Graphics Proseminar SS 2015
* 
* Interactive Graphics and Simulation Group
* Institute of Computer Science
* University of Innsbruck
*
*******************************************************************/

/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* OpenGL includes */
#include <GL/glew.h>
#include <GL/freeglut.h>


/* Local includes */
#include "LoadShader.h"   /* Provides loading function for shader code */
#include "Matrix.h"  
#include "Octagon.h"
#include "Pyramid.h"
#include "mainBar.h"
#include "cube.h"

/*----------------------------------------------------------------*/

#define OBJECTS 7

/* Define handle to a vertex buffer object */
GLuint VBO[OBJECTS];

/* Define handle to a color buffer object */
GLuint CBO[OBJECTS]; 

/* Define handle to an index buffer object */
GLuint IBO[OBJECTS];


/* Indices to vertex attributes; in this case positon and color */ 
enum DataID {vPosition = 0, vColor = 1}; 

/* Strings for loading and storing shader code */
static const char* VertexShaderString;
static const char* FragmentShaderString;

GLuint ShaderProgram;

float ProjectionMatrix[16]; /* Perspective projection matrix */
float ViewMatrix[16]; /* Camera view matrix */ 
float ModelMatrix[OBJECTS][16]; /* Model matrix */ 

/* Transformation matrices for initial position */
float TranslateOrigin[16];
float TranslateDown[16];
float RotateX[16];
float RotateZ[16];
float InitialTransform[16];


GLfloat vertex_buffer_data1[sizeof(vertex_octagon)]; 
GLfloat vertex_buffer_data2[sizeof(vertex_pyramid)];  
GLfloat vertex_buffer_data3[sizeof(vertex_mainBar)]; 
GLfloat vertex_buffer_data4[sizeof(vertex_cube)];
GLfloat vertex_buffer_data5[sizeof(vertex_cube)];
GLfloat vertex_buffer_data6[sizeof(vertex_cube)];
GLfloat vertex_buffer_data7[sizeof(vertex_cube)];

GLfloat color_buffer_data1[sizeof(color_octagon)];
GLfloat color_buffer_data2[sizeof(color_pyramid)];
GLfloat color_buffer_data3[sizeof(color_mainBar)];
GLfloat color_buffer_data4[sizeof(color_cube)];
GLfloat color_buffer_data5[sizeof(color_cube)];
GLfloat color_buffer_data6[sizeof(color_cube)];
GLfloat color_buffer_data7[sizeof(color_cube)];

GLushort index_buffer_data1[sizeof(index_octagon)];
GLushort index_buffer_data2[sizeof(index_pyramid)];
GLushort index_buffer_data3[sizeof(index_mainBar)];
GLushort index_buffer_data4[sizeof(index_cube)];
GLushort index_buffer_data5[sizeof(index_cube)];
GLushort index_buffer_data6[sizeof(index_cube)];
GLushort index_buffer_data7[sizeof(index_cube)];


/*----------------------------------------------------------------*/

void transform(int i, float rot_offset, float rot_speed, float size,
    float height, float radius) {
    float angle = (glutGet(GLUT_ELAPSED_TIME) / 1000.0) * (180/M_PI);
    float RotationMatrixAnim[16];
    float ScaleMatrix[16];
    float InitialTransform[16];

    SetScaling(size, size, size, ScaleMatrix);

    SetRotationY(rot_speed*angle + rot_offset, RotationMatrixAnim);
    SetTranslation(radius, height, 0, InitialTransform);

    MultiplyMatrix(InitialTransform, ScaleMatrix, ModelMatrix[i]);
    MultiplyMatrix(RotationMatrixAnim, ModelMatrix[i], ModelMatrix[i]);
}

void DisplayOneObject(int i) {
    glEnableVertexAttribArray(vPosition);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(vColor);
    glBindBuffer(GL_ARRAY_BUFFER, CBO[i]);
    glVertexAttribPointer(vColor, 3, GL_FLOAT,GL_FALSE, 0, 0);   

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[i]);
    GLint size; 
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    /* Associate program with shader matrices */
    GLint projectionUniform = glGetUniformLocation(ShaderProgram, "ProjectionMatrix");
    if (projectionUniform == -1) 
    {
        fprintf(stderr, "Could not bind uniform ProjectionMatrix\n");
	exit(-1);
    }
    glUniformMatrix4fv(projectionUniform, 1, GL_TRUE, ProjectionMatrix);
    
    GLint ViewUniform = glGetUniformLocation(ShaderProgram, "ViewMatrix");
    if (ViewUniform == -1) 
    {
        fprintf(stderr, "Could not bind uniform ViewMatrix\n");
        exit(-1);
    }
    glUniformMatrix4fv(ViewUniform, 1, GL_TRUE, ViewMatrix);
   
    GLint RotationUniform = glGetUniformLocation(ShaderProgram, "ModelMatrix");
    if (RotationUniform == -1) 
    {
        fprintf(stderr, "Could not bind uniform ModelMatrix\n");
        exit(-1);
    }
    glUniformMatrix4fv(RotationUniform, 1, GL_TRUE, ModelMatrix[i]);  

    /* Issue draw command, using indexed triangle list */
    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

    /* Disable attributes */
    glDisableVertexAttribArray(vPosition);
    glDisableVertexAttribArray(vColor);   
	
}


/******************************************************************
*
* Display
*
* This function is called when the content of the window needs to be
* drawn/redrawn. It has been specified through 'glutDisplayFunc()';
* Enable vertex attributes, create binding between C program and 
* attribute name in shader
*
*******************************************************************/

void Display()
{
    	/* Clear window; color specified in 'Initialize()' */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	int i = 0;  
	for(;i < OBJECTS; i++) { 
		DisplayOneObject(i);
	}  
    /* Swap between front and back buffer */ 
    glutSwapBuffers();
}


/******************************************************************
*
* OnIdle
*
* 
*
*******************************************************************/

void OnIdle()
{
    //float angle = (glutGet(GLUT_ELAPSED_TIME) / 1000.0) * (180.0/M_PI); 
    //float RotationMatrixAnim[16];

    /* Time dependent rotation */
    //SetRotationY(angle, RotationMatrixAnim);

    /* Apply model rotation; finally move cube down */
    //int i = 0;
    //for(; i < OBJECTS; i++) {
	//	MultiplyMatrix(RotationMatrixAnim, InitialTransform, ModelMatrix[i]);
	//	MultiplyMatrix(TranslateDown, ModelMatrix[i], ModelMatrix[i]);
//}

    // transform karusell
    transform(0, 0.0, 0.3, 1.0, -2.5, 0.0);
    transform(1, 0.0, 0.3, 1.0, -2.5, 0.0);
    transform(2, 0.0, 0.3, 1.0, -2.5, 0.0);

    // transform cube
    transform(3,   0.0, 0.3, 0.5, -1.0, 2.0);
    transform(4,  90.0, 0.3, 0.5, -1.0, 2.0);
    transform(5, 180.0, 0.3, 0.5, -1.0, 2.0);
    transform(6, 270.0, 0.3, 0.5, -1.0, 2.0);

    /* Request redrawing forof window content */  
    glutPostRedisplay();
}


/******************************************************************
*
* SetupDataBuffers
*
* Create buffer objects and load data into buffers
*
*******************************************************************/

void SetupDataBuffers()
{
    // ground plane
    glGenBuffers(1, &VBO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data1), vertex_buffer_data1, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data1), index_buffer_data1, GL_STATIC_DRAW);

    glGenBuffers(1, &CBO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, CBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data1), color_buffer_data1, GL_STATIC_DRAW);
    
    // stange
    glGenBuffers(1, &VBO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data2), index_buffer_data2, GL_STATIC_DRAW);

    glGenBuffers(1, &CBO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, CBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);
        
    // kopf
    glGenBuffers(1, &VBO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO[2]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data3), index_buffer_data3, GL_STATIC_DRAW);

    glGenBuffers(1, &CBO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, CBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);
   
    // cube 1
    glGenBuffers(1, &VBO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4), vertex_buffer_data4, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data4), index_buffer_data4, GL_STATIC_DRAW);

    glGenBuffers(1, &CBO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, CBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);

    // cube 2
    glGenBuffers(1, &VBO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data5), vertex_buffer_data5, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO[4]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[4]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data5), index_buffer_data5, GL_STATIC_DRAW);

    glGenBuffers(1, &CBO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, CBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data5), color_buffer_data5, GL_STATIC_DRAW);

    // cube 3
    glGenBuffers(1, &VBO[5]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data6), vertex_buffer_data6, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO[5]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[5]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data6), index_buffer_data6, GL_STATIC_DRAW);

    glGenBuffers(1, &CBO[5]);
    glBindBuffer(GL_ARRAY_BUFFER, CBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data6), color_buffer_data6, GL_STATIC_DRAW);

    // cube 4
    glGenBuffers(1, &VBO[6]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data7), vertex_buffer_data7, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO[6]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[6]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data7), index_buffer_data7, GL_STATIC_DRAW);

    glGenBuffers(1, &CBO[6]);
    glBindBuffer(GL_ARRAY_BUFFER, CBO[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data7), color_buffer_data7, GL_STATIC_DRAW);

}


/******************************************************************
*
* AddShader
*
* This function creates and adds individual shaders
*
*******************************************************************/

void AddShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
    /* Create shader object */
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) 
    {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    /* Associate shader source code string with shader object */
    glShaderSource(ShaderObj, 1, &ShaderCode, NULL);

    GLint success = 0;
    GLchar InfoLog[1024];

    /* Compile shader source code */
    glCompileShader(ShaderObj);
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) 
    {
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    /* Associate shader with shader program */
    glAttachShader(ShaderProgram, ShaderObj);
}


/******************************************************************
*
* CreateShaderProgram
*
* This function creates the shader program; vertex and fragment
* shaders are loaded and linked into program; final shader program
* is put into the rendering pipeline 
*
*******************************************************************/

void CreateShaderProgram()
{
    /* Allocate shader object */
    ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) 
    {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    /* Load shader code from file */
    VertexShaderString = LoadShader("vertexshader.vs");
    FragmentShaderString = LoadShader("fragmentshader.fs");

    /* Separately add vertex and fragment shader to program */
    AddShader(ShaderProgram, VertexShaderString, GL_VERTEX_SHADER);
    AddShader(ShaderProgram, FragmentShaderString, GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024];

    /* Link shader code into executable shader program */
    glLinkProgram(ShaderProgram);

    /* Check results of linking step */
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

    if (Success == 0) 
    {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    /* Check if shader program can be executed */ 
    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);

    if (!Success) 
    {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    /* Put linked shader program into drawing pipeline */
    glUseProgram(ShaderProgram);
}


/******************************************************************
*
* Initialize
*
* This function is called to initialize rendering elements, setup
* vertex buffer objects, and to setup the vertex and fragment shader
*
*******************************************************************/

void Initialize(void)
{   
    /* Set background (clear) color to dark blue */ 
    glClearColor(0.0, 0.0, 0.4, 0.0);

    /* Enable depth testing */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);    
    
    /* Transform matrix for the bar in the middle*/
    
    /*copy objects into buffer*/
    memcpy(vertex_buffer_data1, vertex_octagon, sizeof(vertex_octagon));
    memcpy(vertex_buffer_data2, vertex_pyramid, sizeof(vertex_pyramid));
    memcpy(vertex_buffer_data3, vertex_mainBar, sizeof(vertex_mainBar));
    memcpy(vertex_buffer_data4, vertex_cube, sizeof(vertex_cube));    
    memcpy(vertex_buffer_data5, vertex_cube, sizeof(vertex_cube));
    memcpy(vertex_buffer_data6, vertex_cube, sizeof(vertex_cube));
    memcpy(vertex_buffer_data7, vertex_cube, sizeof(vertex_cube));

    memcpy(color_buffer_data1, color_octagon, sizeof(color_octagon));
    memcpy(color_buffer_data2, color_pyramid, sizeof(color_pyramid));
    memcpy(color_buffer_data3, color_mainBar, sizeof(color_mainBar));
    memcpy(color_buffer_data4, color_cube, sizeof(color_cube));    
    memcpy(color_buffer_data5, color_cube, sizeof(color_cube));
    memcpy(color_buffer_data6, color_cube, sizeof(color_cube));
    memcpy(color_buffer_data7, color_cube, sizeof(color_cube));

    memcpy(index_buffer_data1, index_octagon, sizeof(index_octagon));
    memcpy(index_buffer_data2, index_pyramid, sizeof(index_pyramid));
    memcpy(index_buffer_data3, index_mainBar, sizeof(index_mainBar));
    memcpy(index_buffer_data4, index_cube, sizeof(index_cube));
    memcpy(index_buffer_data5, index_cube, sizeof(index_cube));
    memcpy(index_buffer_data6, index_cube, sizeof(index_cube));
    memcpy(index_buffer_data7, index_cube, sizeof(index_cube));

    /* Setup vertex, color, and index buffer objects */
    SetupDataBuffers();

    /* Setup shaders and shader program */
    CreateShaderProgram();  

    /* Initialize matrices */
    SetIdentityMatrix(ProjectionMatrix);
    SetIdentityMatrix(ViewMatrix);
    int i = 0;
    for(;i<OBJECTS;i++) {
		SetIdentityMatrix(ModelMatrix[i]);
	}

    /* Set projection transform */
    float fovy = 45.0;
    float aspect = 1.0; 
    float nearPlane = 1.0; 
    float farPlane = 50.0;
    SetPerspectiveMatrix(fovy, aspect, nearPlane, farPlane, ProjectionMatrix);

    /* Set viewing transform */
    float camera_disp = -10.0;
    SetTranslation(0.0, 0.0, camera_disp, ViewMatrix);

    /* Translate and rotate cube onto tip */
    SetTranslation(0, 0, 0, TranslateOrigin);
    SetRotationX(0.0, RotateX);
    SetRotationZ(0.0, RotateZ);	

    /* Translate down */	
    SetTranslation(0, -sqrtf(sqrtf(2.0) * 1.0), 0, TranslateDown);

    /* Initial transformation matrix */
    MultiplyMatrix(RotateX, TranslateOrigin, InitialTransform);
    MultiplyMatrix(RotateZ, InitialTransform, InitialTransform);
}



/******************************************************************
*
* main
*
* Main function to setup GLUT, GLEW, and enter rendering loop
*
*******************************************************************/

int main(int argc, char** argv)
{
    /* Initialize GLUT; set double buffered window and RGBA color model */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("CG Proseminar - merry-go-round");

    /* Initialize GL extension wrangler */
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    /* Setup scene and rendering parameters */
    Initialize();


    /* Specify callback functions;enter GLUT event processing loop, 
     * handing control over to GLUT */
    glutIdleFunc(OnIdle);
    glutDisplayFunc(Display);
    glutMainLoop();

    /* ISO C requires main to return int */
    return 0;
}
