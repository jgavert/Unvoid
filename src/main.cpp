
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
const float SPD = 0.15f;

void look(Renderer& render, Controller& input)
{
  forward = strafe = 0.f;

  if (input.getKeyState(UP))
    forward += SPD;
  if (input.getKeyState(DOWN))
    forward -= SPD;
  if (input.getKeyState(LEFT))
    strafe -= SPD;
  if (input.getKeyState(RIGHT))
    strafe += SPD;

  mouse = input.getRelativeMouseState();
//  std::cout << mouse[0] << std::endl;
//  std::cout << mouse[1] << std::endl;
  //if (mouse[1]+mouse[0] == 0)
  //  return;
  y_a += (float)mouse[1]*0.001f;
  zx_a += (float)mouse[0]*0.001f;
  //std::cout << "zx_a: " << zx_a << std::endl;
  tx = cosf(zx_a);
  tz = sinf(zx_a);
  ty = -y_a;

  //std::cout << "tx: " << tx << std::endl;
  //std::cout << "tz: " << tz << std::endl;
  x += (-tz)*SPD*strafe;
  x += tx*SPD*forward;
  //x += SPD*strafe*tz;
  y += ty*SPD*forward;
  z += tz*SPD*forward;
  z += tx*SPD*strafe;
  //z += SPD*strafe*tx;

//std::cout << x << ", " << tx << std::endl;
//std::cout << z << ", " << tz << std::endl;


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
  bool flip = true, clicked = false;
  while(!input.hasQuit()) {
    input.update();

    // Enable/Disable keygrab
    if (input.getKeyState(K1))
    {
      if (!clicked)
      {
        if (flip)
        {
          window.enable_grab();
          flip = false;
        }
        else{
          window.disable_grab();
          flip = true;
        }
        clicked = true;
      }
    }
    else {
      clicked = false;
    }
    // grab ends

    look(render, input); //where to look at

    render.render(); //renders the scene

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
