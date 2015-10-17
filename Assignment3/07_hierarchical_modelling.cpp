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
glm::vec4 positions[8];

//RGBA colors
glm::vec4 colors[8] = { 
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0)

};

int tri_idx=0;
glm::vec4 v_positions[num_vertices];
glm::vec4 v_colors[num_vertices];

// quad generates two triangles for each face and assigns colors to the vertices
void quad(int a, int b, int c, int d)
{
	v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
	v_colors[tri_idx] = colors[b]; v_positions[tri_idx] = positions[b]; tri_idx++;
	v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
	v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
	v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
	v_colors[tri_idx] = colors[d]; v_positions[tri_idx] = positions[d]; tri_idx++;
 }

// generate 12 triangles: 36 vertices and 36 colors
void colorcube(GLfloat xDim, GLfloat yDim)
{
	tri_idx = 0;
	positions[0] = glm::vec4(0,0,1,1);
	positions[1] = glm::vec4(0,yDim,1,1);
	positions[2] = glm::vec4(xDim,yDim,1,1);
	positions[3] = glm::vec4(xDim,0,1,1);
	positions[4] = glm::vec4(0,0,0,1);
	positions[5] = glm::vec4(0,yDim,0,1);
	positions[6] = glm::vec4(xDim,yDim,0,1);
	positions[7] = glm::vec4(xDim,0,0,1);		
	quad( 1, 0, 3, 2 );
	quad( 2, 3, 7, 6 );
	quad( 3, 0, 4, 7 );
	quad( 6, 5, 1, 2 );
	quad( 4, 5, 6, 7 );
	quad( 5, 4, 0, 1 );
}


//-----------------------------------------------------------------

void initBuffersGL(void)
{

	// Load shaders and use the resulting shader program
	std::string vertex_shader_file("07_vshader.glsl");
	std::string fragment_shader_file("07_fshader.glsl");

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	shaderProgram = csX75::CreateProgramGL(shaderList);
	glUseProgram( shaderProgram );

	// getting the attributes from the shader program
	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

	// Creating the hierarchy:
	// We are using the original colorcube function to generate the vertices of the cuboid

	//note that the buffers are initialized in the respective constructors
 
	colorcube(1.5,3.0);
	chest = new csX75::HNode(NULL,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
	chest->change_parameters(0,0,0,0,0,0);

	colorcube(0.5,2.0);
	rightUpperArm = new csX75::HNode(chest,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
	rightUpperArm->change_parameters(1.6,3.1,0,0,0,0);

	rightLowerArm = new csX75::HNode(rightUpperArm, num_vertices, v_positions, v_colors, sizeof(v_positions), sizeof(v_colors));
	rightLowerArm->change_parameters(0,2.1,0,0,0,0);

	leftUpperArm = new csX75::HNode(chest,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
	leftUpperArm->change_parameters(-0.6,3.1,0,0,0,0);	

	leftLowerArm = new csX75::HNode(leftUpperArm,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
	leftLowerArm->change_parameters(0,2.1,0,0,0,0);	

	leftUpperLeg = new csX75::HNode(chest,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
	leftUpperLeg->change_parameters(0,0,0,0,0,0);

	leftLowerLeg = new csX75::HNode(leftUpperLeg,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));;
	leftLowerLeg->change_parameters(0,2.1,0,0,0,0);
	
	leftUpperLeg->change_parameters(0.5,-0.1,0,0,0,180);
	
	rightUpperLeg = new csX75::HNode(chest,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
	rightUpperLeg->change_parameters(0,0,0,0,0,0);

	rightLowerLeg = new csX75::HNode(rightUpperLeg,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));;
	rightLowerLeg->change_parameters(0,2.1,0,0,0,0);

	rightUpperLeg->change_parameters(1.5,-0.1,0,0,0,180);
	
	colorcube(1.5,1);
	head = new csX75::HNode(chest,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
	head->change_parameters(0,3.1,0,0,0,0);

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

