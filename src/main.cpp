
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "graphics/renderer.h"
#include "input/controller.h"

int main(void)
{
  Window window;
  Renderer render(window);
  Controller input;
  render.initialize();
  while(!input.hasQuit()) {
  	input.update();
  	if (input.getKeyState(ESC))
  		break;
  	render.render();
  }
  exit(EXIT_SUCCESS);
}
