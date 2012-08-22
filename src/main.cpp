
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

int main(void)
{
  auto time1 = getMilliSecs();
  Window window;
  Renderer render(window);
  Controller input;
  render.initialize();
  while(!input.hasQuit()) {
  	input.update();
  	render.render();
    auto time2 = getMilliSecs();
    if (time2 - time1 > 1000) {
      std::cout << render.getResetFrames() << std::endl;
      time1 = time2;
    }
  }
  exit(EXIT_SUCCESS);
}
