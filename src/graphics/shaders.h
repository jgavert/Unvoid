
#ifndef SHADERS_H
#define	SHADERS_H
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

class Shaders
{
public:
	Shaders(void);
	~Shaders(void);
	void loadShaders();
  GLint createShaders();
  void reload();
  void destroyShaders();
  GLuint VertexShaderId, FragmentShaderId, ProgramId;
private:
  std::string readShaderFile(std::string);
  std::string vertex;
  std::string fragment;
  std::vector<std::string> shaderSources;
  std::vector<GLint> shaders;
  std::vector<GLint> programs;
};


#endif	/* SHADERS_H */
