#version 330

in vec3 normal;
in vec3 eye;
in vec4 COLOR;

uniform mat4 viewMatrix;
uniform int Light1;
uniform int Light2;
out vec4 frag_color;

void main () 
{
  // Defining Materials
  vec4 diffuse = vec4(0.5, 0.0, 0.0, 1.0); 
  vec4 ambient = vec4(0.1, 0.0, 0.0, 1.0);
  vec4 specular = vec4(1.0, 0.5, 0.5, 1.0);
  float shininess = 0.2;
  vec4 spec1 = vec4(0.0);
  vec4 spec2 = vec4(0.0); 

  // Defining Light 1
  vec4 lightPos1 = vec4(0.0, 0.0, 10.0, 0.0);
  vec3 lightDir1 = vec3(viewMatrix * lightPos1);  // Transforms with camera
  lightDir1 = normalize(lightDir1);

  //Diffuse
  float dotProduct1 = dot(normal, lightDir1);
  float intensity1 =  max( dotProduct1, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity1 > 0.0)
  {
	vec3 h1 = normalize(lightDir1 + eye);
   	float intSpec1 = max(dot(h1,normal), 0.0);	
        spec1 = specular * pow(intSpec1, shininess);
  }  

  // Defining Light 2
  vec4 lightPos2 = vec4(-10.0, 0.0, 0.0, 0.0);
  vec3 lightDir2 = vec3(viewMatrix * lightPos2);  // Transforms with camera
  lightDir2 = normalize(lightDir2);

  //Diffuse
  float dotProduct2 = dot(normal, lightDir2);
  float intensity2 =  max( dotProduct2, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity2 > 0.0)
  {
	vec3 h2 = normalize(lightDir2 + eye);
   	float intSpec2 = max(dot(h2,normal), 0.0);	
        spec2 = specular * pow(intSpec2, shininess);
  } 
  vec4 color;
  if(Light1 == 1 && Light2 == 1){
  	color = max((intensity2 * diffuse  + spec2 + intensity1*diffuse + spec1 )*COLOR, ambient); // All
  }
  else if(Light1 == 1){
  	color = max((intensity1*diffuse + spec1 )*COLOR, ambient); // All
  }
  else if(Light2 == 1){
  	color = max((intensity1*diffuse + spec1 )*COLOR, ambient); // All
  }
  else{
  	color = ambient;
  }
  frag_color = color;

}
