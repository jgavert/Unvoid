#ifndef _PARTICLEMANAGER_
#define _PARTICLEMANAGER_
#ifdef _WIN32
#include <GL\glew.h>
#else
#include <GL/glew.h>
#endif
#include <iostream>
#include "particle.h"

class ParticleManager{
public:
  ParticleManager();
  ParticleManager(int);
  ~ParticleManager();
  void Initialize(int);
  void Simulate(float, glm::vec4);
  GLuint getBufferID();
  int getParticleCount();
private:
  GLuint bufferID;
  int numParticles;
  struct Particle* particles;
  int computeProg, uniOriginPoint, uniTimeDiff, uniParticleCount;
};

#endif