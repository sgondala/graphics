#include "gl_framework.hpp"

extern GLfloat xrot,yrot,zrot, intTemp, mode;
extern std::vector<glm::vec4> vertices;
extern std::vector<glm::vec4> colors;

int colorDecider = 0;

void helperPrinter(std::ofstream& myFile, int i){
	myFile << vertices[i].x <<" "<< vertices[i].y<< " "<<vertices[i].z<<" "
		<< colors[i].r<< " "<<colors[i].g<< " "<<colors[i].b <<std::endl;
	return;
}

namespace csX75
{
	//! Initialize GL State

	void initGL(void)
	{
		//Set framebuffer clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//Set depth buffer furthest depth
		glClearDepth(1.0);
		//Set depth test to less-than
		glDepthFunc(GL_LESS);
		//Enable depth testing
		glEnable(GL_DEPTH_TEST);
	}
	
	//!GLFW Error Callback
	void error_callback(int error, const char* description)
	{
		std::cerr<<description<<std::endl;
	}
	
	//!GLFW framebuffer resize callback
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		//!Resize the viewport to fit the window size - draw to entire window
		glViewport(0, 0, width, height);
	}
	
	//!GLFW keyboard callback
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//!Close the window if the ESC key was pressed
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		else if (key == GLFW_KEY_A && action == GLFW_PRESS)
			{std::cout<<"Accepted"<<std::endl;}
		else if (key == GLFW_KEY_M && action == GLFW_PRESS){
			if(mode==0){
				std::cout<<"Already in modeling mode"<<std::endl;
			}
			else{
				mode = 0;
				std::cout<<"Modelling mode on"<<std::endl;
			}
		}
		else if (key == GLFW_KEY_I && action == GLFW_PRESS){
			if(mode==1){
				std::cout<<"Already in inspection mode"<<std::endl;
			}
			else{
				mode = 1;
				std::cout<<"Inspection mode on"<<std::endl;
			}
		}
		else if (key == GLFW_KEY_K && action == GLFW_PRESS && mode==0){
			std::string fileName;
			std::cout<<"Enter file name (Do not append .raw): ";
			std::cin>>fileName;
			fileName += ".raw";
			std::ofstream myFile;
			myFile.open (fileName.c_str());
			for(int i=1; i<vertices.size()-1; i++){
				
				helperPrinter(myFile, 0);
				helperPrinter(myFile, i);
				helperPrinter(myFile, i+1);
			}
			myFile.close();
			vertices.clear();
			colors.clear();
		}
		else if (key == GLFW_KEY_L && action == GLFW_PRESS && mode==0){
			std::string fileName, line;
			std::cout<<"Enter file name (Do not append .raw): ";
			std::cin>>fileName;
			vertices.clear();
			colors.clear();
			fileName += ".raw";
			std::ifstream myFile(fileName.c_str());
			int lineNo = 0;
			if(myFile.is_open()){
				std::vector<double> probablyLast;
				while (getline(myFile,line)){
					std::vector<double> inputFromFile;
					while(line.find(' ')!=std::string::npos){
						int temp  = line.find(' ');
						std::string value = line.substr(0, temp);
						inputFromFile.push_back(atof(value.c_str()));
						line = line.substr(temp+1);
					}
					inputFromFile.push_back(atof(line.c_str()));
					if(lineNo==0 || lineNo%3==1){
						vertices.push_back(
							glm::vec4(inputFromFile[0],inputFromFile[1],inputFromFile[2],1));
						colors.push_back(
							glm::vec4(inputFromFile[3],inputFromFile[4],inputFromFile[5],1));
					}
					if(lineNo%3==2){
						probablyLast = inputFromFile;
					}
					lineNo++;
				}
				vertices.push_back(
					glm::vec4(probablyLast[0], probablyLast[1], probablyLast[2], 1));
				colors.push_back(
					glm::vec4(probablyLast[3], probablyLast[4], probablyLast[5], 1));
				myFile.close();
			}
		}
	}

	void mouse_callback(GLFWwindow* window, int button, int action, int mods){
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT
			&& mode == 0){
			if(vertices.size()>0){
				vertices.pop_back();
				colors.pop_back();
				std::cout<<"Removed last vertex"<<std::endl;
			}
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mode == 0){
			double x,y,z;
			double *xAddr; double *yAddr;
			xAddr = &x; yAddr = &y;
			glfwGetCursorPos(window, xAddr, yAddr);
			std::cout<<"Value of z? ";
			std::cin>>z;
			vertices.push_back(glm::vec4(x,y,z,1));
			std::cout<<"Added "<<x<<" "<<y<<" "<<z<<std::endl;
			colors.push_back(glm::vec4(0,0,0,1));
			colors[colors.size()-1][colorDecider] = 1;
			colorDecider = (colorDecider+1)%3;
			std::cout<<"Color is "<<colors[colors.size()-1].x<<" "<<colors[colors.size()-1].y
			<<" "<<colors[colors.size()-1].z<<std::endl;
		}
	}
};  
	


