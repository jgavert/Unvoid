
#ifndef SHADERS_H
#define	SHADERS_H
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#ifdef _WIN32
#include <SDL.h>
#include <GL\glew.h>
#else
#include "SDL2/SDL.h"
#include "GL/glew.h"
#endif

class Shaders
{
public:
	Shaders(void);
	~Shaders(void);
	void loadShaders();
  GLint createShaders();
  void destroyShaders();
private:
  GLuint VertexShaderId, FragmentShaderId, ProgramId;
  std::string readShaderFile(std::string);
  std::string vertex;
  std::string fragment;
};


#endif	/* SHADERS_H */