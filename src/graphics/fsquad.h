#ifndef _FSQUAD_
#define _FSQUAD_

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

class FSQuad{
public:
  FSQuad();
  FSQuad(int height, int width, int shaderProgram);
  ~FSQuad();
  void loadToGpu();
  void drawFBO();
  void drawToFBO();

  void reshape(int height, int width);

private:
  int screenHeight, screenWidth;
  glm::mat4 modelMatrix,viewMatrix;
  GLuint vaoId, vboId, eboId, shaderProgramId;
  GLuint fbo, fbo_texture, rbo_depth;
  GLint fbotextureUniLoc, v_coord_pos;
};


#endif