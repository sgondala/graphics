/*
  A program which opens a window and draws the "color cube."

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by Parag Chaudhuri, 2015
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

//Include Files
#include "glm/mat4x4.hpp"
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

#define pb push_back 


int mode = 0; //1 for inspection mode
glm::vec4 vertices[200];
glm::vec4 colors[200];

glm::vec4 vertexGroups[4][200];
glm::vec4 colorGroups[4][200];
int vertexCount[] = {0,0,0,0};

int vertexNo = 0;

float frustumL, frustumR, frustumT, frustumB, frustumN, frustumF;
glm::vec3 eye, lookAt, up;

GLfloat xTrans = 0.0, yTrans = 0.0, zTrans = 0.0;
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;
int terminalInput = 1;
int rotationCase = 0;
bool choosenVCS = false;
bool choosenCCS = false;
bool choosenNDCS = false;
#endif
