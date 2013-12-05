#ifndef WObject_H
#define WObject_H

#include <vector>
#include "../graphics/vbo.h"

class WObject {
public:
  WObject();
  ~WObject();
  VBO vbo;
  float x,y,z;
  private:
};

#endif
