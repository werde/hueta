#ifndef APP_H
#define APP_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>


//#define GL_GLEXT_PROTOTYPES
#include <GL/GL.h>
#include <GL/glext.h>

#include "MyWindow.h"
#include "Camera.h"
#include "Model.h"

extern HINSTANCE hInst;

class App
{
    public:
        App();
        void cfgInit();
        void run();
        bool resize();

        void handleKeyDown(UINT msg, WPARAM wParam);
    private:
        void* cfg;
        void* state;
        bool _quit = false;

        bool SetContext();
        bool InitGLVars();
        void loop();
        int _counter = 0;

        Camera* c;

        MyWindow* _mw;
        HGLRC _ctx;

        int mouseX, mouseY;
};


#endif // APP_H
