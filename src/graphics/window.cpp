#include "window.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#ifdef _WIN32
#include <GL\glew.h>
#else
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

using namespace std;

void checkForGLError2(std::string info)
{
  GLenum ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "GL_ERROR \"" << info << "\":" << gluErrorString(ErrorCheckValue) << std::endl;
    //exit(-1);
  }
}

Window::Window()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "ERROR: SDL init failed." << endl;
		throw std::string("Unable to init SDL");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
}

Window::~Window()
{
	SDL_Quit();
}

void Window::createWindow(int width, int height)
{
	assert(width   >   10);
	assert(width  <= 4096);
	assert(height  >   10);
	assert(height <= 4096);

	width_  = width;
	height_ = height;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
  //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,2);
  fullscreen = false;
	mainwindow = SDL_CreateWindow("woot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(!mainwindow)
	{
		cerr << "ERROR: drawContext = " << drawContext << endl;
		throw std::runtime_error("Unable to set SDL video mode");
	}
  drawContext = SDL_GL_CreateContext(mainwindow);
}

size_t Window::width() const
{
	return width_;
}

size_t Window::height() const
{
	return height_;
}

void Window::toggle_vsync() {
  if (!vsync) {
    SDL_GL_SetSwapInterval(1); //probably doesnt work
    vsync = true;
  } else {
    SDL_GL_SetSwapInterval(0);
    vsync = false;
  }
}

void Window::toggle_fullscreen()
{
  if (fullscreen) {
    SDL_SetWindowFullscreen(mainwindow, SDL_FALSE);
    fullscreen = false;
  } else {
    SDL_SetWindowFullscreen(mainwindow, SDL_TRUE);
    fullscreen = true;
  }
}

void Window::swap_buffers() const
{
	//if (grab)
	//	SDL_WarpMouseInWindow(mainwindow, 300, 300);
	SDL_GL_SwapWindow(mainwindow);
}
/*
std::string next_screenshot_filename()
{
	static int next = 0;

	string filename;
	do
	{
		stringstream ss;
		ss << "screenshots/screenshot" << setw(3) << setfill('0') << next << ".bmp";
		filename = ss.str();
		++next;
	}
	while(ifstream(filename));

	return filename;
}

void Window::screenshot() const
{
	std::string filename = next_screenshot_filename();

	SDL_Surface* screen = drawContext;
	SDL_Surface* temp = 0;

	if(!(screen->flags & SDL_OPENGL))
	{
		cerr << "Weird, saving non-opengl screenshot to '" << filename << "'?" << endl;
		SDL_SaveBMP(screen, filename.c_str());
		return;
	}

	vector<unsigned char> pixels(3 * screen->w * screen->h);

	temp = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 24,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
			0x000000FF, 0x0000FF00, 0x00FF0000, 0
#else
			0x00FF0000, 0x0000FF00, 0x000000FF, 0
#endif
			);
	if(!temp)
	{
		cerr << "ERROR: screenshot failed" << endl;
		return;
	}

	glReadPixels(0, 0, screen->w, screen->h, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);

	for(int i = 0; i < screen->h; ++i)
	{
		memcpy(((char *) temp->pixels) + temp->pitch * i, &pixels[0] + 3*screen->w * (screen->h-i-1), screen->w*3);
	}

	cerr << "Saving screenshot to '" << filename << "'" << endl;
	SDL_SaveBMP(temp, filename.c_str());

	SDL_FreeSurface(temp);
}*/


void Window::enable_grab()
{
	grab = true;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_SetWindowGrab(mainwindow, SDL_TRUE);
	SDL_ShowCursor(0);
}

void Window::disable_grab()
{
	grab = false;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_SetWindowGrab(mainwindow, SDL_FALSE);
	SDL_ShowCursor(1);
}
/*
bool Window::active() const
{
	return SDL_GetAppState() & SDL_APPACTIVE;
}

void Window::hide() const
{
	disable_grab();
	SDL_WM_IconifyWindow();
}
*/
