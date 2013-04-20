#include "vbo.h"
#include <iostream>

VBO::VBO()
{
  modelMatrix = viewMatrix = glm::mat4();
}

VBO::~VBO() {
	glDeleteBuffers( 1, &eboId );
	glDeleteBuffers( 1, &vboId );
	glDeleteVertexArrays( 1, &vaoId );
}

void VBO::loadToGpu() {
  GLenum ErrorCheckValue = glGetError();
  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);

  glEnableVertexAttribArray(0);
  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);         // for vertex coordinates
  glBufferData(GL_ARRAY_BUFFER, sizeof( float ) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  std::cout << "vertices size: " << vertices.size() << std::endl;


  glEnableVertexAttribArray(1);
  glGenBuffers(1, &colorBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof( float ) * colors.size(), colors.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
  std::cout << "colors size: " << colors.size() << std::endl;

  glGenBuffers(1, &eboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId); // for indices
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * indices.size(), indices.data(), GL_STATIC_DRAW );
  std::cout << "indices size: " << indices.size() << std::endl;

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "ERROR: Could not create a VBO: " << gluErrorString(ErrorCheckValue) << std::endl;
    exit(-1);
  }
  glBindVertexArray(0);
}

void VBO::draw() {
	glBindVertexArray(vaoId);
	glDrawElements( GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0 );
  glBindVertexArray(0);
}

glm::mat4 VBO::getModelMatrix() {
  return modelMatrix;
}


