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
#else
#include <GL/glew.h>
#endif

#include "window.h"
#include "shaders.h"
#include <vector>

class Renderer {
public:
  Renderer(Window& window);
  virtual ~Renderer();
  void initialize();
  virtual void render();
private:
  int CurrentWidth;
  int CurrentHeight;
  int WindowHandle;

  unsigned FrameCount;
  GLuint VaoId, VboId, ColorBufferId;
  Window& window;
  Shaders shaders;
  //TODO: implement below
  std::vector<int> screenStack;
  std::vector<GLuint> vbos, vaos, colorbufferids;
  //void onResize() ?

  void CreateVBO();
  void DestroyVBO();
  void Cleanup();
};

#endif	/* RENDERER_H */
