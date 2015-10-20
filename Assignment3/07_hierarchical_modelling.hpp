/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 2.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;
//Shader program attribs
GLuint vPosition,vColor,vNormal;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;
int objectSelected, podno = -1, podarmno = 1, podselected = 0;
int light1 = 0,light2 = 0;
csX75::HNode* root_node;
csX75::HNode* curr_node;
//c3po------------------------------------------//
csX75::HNode* chest;
csX75::HNode* head;
csX75::HNode* rightUpperArm;
csX75::HNode* rightLowerArm;
csX75::HNode* leftUpperArm;
csX75::HNode* leftLowerArm;
csX75::HNode* rightUpperLeg;
csX75::HNode* rightLowerLeg;
csX75::HNode* leftUpperLeg;
csX75::HNode* leftLowerLeg;
//c3po------------------------------------------//

//vulture droid---------------------------------//
csX75::HNode* vbody;
csX75::HNode* vneck;
csX75::HNode* vhead;
csX75::HNode* vpod1arm;
csX75::HNode* vpod1;
csX75::HNode* vpod2arm;
csX75::HNode* vpod2;
csX75::HNode* vpod3arm;
csX75::HNode* vpod3;
csX75::HNode* vpod4arm;
csX75::HNode* vpod4;
//-------------------------------------------------------------------------
csX75::plane* ground;

#endif
