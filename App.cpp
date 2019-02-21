#include "App.h"

#include "shaders.h"

#include "MyWindow.h"
#include "Camera.h"
#include "Renderer.h"

#include "Model.h"


App::App() : _mw(NULL)
{
    char buf[1024];
    GetModuleFileNameA(NULL, buf, 1024);

    _ren = new Renderer();
    c = new Camera();

    printf("%s\n", buf);

    POINT p;
    GetCursorPos(&p);
    mouseX = p.x;
    mouseY = p.y;
}

void App::run()
{
    ///**** window*/
    _mw = new MyWindow();
    HWND hWnd = _mw->GetHwnd();
    HDC myHDC = _mw->GetDC();
	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);

    SetContext();

	InitGLVars();
	bool succ = MyGLInit();

	GLuint sp = glCreateProgram();
	compileShaderProgramm(&sp);

    GLfloat v[] =   {
                    -1.0f, -1.5f,  0.0f,
                    1.0f, -1.0f,  0.0f,
                    0.0f, 1.0f,  0.0f
                    };
    GLfloat ex_Color[3] = {0.3,0.2,0.6};

    Model m;
    m.LoadObj(&m);
    _ren->registerModel(&m);
//------------------

    GLuint MatrixID = glGetUniformLocation(sp, "MVP");
    GLuint TextureID = glGetUniformLocation(sp, "myTextureSampler");
    GLuint ex_ColorID = glGetUniformLocation(sp, "ex_Color");

    for (int i=0; i<m.vt.size(); i++)
    {
        printf("%f %f\n", m.vt[i].m[0], m.vt[i].m[1]);
    }

    while (!_quit)
    {
        auto _start = std::chrono::high_resolution_clock::now();
        MSG msg;
        while (::PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ///*Rendering part
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(sp);

		mat4 ProjectionMatrix = perspective(45.0f, (float)4.0f / 3.0f, 0.1f, 100.0f);
		mat4 ViewMatrix = lookAt(c->pos, c->focus); ;
        mat4 ModelMatrix = IDENTITY_MATRIX;
        mat4 temp = multymat(&ViewMatrix, &ModelMatrix);
        mat4 MVP = multymat(&temp, &ProjectionMatrix);;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(MVP.m[0]));

        glUniform3f(ex_ColorID, ex_Color[0], ex_Color[1], ex_Color[2]);

        _ren->render();
        SwapBuffers(myHDC);

        /// render end
        auto _end = std::chrono::high_resolution_clock::now();
        _lastFrame = static_cast<float>((_end - _start)/std::chrono::milliseconds(1));

        {
            BYTE lpKeyState[256];
            GetKeyboardState(lpKeyState);

            float speed = 0.005;
            if (lpKeyState[MKEY_W] & 0x1 << 7)
            {
                c->forward(speed*_lastFrame);
            }
            if (lpKeyState[MKEY_S] & 0x1 << 7)
            {
                c->forward(-1.0*speed*_lastFrame);
            }
            if (lpKeyState[MKEY_A] & 0x1 << 7)
            {
                c->strafe(-1.0*speed*_lastFrame);
            }
            if (lpKeyState[MKEY_D] & 0x1 << 7)
            {
                c->strafe(speed*_lastFrame);
            }
        }

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
    RECT rect;
    _mw->GetSize(&rect);
    glViewport(0,0,rect.right,rect.bottom);
    //glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    //glLoadIdentity();

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.5f, 0.2f, 0.5f, 0.5f);				// Black Background
//	glClearDepth(1.0f);									// Depth Buffer Setup
//	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LESS);								// The Type Of Depth Testing To Do
    glEnable(GL_CULL_FACE);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    return true;
}

bool App::resize()
{
    if (!_mw) return false;

    RECT rect;
    _mw->GetSize(&rect);
    glViewport(0,0,rect.right,rect.bottom);

    return true;
}

void App::handleKeyDown(UINT msg, WPARAM wParam, LPARAM lParam)
{
    float speed = 0.1f;
    float d = 0.1;



    switch(wParam)
    {
    case MKEY_W:
        c->forward(d);
        break;
    case MKEY_A:
        c->strafe(-1.0f*d);
        break;
    case MKEY_S:
        c->forward(-1.0f*d);
        break;
    case MKEY_D:
        c->strafe(d);
        break;
    case MKEY_Q:
        c->rotate(0.05, 0.0);
        break;
    case MKEY_E:
        c->rotate(-0.05, 0.0);
        break;
    case MKEY_Z:
        c->rotate(0, 0.05);
        break;
    case MKEY_C:
        c->rotate(0.0, -0.05);
        break;
    default:
        break;
    }
};

void App::handleMouseMove(UINT msg, WPARAM wParam, LPARAM lParam)
{
    int xPos = GET_X_LPARAM(lParam);
    int yPos = GET_Y_LPARAM(lParam);

    int dx = mouseX - xPos;
    int dy = mouseY - yPos;

    if ((dx == 0)&&(dy == 0)) return;

    const float kVert = 0.001f;
    const float kHor = -0.001f;

    c->rotate(dy*kVert, dx*kHor);

    RECT rect;
    _mw->GetSize(&rect);
    mouseX = rect.right/2;
    mouseY = rect.bottom/2;

    POINT pt;
    pt.x = 0;
    pt.y = 0;
    ScreenToClient(_mw->GetHwnd(), &pt);
    SetCursorPos(mouseX-pt.x,mouseY-pt.y);
    printf("xPos %d, yPos %d, mX %d, mY %d %d %d\n", xPos, yPos, mouseX, mouseY, pt.x, pt.y);
};


void App::loop()
{
    // message queue
    int bRet = true;
    MSG msg;
//    while ((*/bRet = GetMessage(&msg, NULL, 0, 0);//) != 0)
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
