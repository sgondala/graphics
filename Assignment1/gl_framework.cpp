#include "gl_framework.hpp"

extern GLfloat xrot,yrot,zrot, intTemp, mode;
extern std::vector<std::pair<double,double> > vertices;

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
	}

	void mouse_callback(GLFWwindow* window, int button, int action, int mods){
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT
			&& mode == 0){
			if(vertices.size()>0){
				vertices.pop_back();
				std::cout<<"Removed last vertex"<<std::endl;
			}
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mode == 0){
			double x,y;
			double *xAddr; double *yAddr;
			xAddr = &x; yAddr = &y;
			glfwGetCursorPos(window, xAddr, yAddr);
			vertices.push_back(std::make_pair(x,y));
			std::cout<<"Added "<<x<<" "<<y<<std::endl;
		}
	}
};  
	


