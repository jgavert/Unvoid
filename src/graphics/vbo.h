#ifdef _WIN32
#include <GL\glew.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef VBO_H
#define	VBO_H

class VBO {
public:
	int modelMatrix,viewMatrix;
	GLuint vaoId, vboId, colorBufferId, shaderProgramId;
	glm::mat4 vertices, colors, indices;
	VBO();
	~VBO();
private:
};

#endif
