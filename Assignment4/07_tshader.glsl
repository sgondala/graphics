#version 330

in vec3 normal1;
in vec3 eye1;
in vec4 COLOR1;
in vec4 pos1;
in vec2 tex;

out vec3 normal;
out vec3 eye;
out vec4 pos;
out vec4 COLOR;
out vec4 texCOLOR;

uniform sampler2D texture;

void main (void) 
{
	texCOLOR = texture2D(texture, tex);
	normal = normal1;
	eye = eye1;
	COLOR = COLOR1;
	pos1 = pos;
 }
