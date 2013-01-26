#include "controller.h"

Controller::Controller(void) {
	keyboard = 0;
	quit = false;
	keys[0] = 1;
	for (int i=1;i<20;i++)
		keys[i] = keys[i-1] * 2;
}

Controller::~Controller(void) {
}

void Controller::update() {
	SDL_Event event;

  //SDL_GetMouseState(&mouse[0], &mouse[1]);
  SDL_GetRelativeMouseState(&mouse[0], &mouse[1]);
  //mouse[0] -=300;
  //mouse[1] -=300;

	while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
      	handleKeyDownEvent(event);
      	break;
     	case SDL_KEYUP:
     		handleKeyUpEvent(event);
     		break;
      /*case SDL_MOUSEMOTION:
        handleMouseMotionEvent(event);*/
      default:
        break;
    }
  }
  if (getKeyState(ESC))
  	quit = true;
}

bool Controller::hasQuit(void) {
	return quit;
}

void Controller::handleMouseMotionEvent(SDL_Event event)
{
  mouse[0] = event.motion.xrel;
  mouse[1] = event.motion.yrel;
  //std::cout << "mouse x: " << x << std::endl;


}

void Controller::handleKeyDownEvent(SDL_Event keyevent) {
	switch(keyevent.key.keysym.sym){
    case SDLK_ESCAPE:
    	keyboard |= 1;
      break;
    case SDLK_UP:
      keyboard |= 2;
      break;
    case SDLK_DOWN:
      keyboard |= 4;
      break;
    case SDLK_LEFT:
      keyboard |= 8;
      break;
    case SDLK_RIGHT:
      keyboard |= 16;
      break;
    case SDLK_w:
      keyboard |= 2;
      break;
    case SDLK_s:
      keyboard |= 4;
      break;
    case SDLK_a:
      keyboard |= 8;
      break;
    case SDLK_d:
      keyboard |= 16;
      break;
    case SDLK_3:
      keyboard |= keys[K3];
      break;
    case SDLK_1:
      keyboard |= keys[K1];
      break;
    case SDLK_2:
      keyboard |= keys[K2];
    default:
      break;
	}
}

void Controller::handleKeyUpEvent(SDL_Event keyevent) {
	switch(keyevent.key.keysym.sym){
    case SDLK_ESCAPE:
    	keyboard &= (~1);
      break;
    case SDLK_UP:
      keyboard &= (~2);
      break;
    case SDLK_DOWN:
      keyboard &= (~4);
      break;
    case SDLK_LEFT:
      keyboard &= (~8);
      break;
    case SDLK_RIGHT:
      keyboard &= (~16);
      break;
    case SDLK_w:
      keyboard &= (~2);
      break;
    case SDLK_s:
      keyboard &= (~4);
      break;
    case SDLK_a:
      keyboard &= (~8);
      break;
    case SDLK_d:
      keyboard &= (~16);
      break;
    case SDLK_3:
      keyboard &= (~keys[K3]);
      break;
    case SDLK_2:
      keyboard &= (~keys[K2]);
      break;
    case SDLK_1:
      keyboard &= (~keys[K1]);
    default:
      break;
	}
}

bool Controller::getKeyState(Key key)
{
	return (keyboard & keys[key]) != 0;
}

int* Controller::getRelativeMouseState()
{
  return mouse;
}

