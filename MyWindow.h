#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <windows.h>
#include "GL/gl.h"

extern HINSTANCE hInst;
const char cp_windClassName[] = "myWindClassName";

typedef LRESULT CALLBACK (*PWndProc)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef struct
{
    RECT rect;
    bool fullscreen;
} WinCfg;

class MyWindow
{
public:
    MyWindow();
    virtual ~MyWindow();

    HDC GetDC();
    HWND GetHwnd(){return _hwnd;};

protected:

private:
    HWND _hwnd;
    PWndProc _wndProc;
    WinCfg* _cfg;
};

#endif // WINDOW_H
