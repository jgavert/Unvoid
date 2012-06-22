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

#ifdef _WIN32
#include <GL\glew.h>
#else
#include "glew/glew.h"
#endif

#include "window.h"
#include "renderer.h"

Renderer::Renderer(Window& w):
	window(w)
{
    CurrentWidth = 800;
    CurrentHeight = 600;
    WindowHandle = 0;

    FrameCount = 0;
    window.createWindow(800, 600);
}
/*
//whattt doesss thisss dooooo
Renderer::Renderer(const Renderer& orig) {
}*/

Renderer::~Renderer() {
}

void Renderer::startLoop()
{
    Initialize();
    std::cout << "lol" << std::endl;
    RenderLoop();
}

void Renderer::Initialize()
{
    GLenum GlewInitResult;

    glewExperimental = GL_TRUE;
    GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult) {
        std::cerr << "ERROR: %s" << glewGetErrorString(GlewInitResult) << std::endl << std::endl;
        exit(EXIT_FAILURE);
    }
    int OpenGLVersion[2];
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
    std::cout << "OpenGL major version = " << OpenGLVersion[0] << std::endl;
    std::cout << "OpenGL minor version = " << OpenGLVersion[1] << std::endl << std::endl;
    glClearColor(0.2f, 0.4f, 0.6f, 0.0f);
    shaders.loadShaders();
    GLint woot = shaders.createShaders();
    glUseProgram(woot);
    CreateVBO();
}

void Renderer::CreateVBO(void)
{
    GLfloat Vertices[] = {
        -0.4f, -0.4f, 0.0f, 1.0f,
         0.0f,  0.4f, 0.0f, 1.0f,
         0.4f, -0.4f, 0.0f, 1.0f
    };

    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.2f, 1.0f,
        0.2f, 0.0f, 1.0f, 1.0f
    };

    GLenum ErrorCheckValue = glGetError();

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1, &VboId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        std::cerr << "ERROR: Could not create a VBO: " << gluErrorString(ErrorCheckValue) << std::endl;
        exit(-1);
    }
}

void Renderer::DestroyVBO()
{
    GLenum ErrorCheckValue = glGetError();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &ColorBufferId);
    glDeleteBuffers(1, &VboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
    std::cerr << "ERROR: Could not destroy the VBO: " << gluErrorString(ErrorCheckValue)<< std::endl;
        exit(-1);
    }
}
void Renderer::Cleanup(void)
{
    shaders.destroyShaders();
    DestroyVBO();
}

void Renderer::RenderLoop()
{
  for (int i=0; i<1000; ++i)
  {
    Render();
  }
}

void Renderer::Render()
{
  ++FrameCount;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);


  sleep(1000);
  window.swap_buffers();
}
