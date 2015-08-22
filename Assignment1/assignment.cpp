#include "assignment.hpp"

GLuint shaderProgram;
GLuint vao;
GLuint verticesVbo, colorsVbo;

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

void renderGL(){
  // std::cout<<"CAME "<<std::endl;
  glGenBuffers (1, &verticesVbo);
  glBindBuffer (GL_ARRAY_BUFFER, verticesVbo);
  glBufferData (GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertexNo, vertices, GL_STATIC_DRAW);

  glGenBuffers (1, &colorsVbo);
  glBindBuffer (GL_ARRAY_BUFFER, colorsVbo);
  glBufferData (GL_ARRAY_BUFFER, sizeof(colors[0]) * vertexNo, colors, GL_STATIC_DRAW);

  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
  glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,NULL);
  glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
  glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,NULL);

  glEnableVertexAttribArray (0);
  glEnableVertexAttribArray (1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLE_FAN, 0, vertexNo);
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
  glfwSetMouseButtonCallback(window, csX75::mouse_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();
  bool tempBool = false;
  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
      renderGL();
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  
  glfwTerminate();
  // std:: cout<< intTemp << std::endl;
  return 0;
}