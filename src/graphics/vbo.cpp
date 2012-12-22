#include "vbo.h"
#include <iostream>

VBO::VBO():
	indices{
    0,2,1, 0,3,2,
    4,3,0, 4,7,3,
    4,1,5, 4,0,1,
    3,6,2, 3,7,6,
    1,6,5, 1,2,6,
    7,5,6, 7,4,5
	},
  vertices{
   -1.0f, -1.0f,  1.0f, 1.0f,
   -1.0f,  1.0f,  1.0f, 1.0f,
    1.0f,  1.0f,  1.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 1.0f,
   -1.0f, -1.0f, -1.0f, 1.0f,
   -1.0f,  1.0f, -1.0f, 1.0f,
    1.0f,  1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 1.0f
  },
  colors{
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f
  }
{
  modelMatrix = viewMatrix = glm::mat4();
}

VBO::~VBO() {
	glDeleteBuffers( 1, &eboId );
	glDeleteBuffers( 1, &vboId );
	glDeleteVertexArrays( 1, &vaoId );
}

void VBO::loadToGpu()
{
  GLenum ErrorCheckValue = glGetError();
  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);

  glEnableVertexAttribArray(0);
  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);         // for vertex coordinates
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);


  glEnableVertexAttribArray(1);
  glGenBuffers(1, &colorBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glGenBuffers(1, &eboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId); // for indices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "ERROR: Could not create a VBO: " << gluErrorString(ErrorCheckValue) << std::endl;
    exit(-1);
  }
}

void VBO::draw()
{
	glBindVertexArray(vaoId);
	// bind VBOs for vertex array and index array
	glBindBuffer(GL_ARRAY_BUFFER, vboId);         // for vertex coordinates
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId); // for indices
	glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
}

glm::mat4 VBO::getModelMatrix()
{
  return modelMatrix;
}


