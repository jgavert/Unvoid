#pragma once
#ifndef WObject_H
#define WObject_H

#include <string>
#ifdef _WIN32
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#else
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif


// TODO: need a object that physics and model
class WObject { //ghetto object... something temporary for generic objects...
public:
  WObject(int modelID, std::string shader);
  ~WObject();
  std::string getShaderName();
  int getModelID();

  glm::vec3 pos;
  glm::mat4 modelMatrix;
  private:
  std::string shadername;
  int model;
};

#endif
