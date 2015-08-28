#include "gl_framework.hpp"

extern glm::vec4 vertices[100];
extern glm::vec4 colors[100];
extern int vertexNo, mode;
extern GLfloat xTrans, yTrans, zTrans, xrot, yrot, zrot;
extern int terminalInput;
extern int rotationCase;

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
		else if (key == GLFW_KEY_K && action == GLFW_PRESS){
			std::string fileName;
			terminalInput = 0;
			std::cout<<"Enter file name (Do not append .raw): ";
			std::cin>>fileName;
			terminalInput = 1;
			fileName += ".raw";
			std::ofstream myFile;
			myFile.open (fileName.c_str());
			for(int i=0; i<vertexNo; i++){
				myFile << vertices[i].x <<" "<< vertices[i].y<< " "<< vertices[i].z<<" "
			<< colors[i].r<< " "<<colors[i].g<< " "<<colors[i].b <<std::endl;
			}
			myFile.close();
			std::cout << "File saved as " << fileName << std::endl; 
			//vertexNo = 0;						//	<== are these necessary
			//xTrans = yTrans = zTrans = 0.0;		//
		}
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
		}
		else if (key == GLFW_KEY_R && action == GLFW_PRESS && mode==1){
			GLfloat xTransTemp = 0.0, yTransTemp = 0.0, zTransTemp = 0.0; 
			for(int i=0; i<vertexNo; i++){
				xTransTemp += vertices[i].x;
				yTransTemp += vertices[i].y;
				zTransTemp += vertices[i].z;
			}
			xTrans = -xTransTemp/vertexNo;
			yTrans = -yTransTemp/vertexNo;
			zTrans = -zTransTemp/vertexNo;
			std::cout<<xTrans<<" "<<yTrans<<" "<<zTrans<<std::endl;
		}
		else if (key == GLFW_KEY_W && action == GLFW_PRESS && mode==1){
			yTrans = 0.1;
		}
		else if (key == GLFW_KEY_S && action == GLFW_PRESS && mode==1){
			yTrans = -0.1;
		}
		else if (key == GLFW_KEY_A && action == GLFW_PRESS && mode==1){
			xTrans = -0.1;
		}
		else if (key == GLFW_KEY_D && action == GLFW_PRESS && mode==1){
			xTrans = 0.1;
		}
		else if (key == GLFW_KEY_Z && action == GLFW_PRESS && mode==1){
			zTrans = 0.1;
		}
		else if (key == GLFW_KEY_X && action == GLFW_PRESS && mode==1){
			zTrans = -0.1;
		}
		else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS && mode == 1){
			yrot = -0.1;
			rotationCase = 1;
		}
		else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS && mode == 1){
			yrot = 0.1;
			rotationCase = 1;
		}
		else if(key == GLFW_KEY_UP && action == GLFW_PRESS && mode == 1){
			xrot = 0.1;
			rotationCase = 1;
		}
		else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS && mode == 1){
			xrot = -0.1;
			rotationCase = 1;
		}
		else if(key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && mode == 1){
			zrot = 0.1;
			rotationCase = 1;
		}
		else if(key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && mode == 1){
			zrot = -0.1;
			rotationCase = 1;
		}

	}
	double xydistance(glm::vec4 a, glm::vec4 b){
		return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
	}
	void mouse_callback(GLFWwindow* window, int button, int action, int mods){
		double x,y,z;
		double *xAddr; double *yAddr;
		xAddr = &x; yAddr = &y;
		double R,G,B;
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT
			&& mode == 0){
			if(vertexNo>0){
				std::cout<<"Removed last vertex : ("<<vertices[vertexNo-1].x << "," << vertices[vertexNo-1].y << " " << vertices[vertexNo-1].z << ")" << std::endl;
				vertexNo--;
			}
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mode==0){
			glfwGetCursorPos(window, xAddr, yAddr);
			terminalInput = 0;
			std::string response;
			if(vertexNo >=3){
				std::cout << "Merge with nearest neighbor vertex? (y or n)" << std::endl;
				std::cin >> response;
			} 
			if(vertexNo < 3 || (vertexNo >= 3 && (response == "n" || response == "no" || response == "NO"))){
				std::cout<<"Value of z (Between -1 and 1)? ";
				terminalInput = 0;
				std::cin>>z;
				std::cout << "Colors in R:G:B format" << std::endl;
				std::cout << "R?\t";
				std::cin >> R;
				std::cout << "G?\t";
				std::cin >> G;
				std::cout << "B?\t";
				std::cin >> B;
				
				terminalInput = 1;
				x = x/256 -1;
				y = -y/256 +1;
				// y *= -1;
				vertices[vertexNo] = glm::vec4(x, y, z , 1); 
				// vertices.push_back(glm::vec4(x,y,z,1));
				std::cout<<"Added vertex: ("<<x<<","<<y<<","<<z<<")" <<std::endl;
				colors[vertexNo] = glm::vec4(0,0,0,1); 
				// colors.push_back(glm::vec4(0,0,0,1));
				vertexNo++;
				colors[vertexNo-1][0] = R;
				colors[vertexNo-1][1] = G;
				colors[vertexNo-1][2] = B;
				std::cout<<"Color is "<<colors[vertexNo-1].x<<" "<<colors[vertexNo-1].y
				<<" "<<colors[vertexNo-1].z<<std::endl;
			}
			else{
				x = x/256 -1;
				y = -y/256 +1;
				std::cout << "Nearest neighbour is chosen" <<  std::endl;
				glm::vec4 tempVertex = glm::vec4(x,y,0,1);
				int minIndex = 0;
				double minVal = xydistance(vertices[0],tempVertex);
				for(int i=1;i<(vertexNo/3)*3;i++){
					if(xydistance(vertices[i],tempVertex) < minVal){
						minIndex = i;
						minVal = xydistance(vertices[i],tempVertex);
					}
				}
				vertexNo++;
				vertices[vertexNo-1] = vertices[minIndex];
				colors[vertexNo-1] = colors[minIndex];
			}	
		}    
	}
};
