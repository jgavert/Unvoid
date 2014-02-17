#pragma once

#ifdef _WIN32
#include <SDL.h>
#include <GL\glew.h>
#else
#include <SDL2/SDL.h>
#include <GL/glew.h>
#endif

class ShaderUnit
{
public:
  virtual ~ShaderUnit() {};
  virtual void load() = 0;
  virtual void reload() = 0;
  virtual GLuint pid() = 0;
};

