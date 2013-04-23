#include "fsquad.h"
#include <iostream>

FSQuad::FSQuad()
{
  modelMatrix = viewMatrix = glm::mat4();
  screenHeight = 1;
  screenWidth = 1;
  shaderProgramId = 0;
}


FSQuad::FSQuad(int height, int width, int shaderProgram)
{
  modelMatrix = viewMatrix = glm::mat4();
  screenHeight = height;
  screenWidth = width;
  shaderProgramId = shaderProgram;
}

FSQuad::~FSQuad() {
  glDeleteRenderbuffers(1, &rbo_depth);
  glDeleteTextures(1, &fbo_texture);
  glDeleteFramebuffers(1, &fbo);
	glDeleteBuffers( 1, &eboId );
	glDeleteBuffers( 1, &vboId );
	glDeleteVertexArrays( 1, &vaoId );
}

void FSQuad::loadToGpu() {
  GLenum ErrorCheckValue = glGetError();
  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);

  float vertices[16] = {-1.0f, -1.0f,  0.0f, 1.0f,
                        -1.0f,  1.0f,  0.0f, 1.0f,
                         1.0f,  1.0f,  0.0f, 1.0f,
                         1.0f, -1.0f,  0.0f, 1.0f};

  GLuint indices[6] = {0, 2, 1,
                       0, 3, 2};

  glEnableVertexAttribArray(0);
  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);         // for vertex coordinates
  glBufferData(GL_ARRAY_BUFFER, sizeof( float ) * 16, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glGenBuffers(1, &eboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId); // for indices
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * 6, indices, GL_STATIC_DRAW );

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "ERROR: Could not create a VBO: " << gluErrorString(ErrorCheckValue) << std::endl;
    exit(-1);
  }
  glBindVertexArray(0);

  /* Texture */
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &fbo_texture);
  glBindTexture(GL_TEXTURE_2D, fbo_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);

  /* Depth buffer */
  glGenRenderbuffers(1, &rbo_depth);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, screenWidth, screenHeight);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
 
  /* Framebuffer to link everything together */
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  fbotextureUniLoc = glGetAttribLocation(shaderProgramId, "fbo_texture");
}

void FSQuad::drawFBO() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glUseProgram(shaderProgramId);
  glClearColor(0.f, 1.f, 0.f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUniform1i(fbotextureUniLoc, 0);
  glBindTexture(GL_TEXTURE_2D, fbo_texture);

	glBindVertexArray(vaoId);
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
  glBindVertexArray(0);

  glUseProgram(0);
}

void FSQuad::drawToFBO() {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FSQuad::reshape(int height, int width)
{
  screenHeight = height, screenWidth = width;
  // Rescale FBO and RBO as well
  glBindTexture(GL_TEXTURE_2D, fbo_texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);
 
  glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, screenWidth, screenHeight);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}


