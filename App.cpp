#include "App.h"

App::App() : _mw(NULL)
{

}

void App::run()
{
    _mw = new MyWindow();
    HWND hWnd = _mw->GetHwnd();
    HDC myHDC = _mw->GetDC();

    SetContext();

    ///**** scene*/
	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
    glViewport(0,0,300,300);
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.5f, 0.2f, 0.5f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    while (!_quit)
    {

        loop();

        glClear ( GL_COLOR_BUFFER_BIT );
        glLoadIdentity();
        SwapBuffers(myHDC);
    }
}

bool App::SetContext()
{
    if (!_mw) return false;

    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    HDC myHDC = _mw->GetDC();
    if(!myHDC)
        MessageBox(NULL, "HDC is null", "Error!",  MB_ICONEXCLAMATION | MB_OK);

    int  winPixelFormat;
    winPixelFormat = ChoosePixelFormat(myHDC, &pfd);
    if(!winPixelFormat)
        MessageBox(NULL, "winPixelFormat is null", "Error!",  MB_ICONEXCLAMATION | MB_OK);

    if (!SetPixelFormat(myHDC,winPixelFormat, &pfd))
        MessageBox(NULL, "SetPixelFormat is null", "Error!",  MB_ICONEXCLAMATION | MB_OK);

    _ctx = wglCreateContext(myHDC);
    if (!_ctx)
        MessageBox(NULL, "_ctx is null", "Error!",  MB_ICONEXCLAMATION | MB_OK);

    if (!wglMakeCurrent(myHDC, _ctx))
        MessageBox(NULL, "wglMakeCurrent returns null", "Error!",  MB_ICONEXCLAMATION | MB_OK);

    return true;
}

bool App::InitGLVars()
{
    return true;
}


void App::loop()
{
    // message queue
    int bRet = true;
    MSG msg;
/*    while ((*/bRet = GetMessage(&msg, NULL, 0, 0);//) != 0)
//    {
        if (bRet == -1)
        {
            return;
        }

        std::cout << msg.wParam << std::endl;
        std::cout << _counter << std::endl;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
//    }

    std::cout << _counter << std::endl;
    _counter++;
}
