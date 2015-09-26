#version 400

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 color;
uniform mat4 uModelViewMatrix;
uniform mat4 orthoMatrix;
uniform float caseNo;
uniform mat4 dcsMatrix;
void main () 
{
	if(caseNo == 5){
		vec4 tempVec = uModelViewMatrix * vPosition;
		tempVec.x /= tempVec.w;
		tempVec.y /= tempVec.w;
		tempVec.z /= tempVec.w;
		tempVec.w /= tempVec.w;
		gl_Position = orthoMatrix * dcsMatrix * tempVec;
	}
	else if(caseNo==4){
		vec4 tempVec = uModelViewMatrix * vPosition;
		tempVec.x /= tempVec.w;
		tempVec.y /= tempVec.w;
		tempVec.z /= tempVec.w;
		tempVec.w /= tempVec.w;
		gl_Position = orthoMatrix * tempVec; 	 
	}
	else{
		gl_Position = orthoMatrix * uModelViewMatrix * vPosition;
	}
	color = vColor;
}
