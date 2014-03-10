#ifndef WINDOW_H
#define WINDOW_H

#ifdef _WIN32
#include <windows.h>
#include <SDL.h>
#include <GL\glew.h>
#else
#include <SDL2/SDL.h>
#include <GL/glew.h>
#endif

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iomanip>
#include <stdexcept>
#include <cstddef>

class Window
{
public:
	Window();
		~Window();

	size_t width() const;
	size_t height() const;

	void toggle_fullscreen();
	void swap_buffers() const;
	/*void screenshot() const;*/

	void createWindow(int, int);
	void enable_grab();
	void disable_grab();
  void toggle_vsync();
/*
	bool active() const;
	void hide() const;*/
private:
	Window& operator=(const Window&); // Disabled.
	Window(const Window&); // Disabled.

	size_t width_;
	size_t height_;

	SDL_Window *mainwindow;
	SDL_GLContext drawContext;
	bool grab, fullscreen, vsync;
	//SDL_Surface* drawContext;
};

#endif
