#ifndef APP_H
#define APP_H

#include <iostream>
#include <Windows.h>
#include <GL/GL.h>

#include "__trash.h"

#include "MyWindow.h"

extern HINSTANCE hInst;

class App
{
    public:
        App();
        void cfgInit();
        void run();

    private:
        void* cfg;
        void* state;
        bool _quit = false;

        bool SetContext();
        void loop();
        int _counter = 0;

        MyWindow* _mw;
        HGLRC _ctx;
};

#endif // APP_H
