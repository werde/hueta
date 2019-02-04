#include "MyWindow.h"
#include "App.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
		{

		}
		break;
		case WM_SIZE:
		    a->resize();
            break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
            exit(1488);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

MyWindow::MyWindow()
{
    // Window window
    WNDCLASSEXA wndClass = {0};

    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;;
    wndClass.lpfnWndProc = (WNDPROC) WndProc;
    //wndClass.cbClsExtra;
    //wndClass.cbWndExtra;
    wndClass.hInstance = hInst;
    wndClass.hIcon = NULL;
    wndClass.hCursor = NULL;
    wndClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = cp_windClassName;
    wndClass.hIconSm = NULL;

    if (!RegisterClassExA(&wndClass))
    {
        std::cout << "failde to regiester class" << std::endl;
        MessageBox(NULL, "Window Registration Failed!", "Error!",  MB_ICONEXCLAMATION | MB_OK);
    }

    _hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, wndClass.lpszClassName, "test window", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, 0, 0, wndClass.hInstance, 0);

    if (!_hwnd)
    {
        std::cout << "hwnd null" << std::endl;
        MessageBox(NULL, "wnd null!", "hui",  MB_ICONEXCLAMATION | MB_OK);
    }

    ShowWindow(_hwnd, SW_SHOW);
    UpdateWindow(_hwnd);

    _cfg = (WinCfg*) malloc(sizeof(WinCfg));
}


HDC MyWindow::GetDC()
{
    return ::GetDC(this->_hwnd);
}

void MyWindow::GetSize(RECT* r)
{
    ::GetClientRect(_hwnd, r);

/*
    RECT rect;
    if(GetWindowRect(hwnd, &rect))
    {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
    }
*/
/*
    HDC hDC = ::GetDC(this->_hwnd);

    BITMAP structBitmapHeader;
    memset( &structBitmapHeader, 0, sizeof(BITMAP) );

    HGDIOBJ hBitmap = GetCurrentObject(hDC, OBJ_BITMAP);
    GetObject(hBitmap, sizeof(BITMAP), &structBitmapHeader);

    structBitmapHeader.bmWidth;
    structBitmapHeader.bmHeight;
*/
}

MyWindow::~MyWindow()
{
    //dtor
}