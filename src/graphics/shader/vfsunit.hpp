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
  std::string name, FragFile, VertFile;
  GLuint VertexShaderId, FragmentShaderId, ProgramId;
};

