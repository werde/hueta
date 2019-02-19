#include "App.h"
#include "__trash.h"
#include "shaders.h"

static GLboolean MyGLInit()
{
	glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress("glGenBuffers");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress("glEnableVertexAttribArray");
	glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC) wglGetProcAddress("glBufferData");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) wglGetProcAddress("glBindVertexArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) wglGetProcAddress("glVertexAttribPointer");
	glCreateShader = (PFNGLCREATESHADERPROC) wglGetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC) wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC) wglGetProcAddress("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) wglGetProcAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC) wglGetProcAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC) wglGetProcAddress("glLinkProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) wglGetProcAddress("glGenVertexArrays");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) wglGetProcAddress("glGetAttribLocation");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress("glDisableVertexAttribArray");
	glGetShaderiv = (PFNGLGETSHADERIVPROC) wglGetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) wglGetProcAddress("glUniformMatrix4fv");
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) wglGetProcAddress("glActiveTexture");
    glUniform1i = (PFNGLUNIFORM1IPROC) wglGetProcAddress("glUniform1i");
    glUniform3f = (PFNGLUNIFORM3FPROC) wglGetProcAddress("glUniform3f");
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmap");

	return true;
}

App::App() : _mw(NULL)
{
    char buf[1024];
    GetModuleFileNameA(NULL, buf, 1024);

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
	MyGLInit();

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
//------------------

    GLuint MatrixID = glGetUniformLocation(sp, "MVP");
    GLuint TextureID = glGetUniformLocation(sp, "myTextureSampler");
    GLuint ex_ColorID = glGetUniformLocation(sp, "ex_Color");
/*
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, v, GL_STATIC_DRAW);
*/
    GLuint mvbo;
    glGenBuffers(1, &mvbo);
    glBindBuffer(GL_ARRAY_BUFFER, mvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*m.v.size(), &(m.v[0]), GL_STATIC_DRAW);

	GLuint uvbo;
	glGenBuffers(1, &uvbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, m.vt.size()*sizeof(vec2), &(m.vt[0]), GL_STATIC_DRAW);

    for (int i=0; i<m.vt.size(); i++)
    {
        printf("%f %f\n", m.vt[i].m[0], m.vt[i].m[1]);
    }

    DWORD dTime, ctr1, ctr2;
    while (!_quit)
    {
        ctr1 = GetTickCount();

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

        //glUniformMatrix4fv(ex_ColorID, 1, GL_FALSE, ex_Color.m);
        glUniform3f(ex_ColorID, ex_Color[0], ex_Color[1], ex_Color[2]);

        // 1st attribute buffer
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, mvbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m.tex);
        glUniform1i(TextureID, 0);

		// 2nd attribute buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,0);

        glDrawArrays(GL_TRIANGLES, 0, m.v.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        //glDisableVertexAttribArray(2);

        SwapBuffers(myHDC);

        /// render end
        ctr2 = GetTickCount();
        int dTime = ctr2 - ctr1;
        _frameTime = static_cast<double>(dTime);
        float fps60 = 1000.0/60.0;

        /*
        if (dTime < fps60)
            Sleep((fps60 - dTime));
        */

        //float fps = 1/(float)dTime;
        //printf("rought fps : %f\n", 1000*fps);
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
