/*
 * File:   Renderer.h
 * Author: juho
 *
 * Created on November 28, 2011, 1:15 PM
 */

#ifndef WORLD_H
#define	WORLD_H

#include <vector>
#include "WObject.h"

class World {
public:
  World();
  ~World();
  std::vector<WObject> objs;
  private:
};

#endif	/* RENDERER_H */
