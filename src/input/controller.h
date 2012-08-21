#ifndef CONTROLLER_H
#define	CONTROLLER_H
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL2/SDL.h"
#endif

enum Key { ESC, UP, DOWN, LEFT, RIGHT, SPACE, ENTER, K1, K2, K3, K4, K5, K6, K7, K8, K9, K0 };
class Controller
{
public:
	Controller(void);
	~Controller(void);
	void update();
	bool hasQuit(void);
	void handleKeyDownEvent(SDL_Event keyevent);
	void handleKeyUpEvent(SDL_Event keyevent);
	bool getKeyState(Key key);
private:
	int keys[100];
	bool quit;
	int keyboard;
};

#endif	/* CONTROLLER_H */
