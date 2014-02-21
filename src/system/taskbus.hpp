#pragma once
#include "../graphics/renderer.h"
#include "../input/controller.h"
#include <vector>

class TaskBus
{
public:
  TaskBus(std::shared_ptr<Renderer> renderer, std::shared_ptr<Controller> inpt);
  ~TaskBus();
  void addHandler(std::function<void(const std::shared_ptr<Renderer> renderer,const std::shared_ptr<Controller> input)> fun);
  void tick();
private:
  std::shared_ptr<Renderer> render;
  std::shared_ptr<Controller> input;
  std::vector<std::function<void(const std::shared_ptr<Renderer> renderer,const std::shared_ptr<Controller> input)>> handlers;
};
