#ifndef APP_H
#define APP_H

#include <iostream>
#include <Windows.h>
#include <Windowsx.h>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

#include "__trash.h"
#include "QuakeConsole.h"

extern HINSTANCE hInst;

class Camera;
class MyWindow;
class Renderer;
class App
{
    friend CommandInterpretor;
    public:
        App();
        void cfgInit();
        void run();
        bool resize();

        void handleKeyDown(UINT msg, WPARAM wParam, LPARAM lParam);
        void handleMouseMove(UINT msg, WPARAM wParam, LPARAM lParam);

        mat4 MVP;
    private:
        void* cfg;
        void* state;
        bool _quit = false;

        bool SetContext();
        bool InitGLVars();
        void loop();
        int _counter = 0;
        float _lastFrame;


        MyWindow* _mw;
        Camera* c;
        Renderer* _ren;
        HGLRC _ctx;

        int mouseX, mouseY;

        QuakeConsole* _q;
};

#endif // APP_H
