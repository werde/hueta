#ifndef APP_H
#define APP_H

#include <iostream>
#include <Windows.h>

//#define GL_GLEXT_PROTOTYPES
#include <GL/GL.h>
#include <GL/glext.h>

#include "MyWindow.h"

extern HINSTANCE hInst;

class App
{
    public:
        App();
        void cfgInit();
        void run();
        bool resize();

    private:
        void* cfg;
        void* state;
        bool _quit = false;

        bool SetContext();
        bool InitGLVars();
        void loop();
        int _counter = 0;

        MyWindow* _mw;
        HGLRC _ctx;
};

#endif // APP_H
