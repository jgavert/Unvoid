#ifndef WINDOW_H
#define WINDOW_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <cstddef>

class Window
{
public:
	Window();
		~Window();

	size_t width() const;
	size_t height() const;

	//void toggle_fullscreen() const;
	void swap_buffers() const;
	/*void screenshot() const;*/

	void createWindow(int, int);
	/*
	void enable_grab() const;
	void disable_grab() const;

	bool active() const;
	void hide() const;*/
private:
	Window& operator=(const Window&); // Disabled.
	Window(const Window&); // Disabled.

	size_t width_;
	size_t height_;

	SDL_Window *mainwindow;
	SDL_GLContext drawContext;
	//SDL_Surface* drawContext;
};

#endif
