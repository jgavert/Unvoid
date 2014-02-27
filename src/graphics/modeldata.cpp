#include "modeldata.hpp"


ModelData::ModelData(std::vector<float> verts,std::vector<float> colrs, std::vector<GLuint> inds):
  vertices(std::move(verts)), colors(std::move(colrs)), indices(std::move(inds)),
  vaoId(0), vboId(0), eboId(0), colorBufferId(0)
{
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

ModelData::~ModelData()
{
  glDeleteBuffers( 1, &colorBufferId);
  glDeleteBuffers( 1, &eboId );
  glDeleteBuffers( 1, &vboId );
  glDeleteVertexArrays( 1, &vaoId );
}


GLuint ModelData::getVaoID()
{
  return vaoId;
}
int ModelData::getSize()
{
  return vertices.size();
}
