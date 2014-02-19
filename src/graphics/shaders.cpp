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
  addProgram("Basic", "shaders/simple.vertex", "shaders/simple.fragment");
  addProgram("PostProcess", "shaders/postprocess.vertex", "shaders/postprocess.fragment");
  addProgram("glsl", "shaders/simple.vertex", "shaders/glsl.fragment");
  for (auto& kv : shaders) {
    kv.second->load();
  }
}

GLuint Shaders::get(std::string name)
{
  return shaders.at(name)->pid();
}

void Shaders::addProgram(std::string name, std::string vertex, std::string fragment)
{
  auto p1 = std::unique_ptr<VFSUnit>(new VFSUnit(name, vertex, fragment));
  shaders.insert( std::make_pair( name, std::move(p1)));
  filewatchlist.insert( std::make_pair(fwatcher.add(vertex), name));
  filewatchlist.insert( std::make_pair(fwatcher.add(fragment), name));
  //shaders.insert(std::make_pair<std::string,std::unique_ptr<ShaderUnit>>("PostProcess",std::unique_ptr<VFSUnit>(VFSUnit("PostProcess", "shaders/postprocess.vertex", "shaders/postprocess.fragment"))));
}

void Shaders::update()
{
  if (fwatcher.update()) {
    auto queue = fwatcher.getChanged();
    for (auto& i : queue) {
      shaders.at(filewatchlist.at(i))->reload();
    }
  }
}

