#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "graphics/renderer.h"
#include "system/keyboard.h"

int main(int argc, char* argv[])
{
  argc++;
  argv++;
  Keyboard keys;
  keys.info();
  Sleep(10000);
  exit(EXIT_SUCCESS);
  /*
  Window window;
  Renderer render(window);
  std::cerr << "woot" << std::endl;
  render.startLoop();
  for (int i=0; i<10; i++)
  std::cout << "zomg " << std::endl;
  exit(EXIT_SUCCESS);*/
}
