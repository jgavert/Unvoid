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
    default:
      break;
	}
}

bool Controller::getKeyState(Key key)
{
	return (keyboard & keys[key]) != 0;
}