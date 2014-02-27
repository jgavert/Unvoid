#include "WObject.h"

WObject::WObject(int modelID, std::string shader):
  model(modelID), shadername(shader), modelMatrix(glm::mat4()), pos(glm::vec3())
{
}
WObject::~WObject() {
}

std::string getShaderName()
{
  return shadername;
}
int getModelID()
{
  return model;
}
