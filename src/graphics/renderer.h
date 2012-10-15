/*
 * File:   Renderer.h
 * Author: juho
 *
 * Created on November 28, 2011, 1:15 PM
 */

#ifndef RENDERER_H
#define	RENDERER_H
#define WINDOW_TITLE_PREFIX "Project Unvoid"

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


#include "window.h"
#include "shaders.h"
#include "vbo.h"
#include <vector>

class Renderer {
public:
  Renderer(Window& window);
  virtual ~Renderer();
  void initialize();
  virtual void render();
  virtual void lookAt(float, float, float, float, float, float);
  long long getFrames();
  void reloadShaders();
private:
  int CurrentWidth;
  int CurrentHeight;
  int WindowHandle;

  long long FrameCount;
  GLfloat timeGLV;
  Window& window;
  Shaders shaders;
  glm::mat4 view, projection;
  GLint viewMatrix, projectionMatrix, modelMatrix, timeGLP, resolutionGLP;
  //TODO: implement below
  std::vector<int> screenStack;
  std::vector<VBO> vbos;
  //void onResize() ?

  void DestroyVBOs();
  void Cleanup();
};

#endif	/* RENDERER_H */
