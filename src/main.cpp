#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "graphics/vbo.h"
#include "graphics/renderer.h"
#include "input/controller.h"
#include "utils/objloader.h"

//#include <sys/time.h>
#include <cmath>

#include <chrono>
#include <thread>

#define FPSLIMIT 16666667 //nanoseconds


float x=-4.f,y=0.f,z=0.f;
float tx=0.f,ty=0.f,tz=0.f;
float forward=0.f, strafe=0.f;
float zx_a=0.f, y_a=0.f;
int* mouse;
float SPD = 0.4f;
bool capturedMouse = false;

void look(Renderer& render, Controller& input, float speedMod)
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
  if (!capturedMouse) {
    mouse[0] = 0; mouse[1] = 0;
  }
//  std::cout << mouse[0] << std::endl;
//  std::cout << mouse[1] << std::endl;
  //if (mouse[1]+mouse[0] != 0)
  //{
  //  return;
  y_a += (float)mouse[1]*0.001f;
  zx_a += (float)mouse[0]*0.001f;
  if (y_a > 1.f) y_a = 1.f;
  if (y_a < -1.f) y_a = -1.f;
  //std::cout << "mouse[1]: " << mouse[1] << " ,y_a: " << y_a << ", acosf(y_a): " << acosf(y_a) << std::endl;
  tx = cosf(zx_a);
  tz = sinf(zx_a);
  ty = acosf(y_a) - 1.f;
//}
  //std::cout << "tx: " << tx << std::endl;
  //std::cout << "tz: " << tz << std::endl;
  float applySpeed = SPD*speedMod;
  x += (-tz)*applySpeed*strafe;
  x += tx*applySpeed*forward;
  //x += SPD*strafe*tz;
  y += ty*applySpeed*forward;
  z += tz*applySpeed*forward;
  z += tx*applySpeed*strafe;
  //z += SPD*strafe*tx;

//std::cout << x << ", " << tx << std::endl;
//std::cout << z << ", " << tz << std::endl;


  render.lookAt(x, y, z, x+tx, y+ty, z+tz);
}

int main(int argc, char *argv[])
{
  auto fpslimit = std::chrono::nanoseconds(FPSLIMIT);
  auto timing0 = std::chrono::high_resolution_clock::now();
  Window window;
  Renderer render(window);
  Controller input;
  Objloader lol;
  std::cout << "initializing\n";
  render.initialize();
  std::cout << "loading objects...\n";
  VBO vbo1 = lol.readObj("test.obj");
  render.loadVBO(vbo1);
  auto timing1 = std::chrono::high_resolution_clock::now();
  std::cout << "Initialisation took " << std::chrono::duration_cast<std::chrono::milliseconds>(timing1 - timing0).count() << "ms." << std::endl;
  timing0 = timing1;
  auto timing2 = std::chrono::high_resolution_clock::now();
  auto fbefore = 0;
  bool flip = true,limit = true, particlesEnabled = false, highspeed = true, fbo = true;
  auto timing3 = std::chrono::high_resolution_clock::now();

  while(!input.hasQuit()) {
    timing2 = std::chrono::high_resolution_clock::now();
    input.update();

    if (input.getKeyOnce(K1)) {
      if (flip) {
        window.enable_grab();
        flip = false;
        capturedMouse = true;
      } else {
        window.disable_grab();
        capturedMouse = false;
        flip = true;
      }
    }

    if (input.getKeyOnce(K2)) {
      //std::cout << "Reloading shaders..." << std::endl;
      //render.reloadShaders();
    }
    if (input.getKeyOnce(K3)) {
      limit = limit ? false : true;
      std::cout << "fpslimit " << (limit ? "on" : "off") << std::endl;
    }
    if (input.getKeyOnce(K4)) {
      particlesEnabled = particlesEnabled ? false : true;
      std::cout << "particles " << (particlesEnabled ? "on" : "off") << std::endl;
    }
    if (input.getKeyOnce(K5)) {
      window.toggle_fullscreen();
      std::cout << "Toggling fullscreen/windowed" << std::endl;
    }
    if (input.getKeyOnce(K6)) {
      SPD = highspeed ? 0.025f : 0.4f;
      highspeed = highspeed ? false : true;
      std::cout << "Movement speed "<< SPD << std::endl;
    }
    if (input.getKeyOnce(K7)) {
      fbo = fbo ? false : true;
      //window.toggle_vsync();
      std::cout << "Toggling FSQuad/postprocessing fbo: " << (fbo ? "on" : "off") << std::endl;
    }

    timing1 = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(timing1 - timing0).count() > 5000) {
      auto asd = render.getFrames();
      auto frames = asd - fbefore;
      std::cout << "fps " << (frames/5) << " per second"<< std::endl;
      timing0 = timing1;
      fbefore = asd;
    }
    long long currentframe  = std::chrono::duration_cast<std::chrono::nanoseconds>(timing1 - timing3).count();
    float speedMod = (float)currentframe / (float)FPSLIMIT;
    render.render(speedMod, particlesEnabled, fbo); //renders the scene
    look(render, input, speedMod); //where to look at
    timing3 = timing1;
    timing1 = std::chrono::high_resolution_clock::now();
    currentframe  = std::chrono::duration_cast<std::chrono::nanoseconds>(timing1 - timing2).count();
    //std::cout << lol << ", what?" << std::endl;
    if (limit)
      std::this_thread::sleep_for(std::chrono::nanoseconds(FPSLIMIT - currentframe));
    timing2 = timing1;
  }
  exit(EXIT_SUCCESS);
}
