#ifndef SHADERS_H
#define SHADERS_H
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#ifdef _WIN32
#include <SDL.h>
#include <GL\glew.h>
#else
#include <SDL2/SDL.h>
#include <GL/glew.h>
#endif
#include <map>
#include <memory>
#include "shader/vfsunit.hpp"

class Shaders
{
public:
  Shaders();
  ~Shaders();
  void initialize();
  void update();
  GLuint get(std::string name);
private:
  std::map<std::string, std::unique_ptr<ShaderUnit>> shaders;
};


#endif	/* SHADERS_H */
