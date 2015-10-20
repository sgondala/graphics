#include "hierarchy_node.hpp"

#include <iostream>

extern GLuint vPosition,vColor,vNormal,uModelViewMatrix,normalMatrix;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec4* a_normals, std::size_t v_size, std::size_t c_size, std::size_t n_size){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		normal_buffer_size = n_size;
		// initialize vao and vbo of the object;

		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size+normal_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, normal_buffer_size, a_normals );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size+color_buffer_size));


		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;
		// sx=sy=sz=1;

		update_matrices();
	}

		plane::plane(glm::vec4 v0, glm::vec4 v1, glm::vec4 v2, glm::vec4 v3){

		vertices = new glm::vec4[6];
		colors = new glm::vec4[6];

		vertices[0] = v0;
		vertices[1] = v1;
		vertices[2] = v2;
		vertices[3] = v0;
		vertices[4] = v2;
		vertices[5] = v3;

		for(int i=0; i<6; i++){
			colors[i] = glm::vec4(1.0,0,0,1);
		}

		glGenVertexArrays(1,&vao);
		glGenBuffers(1,&vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER,vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*6 + sizeof(colors[0])*6, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices[0])*6, vertices);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices[0])*6, sizeof(colors[0])*6, colors);

		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices[0])*6));
	}

	plane::plane(glm::vec4* alpha){
		vertices = new glm::vec4[6];
		colors = new glm::vec4[6];
		normals = new glm::vec4[6];

		vertices[0] = alpha[0];
		vertices[1] = alpha[1];
		vertices[2] = alpha[2];
		vertices[3] = alpha[0];
		vertices[4] = alpha[2];
		vertices[5] = alpha[3];

		for(int i=0; i<6; i++){
			colors[i] = glm::vec4(1.0,0,0,1);
		}

		for(int i=0; i<6; i++){
			normals[i] = glm::vec4(0,0,-1,1);
		}

		glGenVertexArrays(1,&vao);
		glGenBuffers(1,&vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER,vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*6 + sizeof(colors[0])*6 + sizeof(normals[0])*6, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices[0])*6, vertices);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices[0])*6, sizeof(colors[0])*6, colors);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices[0])*6 + sizeof(colors[0])*6, sizeof(normals[0])*6, normals);

		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices[0])*6));
	
		glEnableVertexAttribArray(vNormal);
		glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET( sizeof(vertices[0])*6 + sizeof(colors[0])*6));
	}

	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));
		// scale = glm::scale(glm::mat4(1.0f),glm::vec3(sx,sy,sz));

	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, 
		GLfloat arx, GLfloat ary, GLfloat arz){
		// GLfloat asx, GLfloat asy, GLfloat asz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;
		// sx = asx;
		// sy = asy;
		// sz = asz;
		update_matrices();
	}

	void HNode::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
 		glm::mat3 normal_matrix = glm::transpose (glm::inverse(glm::mat3(*ms_mult)));
  		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  
		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void plane::render(glm::mat4* modelViewMatrix){
		// std::cout<<"!"<<std::endl;
		// glm::mat4 alpha(1.0f);
		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*modelViewMatrix));
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// std::cout<<"#!"<<std::endl;
	}

	void HNode::render_tree(){
		
		// matrixStack.push_back(scale);
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();
		// matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		rx++;
		update_matrices();
	}


	void HNode::inc_ry(){
		ry++;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz++;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx--;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry--;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz--;
		update_matrices();
	}

	void HNode::inc_tx(bool direction){
		if(direction){
			tx++;
		}
		else{
			tx--;
		}
		update_matrices();
	}

	void HNode::inc_ty(bool direction){
		if(direction){
			ty++;
		}
		else{
			ty--;
		}
		update_matrices();
	}

	void HNode::inc_tz(bool direction){
		if(direction){
			tz++;
		}
		else{
			tz--;
		}
		update_matrices();
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}