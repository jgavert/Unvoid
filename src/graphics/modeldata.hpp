#pragma once

#ifdef _WIN32
#include <GL\glew.h>
#else
#include <GL/glew.h>
#endif
#include <vector>
#include <iostream>
#include <cstdlib>


class ModelData
{
public:
  ModelData(std::vector<float> vertices,std::vector<float> colors, std::vector<GLuint> indices);
  ~ModelData();
  GLuint getVaoID();
  int getSize();

private:
  GLuint vaoId, vboId, eboId, colorBufferId;

  std::vector<GLuint> indices;
  std::vector<float> vertices, colors;
};



