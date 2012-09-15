/*
 * File:   Renderer.cpp
 * Author: juho
 *
 * Created on November 28, 2011, 1:15 PM
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

#ifdef _WIN32
#include <GL\glew.h>
#else
#include <GL/glew.h>
#endif

#include "window.h"
#include "renderer.h"

Renderer::Renderer(Window& w):
	window(w)
{
  CurrentWidth = 800;
  CurrentHeight = 600;
  WindowHandle = 0;

  FrameCount = 0;
  window.createWindow(CurrentWidth, CurrentHeight);
}

Renderer::~Renderer() {
}

void Renderer::initialize()
{
  GLenum GlewInitResult;

  glewExperimental = GL_TRUE;
  GlewInitResult = glewInit();

  if (GLEW_OK != GlewInitResult) {
    std::cerr << "ERROR: %s" << glewGetErrorString(GlewInitResult) << std::endl << std::endl;
    exit(EXIT_FAILURE);
  }
  int OpenGLVersion[2];
  glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
  glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
  std::cout << "OpenGL major version = " << OpenGLVersion[0] << std::endl;
  std::cout << "OpenGL minor version = " << OpenGLVersion[1] << std::endl << std::endl;
  glClearColor(0.3f, 0.1f, 0.5f, 0.0f);

  glEnable( GL_DEPTH_TEST );
  //glDepthFunc(GL_LEQUAL);
  //glEnable( GL_CULL_FACE);
  //glCullFace(GL_BACK);
  //glFrontFace(GL_CCW);

  shaders.loadShaders();
  GLint shaderProgram = shaders.createShaders();
  glUseProgram(shaderProgram);
  viewMatrix = glGetUniformLocation( shaderProgram, "ViewMatrix" );
  projectionMatrix = glGetUniformLocation( shaderProgram, "ProjectionMatrix" );
  modelMatrix = glGetUniformLocation( shaderProgram, "ModelMatrix" );
  projection =view= glm::mat4();
  view = glm::lookAt(
    glm::vec3( -5.0f, 0.0f, -1.0f ), //missä olen
    glm::vec3( 0.0f, 0.0f, 0.0f ), //minne katon
    glm::vec3( 0.0f, 0.0f, 1.0f )  //vektori ylöspäin kamerasta
  );
  projection = glm::perspective( 45.0f, 800.0f / 600.0f, 1.0f, 100.0f );

  glUniformMatrix4fv( viewMatrix, 1, GL_FALSE, glm::value_ptr( view ) );
  glUniformMatrix4fv( projectionMatrix, 1, GL_FALSE, glm::value_ptr( projection ) );

  vbos.push_back(VBO());
  vbos[0].loadToGpu();
}



void Renderer::DestroyVBOs()
{
  GLenum ErrorCheckValue = glGetError();

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "ERROR: Could not destroy the VBO: " << gluErrorString(ErrorCheckValue)<< std::endl;
    exit(-1);
  }
}
void Renderer::Cleanup(void)
{
  shaders.destroyShaders();
  DestroyVBOs();
}

void Renderer::lookAt(float x, float y, float z, float tx, float ty, float tz)
{
  view = glm::lookAt(
    glm::vec3( x, y, z ), //missä olen
    glm::vec3( tx, ty, tz ), //minne katon
    glm::vec3( 0.0f, 1.0f, 0.0f )  //vektori ylöspäin kamerasta
  );
  glUniformMatrix4fv( viewMatrix, 1, GL_FALSE, glm::value_ptr( view ) );

}


void Renderer::render()
{
  ++FrameCount;

  glClearColor(0.3f, 0.1f, 0.5f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUniformMatrix4fv( modelMatrix, 1, GL_FALSE, glm::value_ptr( vbos[0].modelMatrix ) );
  vbos[0].modelMatrix = glm::rotate(
        vbos[0].modelMatrix,
        0.5f,
        glm::vec3( 0.0f, 0.0f, 1.0f )
      );
  vbos[0].draw();

  window.swap_buffers();
}

long long Renderer::getFrames()
{
  return FrameCount;
}
