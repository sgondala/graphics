#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern GLfloat c_xpos,c_ypos,c_zpos;
extern bool enable_perspective;
extern csX75::HNode* chest, *head, *rightUpperArm, *rightLowerArm, *leftUpperArm, *leftLowerArm,
					*leftUpperLeg, *leftLowerLeg, *rightUpperLeg, *rightLowerLeg, *curr_node;
extern csX75::HNode* vbody, *vneck, *vhead, *vpod1arm, *vpod1, *vpod2arm, *vpod2, *vpod3arm, *vpod3, *vpod4arm, *vpod4;
extern int objectSelected;
extern int podno, podarmno, podselected;
extern int light1, light2, spotlight, textureenable;
extern bool enable_perspective;

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
		// camera controls ------------------------------------------------------------//

		else if(key == GLFW_KEY_F6 && action == GLFW_PRESS){
			if(!enable_perspective){
				objectSelected = 3;
				std::cout << "perspetive mode selected" << std::endl;
				enable_perspective = true;
			}
			else{
				enable_perspective = false;
				std::cout << "perspective mode disabled" << std:: endl;
				objectSelected = 1;
				std::cout << "Default c3po is choosen" << std::endl;
			}

		}
		else if(key == GLFW_KEY_Q && action == GLFW_PRESS && objectSelected == 3){
			c_zpos -= 0.1;
			std::cout << "camera moved along Z" << std::endl;
		}
		else if(key == GLFW_KEY_E && action == GLFW_PRESS && objectSelected == 3){
			c_zpos += 0.1;
			std::cout << "camera moved along Z" << std::endl;
		}
		else if(key == GLFW_KEY_W && action == GLFW_PRESS && objectSelected == 3){
			c_ypos += 0.1;
			std::cout << "camera moved along Y" << std::endl;
		}
		else if(key == GLFW_KEY_A && action == GLFW_PRESS && objectSelected == 3){
			c_xpos -= 0.1;
			std::cout << "camera moved along X" << std::endl;
		}
		else if(key == GLFW_KEY_S && action == GLFW_PRESS && objectSelected == 3){
			c_ypos -= 0.1; 
			std::cout << "camera moved along Y" << std::endl;
		}
		else if(key == GLFW_KEY_D && action == GLFW_PRESS && objectSelected == 3){
			c_xpos += 0.1;
			std::cout << "camera moved along X" << std::endl;
		}
		
		else if(key == GLFW_KEY_UP && action == GLFW_PRESS && objectSelected == 3){
			c_xrot -= 0.1; 
			std::cout << "camera rotated along X" << std::endl;
		}
		else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS && objectSelected == 3){
			c_xrot += 0.1; 
			std::cout << "camera rotated along X" << std::endl;
		}
		else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS && objectSelected == 3){
			c_yrot -= 0.1; 
			std::cout << "camera rotated along Y" << std::endl;
		}
		else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS && objectSelected == 3){
			c_yrot += 0.1; 
			std::cout << "camera rotated along Y" << std::endl;
		}
		else if(key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && objectSelected == 3){
			c_zrot -= 0.1; 
			std::cout << "camera rotated along Z" << std::endl;
		}
		else if(key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && objectSelected == 3){
			c_zrot += 0.1;
			std::cout << "camera rotated along Z" << std::endl; 
		}
		//light controls--------------------------------------------------------------//
		else if (key == GLFW_KEY_F1 && action == GLFW_PRESS){
			if(light1 == 0){
				light1 = 1;
				std::cout << "Light 1 turned on" << std::endl;
			}
			else{
				light1 = 0;
				std::cout << "Light 1 turned off" << std::endl;
			}	
		}
		else if (key == GLFW_KEY_F2 && action == GLFW_PRESS){
			if(light2 == 0){
				light2 = 1;
				std::cout << "Light 2 turned on" << std::endl;
			}
			else{
				light2 = 0;
				std::cout << "Light 2 turned off" << std::endl;
			}	
		}
		else if (key == GLFW_KEY_F3 && action == GLFW_PRESS){
			if(spotlight == 0){
				spotlight = 1;
				std::cout << "SpotLight turned on" << std::endl;
			}
			else {
				spotlight = 0;
				std::cout << "SpotLight turned off" << std::endl;
			}
		}
		else if (key == GLFW_KEY_F7 && action == GLFW_PRESS){
			if(textureenable == 0){
				textureenable = 1;
				std::cout << "Texture enabled" << std::endl;
			}
			else {
				textureenable = 0;
				std::cout << "texture disabled" << std::endl;
			}
		}
		//c3po controls ---------------------------------------------------------------//
		else if (key == GLFW_KEY_F4 && action == GLFW_PRESS){
			objectSelected = 1;
			std::cout << "Selected c3po" << std::endl;
		}
		else if(key == GLFW_KEY_D && action == GLFW_PRESS && objectSelected == 1){
			chest->inc_tx(1);
		}
		else if(key == GLFW_KEY_A && action == GLFW_PRESS && objectSelected == 1){
			chest->inc_tx(0);
		}
		else if(key == GLFW_KEY_W && action == GLFW_PRESS && objectSelected == 1){
			chest->inc_ty(1);
		}
		else if(key == GLFW_KEY_S && action == GLFW_PRESS && objectSelected == 1){
			chest->inc_ty(0);
		}
		else if(key == GLFW_KEY_H && action == GLFW_PRESS && objectSelected == 1){
			curr_node = head;
			std::cout<<"Selected head"<<std::endl;
		}
		else if(key == GLFW_KEY_J && action == GLFW_PRESS && objectSelected == 1 && mods==GLFW_MOD_SHIFT){
			curr_node = leftUpperArm;
			std::cout<<"Selected leftUpperArm"<<std::endl;
		}
		else if(key == GLFW_KEY_J && action == GLFW_PRESS && objectSelected == 1){
			curr_node = leftLowerArm;
			std::cout<<"Selected leftLowerArm"<<std::endl;
		}
		else if(key == GLFW_KEY_K && action == GLFW_PRESS && objectSelected == 1 && mods==GLFW_MOD_SHIFT){
			curr_node = rightUpperArm;
			std::cout<<"Selected rightUpperArm"<<std::endl;
		}
		else if(key == GLFW_KEY_K && action == GLFW_PRESS && objectSelected == 1){
			curr_node = rightLowerArm;
			std::cout<<"Selected rightLowerArm"<<std::endl;
		}
		else if(key == GLFW_KEY_N && action == GLFW_PRESS && objectSelected == 1 && mods==GLFW_MOD_SHIFT){
			curr_node = leftUpperLeg;
			std::cout<<"Selected leftUpperLeg"<<std::endl;
		}
		else if(key == GLFW_KEY_N && action == GLFW_PRESS && objectSelected == 1){
			curr_node = leftLowerLeg;
			std::cout<<"Selected leftLowerLeg"<<std::endl;
		}
		else if(key == GLFW_KEY_M && action == GLFW_PRESS && objectSelected == 1 && mods==GLFW_MOD_SHIFT){
			curr_node = rightUpperLeg;
			std::cout<<"Selected rightUpperLeg"<<std::endl;
		}
		else if(key == GLFW_KEY_M && action == GLFW_PRESS && objectSelected == 1){
			curr_node = rightLowerLeg;
			std::cout<<"Selected rightLowerLeg"<<std::endl;
		}
		else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS && objectSelected == 1){
			curr_node->inc_ry();
			std::cout<<"Selected increasingY"<<std::endl;
		}
		else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS && objectSelected == 1){
			curr_node->dec_ry();
			std::cout<<"Selected decreasingY"<<std::endl;
		}
		else if(key == GLFW_KEY_UP && action == GLFW_PRESS && objectSelected == 1){
			curr_node->inc_rx();
			std::cout<<"Selected increasingX"<<std::endl;
		}
		else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS && objectSelected == 1){
			curr_node->dec_rx();
			std::cout<<"Selected decreasingX"<<std::endl;
		}
		else if(key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && objectSelected == 1){
			curr_node->inc_rz();
			std::cout<<"Selected increasingZ"<<std::endl;
		}
		else if(key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && objectSelected == 1){
			curr_node->dec_rz();
			std::cout<<"Selected decreasingZ"<<std::endl;
		}
		//c3po controls ---------------------------------------------------------------//
		

		//vulture droid controls-------------------------------------------------------//
		else if (key == GLFW_KEY_F5 && action == GLFW_PRESS){
			objectSelected = 2;
			curr_node = vbody;
			std::cout << "body of the vulture droid is selected" << std::endl;
		}
		else if(key == GLFW_KEY_D && action == GLFW_PRESS && objectSelected == 2){
			vbody->inc_tx(1);
		}
		else if(key == GLFW_KEY_A && action == GLFW_PRESS && objectSelected == 2){
			vbody->inc_tx(0);
		}
		else if(key == GLFW_KEY_W && action == GLFW_PRESS && objectSelected == 2){
			vbody->inc_ty(1);
		}
		else if(key == GLFW_KEY_S && action == GLFW_PRESS && objectSelected == 2){
			vbody->inc_ty(0);
		}
		else if(key == GLFW_KEY_P && action == GLFW_PRESS && objectSelected == 2){
			podselected = 1;
			std::cout << "pod selected. Now select the number of pod to move" << std::endl;
		}
		else if(key == GLFW_KEY_1 && action == GLFW_PRESS && objectSelected == 2){
			if(podselected == 1){
				podno = 1;
				std::cout<<"pod1 selected"<<std::endl;
			}
			else {
				podarmno = 1;
				std::cout<<"pod arm 1 selected"<<std::endl;
			}
		}
		else if(key == GLFW_KEY_2 && action == GLFW_PRESS && objectSelected == 2){
			if(podselected == 1){
				podno = 2;
				std::cout<<"pod2 selected"<<std::endl;
			}
			else {
				podarmno = 2;
				std::cout<<"pod arm 2 selected"<<std::endl;
			}
		}
		else if(key == GLFW_KEY_3 && action == GLFW_PRESS && objectSelected == 2){
			if(podselected == 1){
				podno = 3;
				std::cout<<"pod 3 selected"<<std::endl;
			}
			else {
				podarmno = 3;
				std::cout<<"pod arm 3 selected"<<std::endl;
			}
		}
		else if(key == GLFW_KEY_4 && action == GLFW_PRESS && objectSelected == 2){
			if(podselected == 1){
				podno = 4;
				std::cout<<"pod 4 selected"<<std::endl;
			}
			else {
				podarmno = 4;
				std::cout<<"pod arm 4 selected"<<std::endl;
			}
		}
		else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS && objectSelected == 2){
			if(podselected == 1){
				if(podno == 1){
					vpod1->dec_rx();
					std::cout << "pod 1 moved";
				}
				else if(podno == 2){
					vpod2->inc_rx();
					std::cout << "pod 2 moved";
				}
				else if(podno == 3){
					vpod3->dec_rx();
					std::cout << "pod 3 moved";
				}
				else if(podno == 4){
					vpod4->inc_rx();
					std::cout << "pod 4 moved";
				}
			}
			else {
				if(podarmno == 1){
					vpod1arm->inc_ry();
					std::cout << "pod arm 1 moved";
				}
				else if(podarmno == 2){
					vpod2arm->dec_ry();
					std::cout << "pod arm 2 moved";
				}
				else if(podarmno == 3){
					vpod3arm->dec_ry();
					std::cout << "pod arm 3 moved";
				}
				else if(podarmno == 4){
					vpod4arm->inc_ry();
					std::cout << "pod arm 4 moved";
				}
			}
			std::cout << " in positive direction" << std::endl;
		}
		else if(key == GLFW_KEY_MINUS && action == GLFW_PRESS && objectSelected == 2){
			if(podselected == 1){
				if(podno == 1){
					vpod1->inc_rx();
					std::cout << "pod 1 moved";
				}
				else if(podno == 2){
					vpod2->dec_rx();
					std::cout << "pod 2 moved";
				}
				else if(podno == 3){
					vpod3->inc_rx();
					std::cout << "pod 3 moved";
				}
				else if(podno == 4){
					vpod4->dec_rx();
					std::cout << "pod 4 moved";
				}
			}
			else {
				if(podarmno == 1){
					vpod1arm->dec_ry();
					std::cout << "pod arm 1 moved";
				}
				else if(podarmno == 2){
					vpod2arm->inc_ry();
					std::cout << "pod arm 2 moved";
				}
				else if(podarmno == 3){
					vpod3arm->inc_ry();
					std::cout << "pod arm 3 moved";
				}
				else if(podarmno == 4){
					vpod4arm->dec_ry();
					std::cout << "pod arm 4 moved";
				}
			}
			std::cout << " in negative direction" << std::endl;
		}
		else if(key == GLFW_KEY_U && action == GLFW_PRESS && objectSelected == 2){
			vneck->inc_rx();
			std::cout<<"vulture neck moved in positive direction"<<std::endl;
		}
		else if(key == GLFW_KEY_B && action == GLFW_PRESS && objectSelected == 2){
			vneck->dec_rx();
			std::cout<<"vulture neck moved in negative direction"<<std::endl;
		}
		else if(key == GLFW_KEY_R && action == GLFW_PRESS && objectSelected == 2){
			vhead->inc_ry();
			std::cout<<"vulture head moved towards right"<<std::endl;
		}
		else if(key == GLFW_KEY_L && action == GLFW_PRESS && objectSelected == 2){
			vhead->dec_ry();
			std::cout<<"vulture neck moved towards left"<<std::endl;
		}
		else if(key == GLFW_KEY_U && action == GLFW_PRESS && objectSelected == 2){
			vneck->inc_rx();
			std::cout<<"vulture Selected increasingY"<<std::endl;
		}
		else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS && objectSelected == 2){
			curr_node->inc_ry();
			std::cout<<"vulture Selected increasingY"<<std::endl;
		}
		else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS && objectSelected == 2){
			curr_node->dec_ry();
			std::cout<<"vulture  Selected decreasingY"<<std::endl;
		}
		else if(key == GLFW_KEY_UP && action == GLFW_PRESS && objectSelected == 2){
			curr_node->inc_rx();
			std::cout<<"vulture  Selected increasingX"<<std::endl;
		}
		else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS && objectSelected == 2){
			curr_node->dec_rx();
			std::cout<<"vulture  Selected decreasingX"<<std::endl;
		}
		else if(key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && objectSelected == 2){
			curr_node->inc_rz();
			std::cout<<"vulture  Selected increasingZ"<<std::endl;
		}
		else if(key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && objectSelected == 2){
			curr_node->dec_rz();
			std::cout<<"vulture  Selected decreasingZ"<<std::endl;
		}

		//vulture droid controls-------------------------------------------------------//

	}
};
	

	// else if (key == GLFW_KEY_1 && action == GLFW_PRESS && objectSelected == 1)
		//   curr_node = node1;  
		// else if (key == GLFW_KEY_2 && action == GLFW_PRESS && objectSelected == 1)
		//   curr_node = node2; 
		// else if (key == GLFW_KEY_3 && action == GLFW_PRESS && objectSelected == 1)
		//   curr_node = node3; 
		// else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && objectSelected == 1)
		//   curr_node->dec_ry();
		// else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && objectSelected == 1)
		//   curr_node->inc_ry();
		// else if (key == GLFW_KEY_UP && action == GLFW_PRESS && objectSelected == 1)
		//   curr_node->dec_rx();
		// else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && objectSelected == 1)
		//   curr_node->inc_rx();
		// else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && objectSelected == 1)
		//   curr_node->dec_rz();
		// else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && objectSelected == 1)
		//   curr_node->inc_rz();
		// else if (key == GLFW_KEY_P && action == GLFW_PRESS && objectSelected == 1)
		//   enable_perspective = !enable_perspective;   
		// else if (key == GLFW_KEY_A  && action == GLFW_PRESS && objectSelected == 1)
		//   c_yrot -= 1.0;
		// else if (key == GLFW_KEY_D  && action == GLFW_PRESS && objectSelected == 1)
		//   c_yrot += 1.0;
		// else if (key == GLFW_KEY_W  && action == GLFW_PRESS && objectSelected == 1)
		//   c_xrot -= 1.0;
		// else if (key == GLFW_KEY_S  && action == GLFW_PRESS && objectSelected == 1)
		//   c_xrot += 1.0;        
		// else if (key == GLFW_KEY_Q  && action == GLFW_PRESS && objectSelected == 1)
		//   c_zrot -= 1.0;
		// else if (key == GLFW_KEY_E  && action == GLFW_PRESS && objectSelected == 1)
		//   c_zrot += 1.0;   
		


