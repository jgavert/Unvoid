#include "particleManager.h"
#include <random>
#define WORK_GROUP_SIZE 128

ParticleManager::ParticleManager()
{
  numParticles = 1;
}

ParticleManager::ParticleManager(int particleCount)
{
  numParticles = particleCount;
}

ParticleManager::~ParticleManager()
{

  //glDeleteBuffers(1, &bufferID);
}

void ParticleManager::Initialize(int computeProgram)
{
  computeProg = computeProgram;
  uniOriginPoint = glGetUniformLocation(computeProg, "originPoint");
  uniTimeDiff = glGetUniformLocation(computeProg, "frameTimeDiff");
  uniParticleCount = glGetUniformLocation(computeProg, "maxParticles");

	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, numParticles*sizeof(Particle), NULL ,GL_STATIC_DRAW);

  particles = (struct Particle*) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, numParticles*sizeof(Particle), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

  std::mt19937 eng;
  std::uniform_real_distribution<float> dist(-10.0f,10.0f);
  std::uniform_real_distribution<float> dist2(0.0f,0.05f);
  std::uniform_real_distribution<float> dist3(0.f,750.f);

  for(int i = 0; i < numParticles; ++i){
    particles[i].currPosition = glm::vec4(0.f,4.f,0.0f,1.f);
    particles[i].speedVector = glm::normalize(glm::vec4(dist(eng), dist(eng), dist(eng), 0.0f)) * dist2(eng);
    particles[i].ttl = glm::mediump_float(5.0f);
  }

	if(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER) == GL_FALSE){
		std::cerr << "Could not unmap the shader storage buffer for particles!" << std::endl;
	}
}

void ParticleManager::Simulate(float time, glm::vec4 targetPos)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, bufferID);

  glUseProgram(computeProg);

  glUniform4fv(uniOriginPoint, 1,glm::value_ptr(targetPos));
  glUniform1fv(uniTimeDiff, 1, &time);
  glUniform1ui(uniParticleCount, numParticles);

  glDispatchCompute((numParticles/WORK_GROUP_SIZE)+1, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
}

GLuint ParticleManager::getBufferID()
{
  return bufferID;
}

int ParticleManager::getParticleCount()
{
  return numParticles;
}

