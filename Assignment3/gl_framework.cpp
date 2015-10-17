#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern csX75::HNode* chest, *head, *rightUpperArm, *rightLowerArm, *leftUpperArm, *leftLowerArm,
					*leftUpperLeg, *leftLowerLeg, *rightUpperLeg, *rightLowerLeg, *curr_node;
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
		else if(key == GLFW_KEY_D && action == GLFW_PRESS){
			chest->inc_tx(1);
		}
		else if(key == GLFW_KEY_A && action == GLFW_PRESS){
			chest->inc_tx(0);
		}
		else if(key == GLFW_KEY_W && action == GLFW_PRESS){
			chest->inc_ty(1);
		}
		else if(key == GLFW_KEY_S && action == GLFW_PRESS){
			chest->inc_ty(0);
		}
		else if(key == GLFW_KEY_H && action == GLFW_PRESS){
			curr_node = head;
			std::cout<<"Selected head"<<std::endl;
		}
		else if(key == GLFW_KEY_J && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT){
			curr_node = leftUpperArm;
			std::cout<<"Selected leftUpperArm"<<std::endl;
		}
		else if(key == GLFW_KEY_J && action == GLFW_PRESS){
			curr_node = leftLowerArm;
			std::cout<<"Selected leftLowerArm"<<std::endl;
		}
		else if(key == GLFW_KEY_K && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT){
			curr_node = rightUpperArm;
			std::cout<<"Selected rightUpperArm"<<std::endl;
		}
		else if(key == GLFW_KEY_K && action == GLFW_PRESS){
			curr_node = rightLowerArm;
			std::cout<<"Selected rightLowerArm"<<std::endl;
		}
		else if(key == GLFW_KEY_N && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT){
			curr_node = leftUpperLeg;
			std::cout<<"Selected leftUpperLeg"<<std::endl;
		}
		else if(key == GLFW_KEY_N && action == GLFW_PRESS){
			curr_node = leftLowerLeg;
			std::cout<<"Selected leftLowerLeg"<<std::endl;
		}
		else if(key == GLFW_KEY_M && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT){
			curr_node = rightUpperLeg;
			std::cout<<"Selected rightUpperLeg"<<std::endl;
		}
		else if(key == GLFW_KEY_M && action == GLFW_PRESS){
			curr_node = rightLowerLeg;
			std::cout<<"Selected rightLowerLeg"<<std::endl;
		}
		else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
			curr_node->inc_ry();
			std::cout<<"Selected increasingY"<<std::endl;
		}
		else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
			curr_node->dec_ry();
			std::cout<<"Selected decreasingY"<<std::endl;
		}
		else if(key == GLFW_KEY_UP && action == GLFW_PRESS){
			curr_node->inc_rx();
			std::cout<<"Selected increasingX"<<std::endl;
		}
		else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
			curr_node->dec_rx();
			std::cout<<"Selected decreasingX"<<std::endl;
		}
		else if(key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS){
			curr_node->inc_rz();
			std::cout<<"Selected increasingZ"<<std::endl;
		}
		else if(key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS){
			curr_node->dec_rz();
			std::cout<<"Selected decreasingZ"<<std::endl;
		}
	}
};
	

	// else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		//   curr_node = node1;  
		// else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		//   curr_node = node2; 
		// else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		//   curr_node = node3; 
		// else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		//   curr_node->dec_ry();
		// else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		//   curr_node->inc_ry();
		// else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		//   curr_node->dec_rx();
		// else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		//   curr_node->inc_rx();
		// else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
		//   curr_node->dec_rz();
		// else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
		//   curr_node->inc_rz();
		// else if (key == GLFW_KEY_P && action == GLFW_PRESS)
		//   enable_perspective = !enable_perspective;   
		// else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
		//   c_yrot -= 1.0;
		// else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
		//   c_yrot += 1.0;
		// else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
		//   c_xrot -= 1.0;
		// else if (key == GLFW_KEY_S  && action == GLFW_PRESS)
		//   c_xrot += 1.0;        
		// else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
		//   c_zrot -= 1.0;
		// else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
		//   c_zrot += 1.0;   
		


