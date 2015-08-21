#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;

// Modelling/Viewing mode - 0 for modelling, 1 for viewing
int mode = 0;

//Debugging thing
int intTemp = 0;

//Vertices
std::vector<glm::vec4> vertices;
std::vector<glm::vec4> colors;
// std::vector<glm::vec4> a;
//-------------------------------------------------------------------------

#endif
