
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "graphics/renderer.h"

int main(int argc, char* argv[])
{
  argc++;
  argv++;
  Window window;
  Renderer render(window);
  std::cerr << "woot";
  render.startLoop();
  for (int i=0; i<10; i++)
  std::cout << "zomg ";
  exit(EXIT_SUCCESS);
}
