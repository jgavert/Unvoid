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
	GLfloat	x,y,z;
	GLfloat	sx,sy,sz;
  GLfloat ttl;
};

#endif