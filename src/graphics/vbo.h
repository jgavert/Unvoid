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
#include <vector>

#ifndef VBO_H
#define	VBO_H

class VBO {
public:
	glm::mat4 modelMatrix,viewMatrix;
	GLuint vaoId, vboId, eboId, colorBufferId, shaderProgramId;
	//GLuint indices[36];
	//float vertices[32], colors[32];
	VBO();
	~VBO();
	void loadToGpu();
	void draw();
	glm::mat4 getModelMatrix();
private:
};

#endif
