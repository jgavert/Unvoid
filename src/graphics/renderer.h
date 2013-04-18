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

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>

#include "window.h"
#include "shaders.h"
#include "vbo.h"

class Renderer {
public:
  Renderer(Window& window);
  ~Renderer();
  void initialize();
  void render(float time);
  void lookAt(float, float, float, float, float, float);
  long long getFrames();
  void reloadShaders();
  void loadObject(std::string);
private:
  int CurrentWidth;
  int CurrentHeight;
  int WindowHandle;

  long long FrameCount;
  GLfloat timeGLV;
  Window& window;
  Shaders shaders;
  glm::mat4 view, projection;
  GLint viewMatrix, projectionMatrix, modelMatrix, timeGLP, resolutionGLP, cameraPosGLP;
  //TODO: implement below
  std::vector<int> screenStack;
  std::vector<VBO> vbos;
  //void onResize() ?

  void DestroyVBOs();
  void Cleanup();
};

#endif	/* RENDERER_H */
