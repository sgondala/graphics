#version 330

in vec4 vPosition;
in vec4 vColor;
in vec4 vNormal;

out vec3 normal;
out vec3 eye;
out vec4 COLOR;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;
void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = normalize(normalMatrix * normalize(vec3(vNormal))); 
  eye = normalize(vec3(-gl_Position)); 
  COLOR = vColor; 
 }
