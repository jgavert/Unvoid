
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
  long timing[2];
  timing[0] = getMilliSecs();
  Window window;
  Renderer render(window);
  Controller input;
  render.initialize();
  timing[1] = getMilliSecs();
  std::cout << "Initialisation took " <<timing[1] - timing[0] << "ms." << std::endl;
  //unsigned asd = 0;
  timing[0] = timing[1];
  while(!input.hasQuit()) {
  	input.update();
   	render.render();
    timing[1] = getMilliSecs();

    if (timing[1] - timing[0] > 5000) {
      auto frames = render.getResetFrames();
      std::cout << frames/5 <<" FPS"<< std::endl;
      timing[0] = timing[1];
      /*++asd;
      if (asd == 5)
        break;*/
    }
  }
  exit(EXIT_SUCCESS);
}
