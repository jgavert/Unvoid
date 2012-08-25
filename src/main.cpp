
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "graphics/renderer.h"
#include "input/controller.h"

#include <sys/time.h>
#include <cmath>

inline long getMilliSecs() {
  timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec*1000 + t.tv_usec/1000;
}

float x=-4.f,y=0.f,z=0.f;
float tx=0.f,ty=0.f,tz=0.f;
float forward=0.f, strafe=0.f;
float zx_a=0.f, y_a=0.f;
int* mouse;
const float SPD = 0.05f;

void look(Renderer& render, Controller& input)
{
  forward = strafe = 0.f;

  if (input.getKeyState(UP))
    forward += SPD;
  if (input.getKeyState(DOWN))
    forward -= SPD;
  if (input.getKeyState(LEFT))
    strafe += SPD;
  if (input.getKeyState(RIGHT))
    strafe -= SPD;

  mouse = input.getRelativeMouseState();

  y_a += (float)mouse[1]*0.01f;
  zx_a += (float)mouse[0]*0.01f;

  tx = sinf(zx_a);
  tz = cosf(zx_a);
  //ty = sinf(y_a);




  render.lookAt(x, y, z, x+tx, y+ty, z+tz);
}

int main(void)
{
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
  window.enable_grab();
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
