#include <iostream>
#include <Windows.h>
#include "App.h"


HINSTANCE hInst;

App* a;

int WINAPI WinMain(HINSTANCE hi, HINSTANCE hi2, LPSTR lpstr, int i)

{
    hInst = hi;
    a = new App();
    a->run();

    return 0;
}
