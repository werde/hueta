#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <Windows.h>


extern HINSTANCE hInst;
const char cp_windClassName[] = "myWindClassName";

class App;
extern App* a;

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

    void GetSize(RECT* r);

protected:

private:
    HWND _hwnd;
    PWndProc _wndProc;
    WinCfg* _cfg;


};

#endif // WINDOW_H
