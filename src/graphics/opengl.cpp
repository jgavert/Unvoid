#include "opengl.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

bool& OpenGL::getGL3bit() {
    static bool gl3 = true;
    return gl3;
}

OpenGL::OpenGL() {
    init();
}


void OpenGL::init() 
{
    /*
    static bool haveInited = false;
    if(haveInited)
        return;
    haveInited = true;*/

    GLenum status = glewInit();
    
    //TODO: fix
    if (status == GLEW_OK) {
        //std::cerr << "" << std::endl;
    } else {
        std::stringstream ss;
        ss << "GLEW initialization failed: " << glewGetErrorString(status);
        throw std::runtime_error(ss.str());
    }
}
