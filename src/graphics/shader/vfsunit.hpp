#pragma once
#include "shaderunit.hpp"
#include <string>
#include <vector>
#include <iostream>
#ifdef _WIN32
#include <SDL.h>
#include <GL\glew.h>
#else
#include <SDL2/SDL.h>
#include <GL/glew.h>
#endif
#include "shaderparser.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/inotify.h>
#include <time.h>
#include <unistd.h>

// Vertex Fragment Shader Unit
class VFSUnit : public ShaderUnit
{
public:
  VFSUnit(std::string programName, std::string VertexFile, std::string FragmentFile);
  virtual ~VFSUnit();
  virtual void load();
  virtual void reload();
  virtual GLuint pid();
private:
  void update();
  fd_set watch_set;
  struct timespec req;
  int wd, fd;
  int frag_mtime, vert_mtime;
  std::string name, FragFile, VertFile;
  GLuint VertexShaderId, FragmentShaderId, ProgramId;
};

