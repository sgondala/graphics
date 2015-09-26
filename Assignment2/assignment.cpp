#include "assignment.hpp"

GLuint shaderProgram;
GLuint vao[4];
GLuint verticesVbo[4], colorsVbo[4];

GLuint uModelViewMatrix;

glm::mat4 translationMatrix, rotationMatrix;
glm::mat4 modelviewMatrix,orthoMatrix;
glm::vec3 frustumxyz[9];

void initBuffersGL(){
	// testing();
	std::string vertex_shader_file("03_vshader.glsl");
	std::string fragment_shader_file("03_fshader.glsl");

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	shaderProgram = csX75::CreateProgramGL(shaderList);
	glUseProgram( shaderProgram );
}

std::vector<double> tokenizer(std::string line, char token){
	std::vector<double> inputFromFile;
	while(line.find(token)!=std::string::npos){
		int temp  = line.find(token);
		std::string value = line.substr(0, temp);
		inputFromFile.push_back(atof(value.c_str()));
		line = line.substr(temp+1);
	}
	inputFromFile.pb(atof(line.c_str()));
	return inputFromFile;
}

void frustumLine(int a, int b,int color){
	vertexGroups[3][vertexCount[3]] = glm::vec4(frustumxyz[a].x,frustumxyz[a].y,frustumxyz[a].z,1);
	if(color == 1){
		colorGroups[3][vertexCount[3]] = glm::vec4(1,0,1,1);
	}
	else{
		colorGroups[3][vertexCount[3]] = glm::vec4(0,1,1,1);
	}
	vertexCount[3]++;
	vertexGroups[3][vertexCount[3]] = glm::vec4(frustumxyz[b].x,frustumxyz[b].y,frustumxyz[b].z,1);
	if(color == 1){
		colorGroups[3][vertexCount[3]] = glm::vec4(1,0,1,1);
	}
	else{
		colorGroups[3][vertexCount[3]] = glm::vec4(0,1,1,1);
	}
	vertexCount[3]++;
}


void frustumGenerator(){
	glm::vec3 frustumabc[8];
	std::cout << frustumL << " " << frustumR << " " << frustumT << " " << frustumB << " " << frustumN << " " << frustumF << std::endl;
	frustumabc[0] = glm::vec3(frustumR,-frustumB,frustumN);
	frustumabc[1] = glm::vec3(-frustumL,-frustumB,frustumN);
	frustumabc[2] = glm::vec3(-frustumL,frustumT,frustumN);
	frustumabc[3] = glm::vec3(frustumR,frustumT,frustumN);
	double factor = frustumF/frustumN;
	frustumabc[4] = glm::vec3(frustumR*factor,-frustumB*factor,frustumF);
	frustumabc[5] = glm::vec3(-frustumL*factor,-frustumB*factor,frustumF);
	frustumabc[6] = glm::vec3(-frustumL*factor,frustumT*factor,frustumF);
	frustumabc[7] = glm::vec3(frustumR*factor,frustumT*factor,frustumF);
	std::cout << "eye" << eye.x << " " << eye.y << " " << eye.z << std::endl;
	std::cout << "lookAt" << lookAt.x << " " << lookAt.y << " " << lookAt.z << std::endl;
	std::cout << "up" << up.x << " " << up.y << " " << up.z << std::endl;
	glm::vec3 n = -(lookAt-eye)/glm::distance(lookAt,eye);
	glm::vec3 u = glm::cross(up,n)/glm::distance(glm::cross(up,n),glm::vec3(0,0,0));
	glm::vec3 v = glm::cross(n,u);
	glm::mat3 transMatrix;
	std::cout << n.x << " " << n.y << " " << n.z << std::endl;
	std::cout << u.x << " " << u.y << " " << u.z << std::endl;
	std::cout << v.x << " " << v.y << " " << v.z << std::endl;	
	
	transMatrix[0] = u;
	transMatrix[1] = v;
	transMatrix[2] = n;
	std::cout << "transmatrix" << std::endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			std::cout << transMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	for(int i=0;i<8;i++){
		frustumxyz[i]= transMatrix*frustumabc[i]+eye;

		 std::cout << "xyz: " << frustumabc[i].x << " " << frustumabc[i].y << " " << frustumabc[i].z << std::endl; 
		 std::cout << "abc: " << frustumxyz[i].x << " " << frustumxyz[i].y << " " << frustumxyz[i].z << std::endl << std::endl; 
	}
	frustumxyz[8] = eye;
	frustumLine(0,1,0);
	frustumLine(1,2,0);
	frustumLine(2,3,0);
	frustumLine(3,0,0);
	frustumLine(0,4,0);
	frustumLine(1,5,0);
	frustumLine(2,6,0);
	frustumLine(3,7,0);
	frustumLine(4,5,0);
	frustumLine(5,6,0);
	frustumLine(6,7,0);
	frustumLine(7,4,0);

	frustumLine(0,8,1);
	frustumLine(1,8,1);
	frustumLine(2,8,1);
	frustumLine(3,8,1);
}

void loadRawImage(std::string fileName, int indexInArray, glm::vec3 scale, 
	glm::vec3 rot, glm::vec3 trans){
	std::ifstream myFile(fileName.c_str());
	std::string line;
	glm::vec3 bodyCenter(0.0,0.0,0.0);
	if(myFile.is_open()){
		while (getline(myFile,line)){
			std::vector<double> inputFromFile = tokenizer(line,' ');

			bodyCenter.x += inputFromFile[0];
			bodyCenter.y += inputFromFile[1];
			bodyCenter.z += inputFromFile[2];
			vertexGroups[indexInArray][vertexCount[indexInArray]] = 
				glm::vec4(inputFromFile[0],inputFromFile[1],inputFromFile[2],1);
			colorGroups[indexInArray][vertexCount[indexInArray]] = 
				glm::vec4(inputFromFile[3],inputFromFile[4],inputFromFile[5],1);
				if(indexInArray==2){
					//std::cout<<inputFromFile[5];
					// std::cout<< colorGroups[indexInArray][vertexCount[indexInArray]].x << " " <<
					// colorGroups[indexInArray][vertexCount[indexInArray]].y << " " <<
					// colorGroups[indexInArray][vertexCount[indexInArray]].z << std::endl;
				}
				vertexCount[indexInArray]++;
		}
		myFile.close();
	}
	bodyCenter.x /= vertexCount[indexInArray];
	bodyCenter.y /= vertexCount[indexInArray];
	bodyCenter.z /= vertexCount[indexInArray];

	glm::mat4 transBodyCenter, transBodyCenterNeg, transMatTemp, rotMatTemp, scaleMatRot, finalMat;

	transBodyCenter = glm::translate(glm::mat4(1.0f), glm::vec3(-bodyCenter.x, -bodyCenter.y, -bodyCenter.z));
	transBodyCenterNeg = glm::translate(glm::mat4(1.0f), glm::vec3(bodyCenter.x, bodyCenter.y, bodyCenter.z));
	transMatTemp = glm::translate(glm::mat4(1.0f), trans);
	// GLfloat tempXRot = (rot.x)*(3.14)/(180);
	std::cout << rot.x << " " << rot.y << " " << rot.z << std::endl;
	rotMatTemp = glm::rotate(glm::mat4(1.0f), (GLfloat) ((rot.x)*(3.14)/(180)), glm::vec3(1.0f,0.0f,0.0f));
	rotMatTemp = glm::rotate(rotationMatrix, (GLfloat) ((rot.y)*(3.14)/(180)), glm::vec3(0.0f,1.0f,0.0f));
	rotMatTemp = glm::rotate(rotationMatrix, (GLfloat) ((rot.z)*(3.14)/(180)), glm::vec3(0.0f,0.0f,1.0f));
	scaleMatRot = glm::scale(glm::mat4(1.0f), scale);

	finalMat = transMatTemp*transBodyCenterNeg*rotMatTemp*scaleMatRot*transBodyCenter;

	for(int i=0; i<vertexCount[indexInArray]; i++){
		vertexGroups[indexInArray][i] = finalMat*vertexGroups[indexInArray][i];
	}

}

void equate(glm::vec3 &a, std::vector<double> v){
	a.x = v[0];
	a.y = v[1];
	a.z = v[2];
}

//TODO
void loadScene(){
	std::string fileName;
	std::string line;
	std::ifstream myFile("myscene.scn");
	int lineNo = 1;
	glm::vec3 scale, trans, rot;
	if(myFile.is_open()){
		while (getline(myFile,line)){
			if(lineNo==1 || lineNo==5 || lineNo==9){
				fileName = line;
			}
			if(lineNo==2 || lineNo==6 || lineNo==10){
				std::vector<double> vec = tokenizer(line, ' ');
				equate(scale,vec);
			}
			if(lineNo==3 || lineNo==7 || lineNo==11){
				std::vector<double> vec = tokenizer(line, ' ');
				equate(rot,vec);
			}
			if(lineNo==4 || lineNo==8 || lineNo==12){
				std::vector<double> vec = tokenizer(line, ' ');
				equate(trans,vec);	
				loadRawImage(fileName,lineNo/4-1,scale,rot,trans);
			}
			if(lineNo==13){
				std::vector<double> vec = tokenizer(line, ' ');
				std::cout<<" Printing mine " << line << " " << vec[0]<<" "<<vec[1]<<" " <<vec[2]<<std::endl;
				equate(eye,vec);
			}
			if(lineNo==14){
				std::vector<double> vec = tokenizer(line, ' ');
				std::cout<<" Printing mine 2" << line << " " << vec[0]<<" "<<vec[1]<<" " <<vec[2]<<std::endl;
				equate(lookAt,vec);
			}
			if(lineNo==15){
				std::vector<double> vec = tokenizer(line, ' ');
				// std::cout<<" Printing mine 3" << line << " " << vec[0]<<" "<<vec[1]<<" " <<vec[2]<<std::endl;
				equate(up,vec);	
				std::cout<<" Printing mine 33 " << up[0]<<" "<<up[1]<<" " <<up[2]<<std::endl;

			}
			if(lineNo==16){
				std::vector<double> vec = tokenizer(line, ',');	
				frustumL = vec[0];
				frustumR = vec[1];
				frustumT = vec[2];
				frustumB = vec[3];
			}
			if(lineNo==17){
				std::vector<double> vec = tokenizer(line, ',');	
				frustumN = vec[0];
				frustumF = vec[1];
			}
			lineNo++;
		}
		myFile.close();
	}
	frustumGenerator();

}

void renderHelper(int i){

	glGenBuffers (1, &verticesVbo[i]);
	glBindBuffer (GL_ARRAY_BUFFER, verticesVbo[i]);
	glBufferData (GL_ARRAY_BUFFER, sizeof(vertexGroups[i][0]) * vertexCount[i], vertexGroups[i], GL_STATIC_DRAW);
	glGenBuffers (1, &colorsVbo[i]);
	glBindBuffer (GL_ARRAY_BUFFER, colorsVbo[i]);
	glBufferData (GL_ARRAY_BUFFER, sizeof(colorGroups[i][0]) * vertexCount[i], colorGroups[i], GL_STATIC_DRAW);
	glGenVertexArrays (1, &vao[i]);
	glBindVertexArray (vao[i]);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVbo[i]);
	glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVbo[i]);
	glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray (0);
	glEnableVertexAttribArray (1);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(i!=3) glDrawArrays(GL_TRIANGLES, 0, vertexCount[i]);	
	else glDrawArrays(GL_LINES, 0, vertexCount[i]);	
}

void renderGL(){

	
	/*uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	/*GLfloat xTransTemp = 0.0, yTransTemp = 0.0, zTransTemp = 0.0; 
	for(int i=0; i<vertexNo; i++){
		xTransTemp += vertices[i].x;
		yTransTemp += vertices[i].y;
		zTransTemp += vertices[i].z;
	}
	xTransTemp = -xTransTemp/vertexNo;
	yTransTemp = -yTransTemp/vertexNo;
	zTransTemp = -zTransTemp/vertexNo;
	*/
	//translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(xTransTemp, yTransTemp, zTransTemp));
	/*rotationMatrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, zrot, glm::vec3(0.0f,0.0f,1.0f));
	modelviewMatrix = rotationMatrix; //* translationMatrix;

	//translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-xTransTemp, -yTransTemp, -zTransTemp));
	//modelviewMatrix = translationMatrix * modelviewMatrix;
	
	translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(xTrans, yTrans, zTrans));
	modelviewMatrix = translationMatrix*modelviewMatrix;
	*/
	double scale_factor = 10;
	orthoMatrix = glm::ortho(-scale_factor, scale_factor, -scale_factor, scale_factor, -scale_factor, scale_factor);
	modelviewMatrix = orthoMatrix;

	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	GLuint vPosition, vColor;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderHelper(3);
	renderHelper(0);
	renderHelper(1);
	renderHelper(2);

}

int main(int argc, char** argv)
{
	//! The pointer to the GLFW window
	GLFWwindow* window;

	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
	if (!glfwInit())
		return -1;

	//We want OpenGL 4.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//This is for MacOSX - can be omitted otherwise
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	//We don't want the old OpenGL 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(512, 512, "Assignment 1", NULL, NULL);
	if (!window)
		{
			glfwTerminate();
			return -1;
		}
	
	//! Make the window's context current 
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	//Turn this on to get Shader based OpenGL
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
		{
			//Problem: glewInit failed, something is seriously wrong.
			std::cerr<<"GLEW Init Failed : %s"<<std::endl;
		}

	//Print and see what context got enabled
	std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
	std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
	std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
	std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Initialize GL state
	csX75::initGL();
	initBuffersGL();
	bool tempBool = false;

	//Filling vertexGroups and colorGroups
	std::cout << "loading scene is to happen" << std::endl;

	loadScene();
	
	std::cout << "loading is done" << std::endl;
	for(int i=0;i<vertexCount[3];i++){
		// std::cout << vertexGroups[3][i].x << " " << vertexGroups[3][i].y << " " << vertexGroups[3][i].z << " " << colorGroups[3][i].x << " " << colorGroups[3][i].y << " " << colorGroups[3][i].z << " " << std::endl; 
	}
	std::cout << vertexCount[0] << " " << vertexCount[1] << " " << vertexCount[2] << " " << vertexCount[3] << std::endl; 
	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
		{
			renderGL();
			glfwSwapBuffers(window);
			if(terminalInput = 1){
				glfwPollEvents();
			}
		}
	
	glfwTerminate();

	return 0;
}
