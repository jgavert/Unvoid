#include "shaders.h"

Shaders::Shaders(void)
{
}

Shaders::~Shaders(void)
{
}

//template<typename T, typename ...Args> std::unique_ptr<T> make_unique( Args&& ...args ) { return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) ); }

void Shaders::initialize(void)
{
  //debug for windows file management
  //remove after clear
  //local directory is the one where you run the main from
  //shaders.insert(std::make_pair<std::string,std::unique_ptr<ShaderUnit>>("Basic", std::unique_ptr<VFSUnit>(VFSUnit("Basic", "shaders/simple.vertex", "shaders/simple.vertex"))));
  auto p1 = std::unique_ptr<VFSUnit>(new VFSUnit("Basic", "shaders/simple.vertex", "shaders/simple.fragment"));
  shaders.insert( std::make_pair( std::string("Basic"), std::move(p1)));
  auto p2 = std::unique_ptr<VFSUnit>(new VFSUnit("PostProcess", "shaders/postprocess.vertex", "shaders/postprocess.fragment"));
  shaders.insert( std::make_pair( std::string("PostProcess"), std::move(p2)));
  auto p3 = std::unique_ptr<VFSUnit>(new VFSUnit("glsl", "shaders/simple.vertex", "shaders/glsl.fragment"));
  shaders.insert( std::make_pair( std::string("glsl"), std::move(p3)));
  //shaders.insert(std::make_pair<std::string,std::unique_ptr<ShaderUnit>>("PostProcess",std::unique_ptr<VFSUnit>(VFSUnit("PostProcess", "shaders/postprocess.vertex", "shaders/postprocess.fragment"))));
  for (auto& kv : shaders) {
    kv.second->load();
  }
}

GLuint Shaders::get(std::string name)
{
  return shaders.at(name)->pid();
}

void Shaders::update()
{
  for (auto& kv : shaders) {
    kv.second->reload();
  }
}

