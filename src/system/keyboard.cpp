#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#ifdef _WIN32
#include <SDL.h>
#else
#include "sdl/SDL.h"
#endif
#include "keyboard.h"


Keyboard::Keyboard(void)
{
	 auto keyStates = SDL_GetKeyboardState;
     std::cout << keyStates << std::endl;
}


Keyboard::~Keyboard(void)
{
}

void Keyboard::info(void)
{
	//std::cout << keyStates << std::endl;
}
