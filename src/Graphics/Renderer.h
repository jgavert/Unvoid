/* 
 * File:   Renderer.h
 * Author: juho
 *
 * Created on November 28, 2011, 1:15 PM
 */

#ifndef RENDERER_H
#define	RENDERER_H
#define WINDOW_TITLE_PREFIX "Project Unvoid"

#include "window.h"

class Renderer {
public:
    Renderer(Window& window);
    //Renderer(const Renderer& orig);
    virtual ~Renderer();
    void startLoop();
private:
    int CurrentWidth;
    int CurrentHeight; 
    int WindowHandle;

    unsigned FrameCount;
    Window& window;
    
    void Initialize();
    //void InitWindow();
    //void ResizeFunction(int, int);
    //void RenderFunction(void);
    //void TimerFunction(int);
    //void IdleFunction(void);

};

#endif	/* RENDERER_H */

