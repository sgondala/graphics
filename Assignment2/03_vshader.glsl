#version 400

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 color;
uniform mat4 uModelViewMatrix;

void main () 
{
  gl_Position = uModelViewMatrix * vPosition;
  color = vColor;
}
