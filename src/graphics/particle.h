#ifndef _PARTICLE_
#define _PARTICLE_

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

struct Particle{
	glm::vec4	currPosition;
	glm::vec4	speedVector;
  glm::mediump_float ttl;
};

#endif