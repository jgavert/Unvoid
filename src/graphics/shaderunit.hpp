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
  virtual ~ShaderUnit();
  virtual void load();
  virtual void reload();
  virtual GLuint pid();
};

