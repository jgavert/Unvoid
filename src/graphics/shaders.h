#ifndef SHADERS_H
#define SHADERS_H
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <memory>
#include "shader/vfsunit.hpp"
#include "../utils/filewatch.hpp"
#ifdef _WIN32
#include <SDL.h>
#include <GL\glew.h>
#else
#include <SDL2/SDL.h>
#include <GL/glew.h>
#endif

class Shaders
{
public:
  Shaders();
  ~Shaders();
  void initialize();
  void update();
  GLuint get(std::string name);
private:
  void addProgram(std::string name, std::string vertex, std::string fragment);
  std::map<std::string, std::unique_ptr<ShaderUnit>> shaders;
  std::map<int, std::string> filewatchlist;
  FileWatch fwatcher;
};


#endif	/* SHADERS_H */
