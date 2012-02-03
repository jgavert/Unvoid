#pragma once

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

