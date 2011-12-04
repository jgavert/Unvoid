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

#include "opengl.h"
#include "window.h"
#include "Renderer.h"

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
    RenderLoop();
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
	CreateShaders();
	CreateVBO();
}

void Renderer::CreateVBO(void)
{
    GLfloat Vertices[] = {
        -0.8f, -0.8f, 0.0f, 1.0f,
         0.0f,  0.8f, 0.0f, 1.0f,
         0.8f, -0.8f, 0.0f, 1.0f
    };
 
    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
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
        fprintf(
            stderr,
            "ERROR: Could not create a VBO: %s \n",
            gluErrorString(ErrorCheckValue)
        );
 
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
        fprintf(
            stderr,
            "ERROR: Could not destroy the VBO: %s \n",
            gluErrorString(ErrorCheckValue)
        );
 
        exit(-1);
    }
}

const GLchar* VertexShader =
{
    "#version 400\n"\
 
    "layout(location=0) in vec4 in_Position;\n"\
    "layout(location=1) in vec4 in_Color;\n"\
    "out vec4 ex_Color;\n"\
 
    "void main(void)\n"\
    "{\n"\
    "   gl_Position = in_Position;\n"\
    "   ex_Color = in_Color;\n"\
    "}\n"
};

const GLchar* FragmentShader =
{
    "#version 400\n"\
 
    "in vec4 ex_Color;\n"\
    "out vec4 out_Color;\n"\
 
    "void main(void)\n"\
    "{\n"\
    "   out_Color = ex_Color;\n"\
    "}\n"
};

void Renderer::CreateShaders(void)
{
    GLenum ErrorCheckValue = glGetError();
 
    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
    glCompileShader(VertexShaderId);
 
    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
    glCompileShader(FragmentShaderId);
 
    ProgramId = glCreateProgram();
        glAttachShader(ProgramId, VertexShaderId);
        glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);
    glUseProgram(ProgramId);
 
    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not create the shaders: %s \n",
            gluErrorString(ErrorCheckValue)
        );
 
        exit(-1);
    }
}

void Renderer::DestroyShaders(void)
{
    GLenum ErrorCheckValue = glGetError();
 
    glUseProgram(0);
 
    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);
 
    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);
 
    glDeleteProgram(ProgramId);
 
    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not destroy the shaders: %s \n",
            gluErrorString(ErrorCheckValue)
        );
 
        exit(-1);
    }
}

void Renderer::Cleanup(void)
{
    DestroyShaders();
    DestroyVBO();
}

void Renderer::RenderLoop()
{
	for (int i=0; i<100000; ++i)
	{
		Render();
	}
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
}*/

void Renderer::Render()
{
	++FrameCount;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	window.swap_buffers();
	//glutPostRedisplay();
}

/*void Renderer::IdleFunction(void)
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

