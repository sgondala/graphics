#include "gl_framework.hpp"

extern glm::vec4 vertices[200];
extern glm::vec4 colors[200];
extern int vertexNo;
extern GLfloat xTrans, yTrans, zTrans, xrot, yrot, zrot;
extern int terminalInput;
extern glm::vec3 eye, lookAt, up;
extern bool choosenVCS;
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
	
	// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){}
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//!Close the window if the ESC key was pressed
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		else if (key == GLFW_KEY_L && action == GLFW_PRESS){
			std::string fileName, line;
			terminalInput = 0;
			std::cout<<"Enter file name (Do not append .raw): ";
			std::cin>>fileName;
			terminalInput = 1;
			vertexNo = 0;
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
					vertices[vertexNo] = glm::vec4(inputFromFile[0],inputFromFile[1],inputFromFile[2],1);
					colors[vertexNo] = glm::vec4(inputFromFile[3],inputFromFile[4],inputFromFile[5],1);
					vertexNo++;
					lineNo++;
				}
				myFile.close();
				std::cout << "Loaded file " << fileName << std::endl; 
			}
			else{
				std::cout << "file cannot be opened" << std::endl;
			}
		}
		else if (key == GLFW_KEY_W && action == GLFW_PRESS){
			yTrans = yTrans + 0.1;
		}
		else if (key == GLFW_KEY_S && action == GLFW_PRESS){
			yTrans = yTrans + -0.1;
		}
		else if (key == GLFW_KEY_A && action == GLFW_PRESS){
			xTrans = xTrans + -0.1;
		}
		else if (key == GLFW_KEY_D && action == GLFW_PRESS){
			xTrans = xTrans + 0.1;
		}
		else if (key == GLFW_KEY_Z && action == GLFW_PRESS){
			zTrans = zTrans + 0.1;
		}
		else if (key == GLFW_KEY_X && action == GLFW_PRESS){
			zTrans = zTrans + -0.1;
		}
		else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
			yrot = yrot + -0.1;
		}
		else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
			yrot = yrot + 0.1;
		}
		else if(key == GLFW_KEY_UP && action == GLFW_PRESS){
			xrot = xrot + 0.1;
		}
		else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
			xrot = xrot + -0.1;
		}
		else if(key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS){
			zrot = zrot + 0.1;
		}
		else if(key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS){
			zrot = zrot + -0.1;
		}
		else if(key == GLFW_KEY_1 && action == GLFW_PRESS){
			choosenVCS = true;
		}

	}
	double xydistance(glm::vec4 a, glm::vec4 b){
		return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
	}
};
