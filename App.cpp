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

	return true;
}

App::App() : _mw(NULL)
{
    char buf[1024];
    GetModuleFileNameA(NULL, buf, 1024);

    c = new Camera();

    printf("%s\n", buf);

    POINT lpPoint;
    GetCursorPos(&lpPoint);
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
    GLfloat ex_Color[3] = {0.0,0.7,0.3};

    Model m;
    m.LoadObj(&m);
//------------------

    GLuint MatrixID = glGetUniformLocation(sp, "MVP");
    GLuint TextureID = glGetUniformLocation(sp, "myTextureSampler");
    GLuint ex_ColorID = glGetUniformLocation(sp, "ex_Color");

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, v, GL_STATIC_DRAW);

    GLuint mvbo;
    glGenBuffers(1, &mvbo);
    glBindBuffer(GL_ARRAY_BUFFER, mvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.v.size(), &(m.v[0]), GL_STATIC_DRAW);

	GLuint uvbo;
	glGenBuffers(1, &uvbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, m.vt.size() * sizeof(vec2), &(m.vt[0]), GL_STATIC_DRAW);

    while (!_quit)
    {

        // Main message loop:
        MSG msg;
        while (::PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        /// Rendering part
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(sp);

		mat4 ProjectionMatrix = perspective(90.0f, (float)4.0f / 3.0f, 0.1f, 100.0f);
		mat4 ViewMatrix = lookAt(c->pos, c->focus); ;
        mat4 ModelMatrix = IDENTITY_MATRIX;
        mat4 temp = multymat(&ViewMatrix, &ModelMatrix);
        mat4 MVP = multymat(&temp, &ProjectionMatrix);;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(MVP.m[0]));

        //glUniformMatrix4fv(ex_ColorID, 1, GL_FALSE, ex_Color.m);
        glUniform3f(ex_ColorID, ex_Color[0], ex_Color[1], ex_Color[2]);

/*
		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m.tex);
        glUniform1i(TextureID, 0);
*/
        // 1st attribute buffer
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// 2nd attribute buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

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
    RECT rect;
    _mw->GetSize(&rect);

    glViewport(0,0,rect.right,rect.bottom);
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.5f, 0.2f, 0.5f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
//	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
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

void App::handleKeyDown(UINT msg, WPARAM wParam)
{
    switch(wParam)
    {
    case MKEY_W:
        c->forward(1.0f);
        break;
    case MKEY_A:
        c->strafe(-1.0f);
        break;
    case MKEY_S:
        c->forward(-1.0f);
        break;
    case MKEY_D:
        c->strafe(1.0f);
        break;
    case MKEY_Q:
        c->rotate(0.05, 0.0);
        break;
    default:
        break;
    }
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
