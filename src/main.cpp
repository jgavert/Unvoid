
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "graphics/renderer.h"
#include "input/controller.h"

#include <sys/time.h>

inline long getMilliSecs() {
  timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec*1000 + t.tv_usec/1000;
}

float x,y,z;
const float SPD = 0.05f;
void look(Renderer& render, Controller& input)
{

  if (input.getKeyState(UP))
    z += SPD;
  if (input.getKeyState(DOWN))
    z -= SPD;
  if (input.getKeyState(LEFT))
    x += SPD;
  if (input.getKeyState(RIGHT))
    x -= SPD;

  render.lookAt(x, 0.f, z, 0.f, 0.f);
}

int main(void)
{
  x=y=z =0.f;
  long timing[2];
  timing[0] = getMilliSecs();
  Window window;
  Renderer render(window);
  Controller input;
  render.initialize();
  timing[1] = getMilliSecs();
  std::cout << "Initialisation took " << timing[1] - timing[0] << "ms." << std::endl;
  timing[0] = timing[1];
  auto fbefore = 0;
  while(!input.hasQuit()) {
  	input.update();
    look(render, input);
   	render.render();
    timing[1] = getMilliSecs();
    if (timing[1] - timing[0] > 5000) {
      auto asd = render.getFrames();
      auto frames = asd - fbefore;
      std::cout << frames/5 << " FPS" << std::endl;
      timing[0] = timing[1];
      fbefore = asd;
    }
  }
  exit(EXIT_SUCCESS);
}
