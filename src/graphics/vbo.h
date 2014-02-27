#ifdef _WIN32
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#else
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif
#include <vector>

#ifndef VBO_H
#define VBO_H

//TODO: introduce proper initializer list and make it more clean.
class VBO {
public:
  glm::mat4 modelMatrix,viewMatrix;
  GLuint vaoId, vboId, eboId, colorBufferId, shaderProgramId;

  std::vector<GLuint> indices;
  std::vector<float> vertices, colors;
  VBO();
  ~VBO();
  void loadToGpu();
  void draw();
  glm::mat4 getModelMatrix();
private:
};

#endif
