/* 
 * File:   Renderer.cpp
 * Author: juho
 * 
 * Created on November 28, 2011, 1:15 PM
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <GL/glew.h>
#include <SFML/System.hpp>
#include "Renderer.h"
#include "opengl.h"
#include "window.h"

Renderer::Renderer(Window& w):
	window(w)
{
    CurrentWidth = 800;
    CurrentHeight = 600; 
    WindowHandle = 0;

    FrameCount = 0;
    window.createWindow(800, 600);
}

/*TODO: WHAT THE FUCK!?
Renderer::Renderer(const Renderer& orig) {
    orig.
}*/

Renderer::~Renderer() {
}

void Renderer::startLoop()
{
    Initialize();
    //glutMainLoop();
}

void Renderer::Initialize()
{
	GLenum GlewInitResult;

        window.createWindow(800, 600);
        glewExperimental=true;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) {
		std::cerr << "ERROR: %s\n" << glewGetErrorString(GlewInitResult)<< std::endl;
		exit(EXIT_FAILURE);
	}
        int OpenGLVersion[2];
	//std::cout << "INFO: OpenGL Version: %s\n" << glGetString(GL_VERSION) << std::endl;
        glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
        glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
        std::cout << "OpenGL major version = " << OpenGLVersion[0] << std::endl;
        std::cout << "OpenGL minor version = " << OpenGLVersion[1] << std::endl << std::endl;
	glClearColor(0.2f, 0.4f, 0.6f, 0.0f);
}

/*void Renderer::InitWindow(int argc, char* argv[])
{
	//glutInit(&argc, argv);

	//glutInitContextVersion(4, 1);
	//glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	//glutInitContextProfile(GLUT_CORE_PROFILE);

	//glutSetOption(
	//	GLUT_ACTION_ON_WINDOW_CLOSE,
	//	GLUT_ACTION_GLUTMAINLOOP_RETURNS
	//);

	//glutInitWindowSize(CurrentWidth, CurrentHeight);

	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	//WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	//if(WindowHandle < 1) {
        //    std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
        //    exit(EXIT_FAILURE);
	//}

	//glutReshapeFunc(ResizeFunction);
	//glutDisplayFunc(RenderFunction);
	//glutIdleFunc(IdleFunction);
	//glutTimerFunc(0, TimerFunction, 0);
}

void Renderer::ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void Renderer::RenderFunction(void)
{
	++FrameCount;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glutSwapBuffers();
	//glutPostRedisplay();
}

void Renderer::IdleFunction(void)
{
	glutPostRedisplay();
}*/

/*void Renderer::TimerFunction(int Value)
{
	if (0 != Value) {
		std::stringstream TempString;

		TempString << WINDOW_TITLE_PREFIX << ": " << FrameCount*4 << " Frames Per Second @ "<< CurrentWidth <<" x "<< CurrentHeight;

		glutSetWindowTitle(TempString.str().c_str());
		free(TempString);
	}

	FrameCount = 0;
	//glutTimerFunc(250, TimerFunction, 1);
}*/

