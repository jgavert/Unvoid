#include "taskbus.hpp"

TaskBus::TaskBus(std::shared_ptr<Renderer> renderer, std::shared_ptr<Controller> inpt):render(renderer), input(inpt)
{
}

TaskBus::~TaskBus()
{
}

void TaskBus::addHandler(std::function<void(const std::shared_ptr<Renderer> renderer,const std::shared_ptr<Controller> input)> fun);
{
  handlers.push_back(fun);
}

void tick()
{
  for (auto &it : handlers)
  {
    it(render, )
  }

}
