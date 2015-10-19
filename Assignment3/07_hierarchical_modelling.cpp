/*
	CSX75 Tutorial 3

	Use the arrow keys and PgUp,PgDn, 
	keys to make the arms move.

	Use the keys 1,2 and 3 to switch between arms.

	Modified from An Introduction to OpenGL Programming, 
	Ed Angel and Dave Shreiner, SIGGRAPH 2013

	Written by - 
							 Harshavardhan Kode
*/


#include "07_hierarchical_modelling.hpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
const int num_vertices = 36;

//-----------------------------------------------------------------

//Eight vertices in homogenous coordinates
//elongated cuboid, basic arm in the hierarchy;
glm::vec4 positions[100];

//RGBA colors
glm::vec4 colors[100] = { 
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0)

};

glm::vec4 red = glm::vec4(1.0,0.0,0.0,1.0);
glm::vec4 green = glm::vec4(0.0,1.0,0.0,1.0);
glm::vec4 blue = glm::vec4(0.0,0.0,1.0,1.0);


int tri_idx=0;
glm::vec4 v_positions[100];
glm::vec4 v_colors[100];

// quad generates two triangles for each face and assigns colors to the vertices
void quad(int a, int b, int c, int d, glm::vec4 color)
{
	v_colors[tri_idx] = color; v_positions[tri_idx] = positions[a]; tri_idx++;
	v_colors[tri_idx] = color; v_positions[tri_idx] = positions[b]; tri_idx++;
	v_colors[tri_idx] = color; v_positions[tri_idx] = positions[c]; tri_idx++;
	v_colors[tri_idx] = color; v_positions[tri_idx] = positions[a]; tri_idx++;
	v_colors[tri_idx] = color; v_positions[tri_idx] = positions[c]; tri_idx++;
	v_colors[tri_idx] = color; v_positions[tri_idx] = positions[d]; tri_idx++;
 }

 void tri(int a, int b, int c, glm::vec4 color){
 	v_colors[tri_idx] = color; v_positions[tri_idx] = positions[a]; tri_idx++;
	v_colors[tri_idx] = color; v_positions[tri_idx] = positions[b]; tri_idx++;
	v_colors[tri_idx] = color; v_positions[tri_idx] = positions[c]; tri_idx++;
 }

 void quadpyramid(int a,int b, int c, int d, int apex, glm::vec4 color){
 	// number of vertices : 18
	quad(a,b,c,d,glm::vec4(1.0,1.0,0.0,1));
	tri(a,b,apex,red);
	tri(b,c,apex,green); 
	tri(c,d,apex,blue);
	tri(a,d,apex,green);
 }

 void tripyramid(int a, int b, int c, int apex, glm::vec4 color){
 	// number of vertices : 12
 	tri(a,b,c,color);
 	tri(a,b,apex,color);
 	tri(b,c,apex,color);
 	tri(c,a,apex,color);
 }

 void cuboid(int p1, int p2, int p3, int p4,int p5, int p6, int p7, int p8, glm::vec4 color){
 	// number of vertices : 36
 	quad(p1,p2,p3,p4,color);
 	quad(p4,p5,p6,p7,color);
 	quad(p1,p2,p5,p6,color);
 	quad(p2,p3,p7,p6,color);
 	quad(p4,p3,p7,p8,color);
 	quad(p4,p8,p5,p1,color);
 }
 

// generate 12 triangles: 36 vertices and 36 colors
void colorcube(GLfloat xDim, GLfloat yDim, GLfloat zDim,glm::vec4 color)
{
	tri_idx = 0;
	positions[0] = glm::vec4(0,0,zDim,1);
	positions[1] = glm::vec4(0,yDim,zDim,1);
	positions[2] = glm::vec4(xDim,yDim,zDim,1);
	positions[3] = glm::vec4(xDim,0,zDim,1);
	positions[4] = glm::vec4(0,0,0,1);
	positions[5] = glm::vec4(0,yDim,0,1);
	positions[6] = glm::vec4(xDim,yDim,0,1);
	positions[7] = glm::vec4(xDim,0,0,1);		
	quad( 1, 0, 3, 2 ,color);
	quad( 2, 3, 7, 6 ,color);
	quad( 3, 0, 4, 7 ,color);
	quad( 6, 5, 1, 2 ,color);
	quad( 4, 5, 6, 7 ,color);
	quad( 5, 4, 0, 1 ,color);
}

void centercube(GLfloat xDim, GLfloat yDim, GLfloat zDim,glm::vec4 color)
{
	tri_idx = 0;
	positions[0] = glm::vec4(-xDim/2,-yDim/2,zDim/2,1);
	positions[1] = glm::vec4(-xDim/2,yDim/2,zDim/2,1);
	positions[2] = glm::vec4(xDim/2,yDim/2,zDim/2,1);
	positions[3] = glm::vec4(xDim/2,-yDim/2,zDim/2,1);
	positions[4] = glm::vec4(-xDim/2,-yDim/2,-zDim/2,1);
	positions[5] = glm::vec4(-xDim/2,yDim/2,-zDim/2,1);
	positions[6] = glm::vec4(xDim/2,yDim/2,-zDim/2,1);
	positions[7] = glm::vec4(xDim/2,-yDim/2,-zDim/2,1);		
	quad( 1, 0, 3, 2 ,color);
	quad( 2, 3, 7, 6 ,color);
	quad( 3, 0, 4, 7 ,color);
	quad( 6, 5, 1, 2 ,color);
	quad( 4, 5, 6, 7 ,color);
	quad( 5, 4, 0, 1 ,color);
}


void vbodyshape(){
	// number of vertices : 72
	tri_idx = 0;
	positions[0] = glm::vec4(-2,-1,0,1);
	positions[1] = glm::vec4(2,-1,0,1);
	positions[2] = glm::vec4(2,1,0,1);
	positions[3] = glm::vec4(-2,1,0,1);
	positions[4] = glm::vec4(-2,-1,-5,1);
	positions[5] = glm::vec4(2,-1,-5,1);
	positions[6] = glm::vec4(2,1,-5,1);
	positions[7] = glm::vec4(-2,1,-5,1);
	positions[8] = glm::vec4(0,0,2,1);
	positions[9] = glm::vec4(0,0,-7,1);		
	cuboid(0,1,2,3,4,5,6,7,blue);
	quadpyramid(0,1,2,3,8,red);
	quadpyramid(4,5,6,7,9,red);
}
//-----------------------------------------------------------------


void podshape(int xDim,int yDim, int zDim, glm::vec4 color){
	// number of vertices : 36+12
	tri_idx = 0;
	positions[0] = glm::vec4(0,0,0,1);
	positions[1] = glm::vec4(xDim,0,0,1);
	positions[2] = glm::vec4(0,0,zDim,1);
	positions[3] = glm::vec4(0,yDim,0,1);
	tripyramid(0,1,2,3,color);
}


void initBuffersGL(void)
{

	std::string vertex_shader_file("07_vshader.glsl");
	std::string fragment_shader_file("07_fshader.glsl");

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	shaderProgram = csX75::CreateProgramGL(shaderList);
	glUseProgram( shaderProgram );

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	//vulture droid ------------------------------------------------------------------------//
	vbodyshape();
	vbody = new csX75::HNode(NULL,72,v_positions,v_colors,sizeof(v_positions[0])*72,sizeof(v_positions[0])*72);

	//pod1
	colorcube(-2.8,-0.4,0.4,red);
	vpod1arm = new csX75::HNode(vbody,36,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	vpod1arm->change_parameters(-0.2,-1,-2.4,0,0,0);

	podshape(-2,-5,1,green);
	vpod1 = new csX75::HNode(vpod1arm,12,v_positions,v_colors,sizeof(v_positions[0])*12,sizeof(v_positions[0])*12);
	vpod1->change_parameters(-2.8,0,0,0,0,0);

	//pod2
	colorcube(-2.8,-0.4,-0.4,red);
	vpod2arm = new csX75::HNode(vbody,36,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	vpod2arm->change_parameters(-0.2,-1,-2.6,0,0,0);

	podshape(-2,-5,-1,green);
	vpod2 = new csX75::HNode(vpod2arm,12,v_positions,v_colors,sizeof(v_positions[0])*12,sizeof(v_positions[0])*12);
	vpod2->change_parameters(-2.8,0,0,0,0,0);

	//pod3
	colorcube(2.8,-0.4,0.4,red);
	vpod3arm = new csX75::HNode(vbody,36,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	vpod3arm->change_parameters(0.2,-1,-2.4,0,0,0);

	podshape(2,-5,1,green);
	vpod3 = new csX75::HNode(vpod3arm,12,v_positions,v_colors,sizeof(v_positions[0])*12,sizeof(v_positions[0])*12);
	vpod3->change_parameters(2.8,0,0,0,0,0);

	//pod4
	colorcube(2.8,-0.4,-0.4,red);
	vpod4arm = new csX75::HNode(vbody,36,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	vpod4arm->change_parameters(0.2,-1,-2.6,0,0,0);

	podshape(2,-5,-1,green);
	vpod4 = new csX75::HNode(vpod4arm,12,v_positions,v_colors,sizeof(v_positions[0])*12,sizeof(v_positions[0])*12);
	vpod4->change_parameters(2.8,0,0,0,0,0);


	centercube(0.4,0.8,0.2,red);
	vneck = new csX75::HNode(vbody,36,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	vneck->change_parameters(0,1.4,-2,0,0,0);
	
	centercube(1.2,1.2,0.2,blue);
	vhead = new csX75::HNode(vneck,36,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	vhead->change_parameters(0,1.0,0,0,0,0);
	// neckshape();
	// vneck = new csX75::HNode(vbody,36,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);

	// headshape();
	// vhead = new csX75::HNode(vneck,54,v_positions,v_colors,sizeof(v_positions[0])*54,sizeof(v_positions[0])*54);


	//c3po ----------------------------------------------------------------------------------//
	colorcube(1.5,3.0,1,red);
	chest = new csX75::HNode(NULL,num_vertices,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	chest->change_parameters(0,0,0,0,0,0);

	colorcube(0.5,2.0,1,red);
	rightUpperArm = new csX75::HNode(chest,num_vertices,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	rightUpperArm->change_parameters(1.6,3.1,0,0,0,0);

	rightLowerArm = new csX75::HNode(rightUpperArm, num_vertices, v_positions, v_colors, sizeof(v_positions[0])*36, sizeof(v_positions[0])*36);
	rightLowerArm->change_parameters(0,2.1,0,0,0,0);

	leftUpperArm = new csX75::HNode(chest,num_vertices,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	leftUpperArm->change_parameters(-0.6,3.1,0,0,0,0);	

	leftLowerArm = new csX75::HNode(leftUpperArm,num_vertices,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	leftLowerArm->change_parameters(0,2.1,0,0,0,0);	

	leftUpperLeg = new csX75::HNode(chest,num_vertices,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	leftUpperLeg->change_parameters(0,0,0,0,0,0);

	leftLowerLeg = new csX75::HNode(leftUpperLeg,num_vertices,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);;
	leftLowerLeg->change_parameters(0,2.1,0,0,0,0);
	
	leftUpperLeg->change_parameters(0.5,-0.1,0,0,0,180);
	
	rightUpperLeg = new csX75::HNode(chest,num_vertices,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	rightUpperLeg->change_parameters(0,0,0,0,0,0);

	rightLowerLeg = new csX75::HNode(rightUpperLeg,num_vertices,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);;
	rightLowerLeg->change_parameters(0,2.1,0,0,0,0);

	rightUpperLeg->change_parameters(1.5,-0.1,0,0,0,180);
	
	colorcube(1.5,1,1,red);
	head = new csX75::HNode(chest,num_vertices,v_positions,v_colors,sizeof(v_positions[0])*36,sizeof(v_positions[0])*36);
	head->change_parameters(0,3.1,0,0,0,0);
	//c3po ----------------------------------------------------------------------------//
}

void renderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	matrixStack.clear();

	//Creating the lookat and the up vectors for the camera
	c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
	c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
	c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

	glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
	glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
	//Creating the lookat matrix
	lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

	//creating the projection matrix
	if(enable_perspective)
		projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
		//projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
	else
		projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -5.0, 5.0);

	view_matrix = projection_matrix*lookat_matrix;

	matrixStack.push_back(view_matrix);

	vbody->render_tree();
	chest->render_tree();
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//This is for MacOSX - can be omitted otherwise
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	//We don't want the old OpenGL 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
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

	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
		{
			 
			// Render here
			renderGL();

			// Swap front and back buffers
			glfwSwapBuffers(window);
			
			// Poll for and process events
			glfwPollEvents();
		}
	
	glfwTerminate();
	return 0;
}

//-------------------------------------------------------------------------

