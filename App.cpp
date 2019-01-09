#include "App.h"

App::App() : _mw(NULL)
{

}

void App::run()
{
    const GLchar *VSS = "void main() \n { \n gl_Position = ftransform(); \n }\0";
    const GLchar *FSS = "void main() \n { \n gl_FragColor = vec4(0.4,0.4,0.8,1.0); \n } \n\0";

    ///**** window*/
    _mw = new MyWindow();
    HWND hWnd = _mw->GetHwnd();
    HDC myHDC = _mw->GetDC();
	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);

    SetContext();

	InitGLVars();

    GLfloat v[] = {
                   -1.0f, -1.5f,  0.0f,
                   1.0f, -1.0f,  0.0f,
                  0.0f, 1.0f,  0.0f
                };

    HMODULE ogl32 = LoadLibrary("opengl32");
    hui glGenBuffers = (hui)wglGetProcAddress("glGenBuffers");
    hui4 glEnableVertexAttribArray = (hui4) wglGetProcAddress("glEnableVertexAttribArray");
    hui2 glBindBuffer = (hui2)wglGetProcAddress("glBindBuffer");
    hui3 glBufferData = (hui3)wglGetProcAddress("glBufferData");
    hui5 glBindVertexArray = (hui5) wglGetProcAddress("glBindVertexArray");
    hui6 glVertexAttribPointer = (hui6) wglGetProcAddress("glVertexAttribPointer");
    hui7 glCreateShader = (hui7) wglGetProcAddress("glCreateShader");
    hui8 glShaderSource = (hui8) wglGetProcAddress("glShaderSource");
    hui9 glCompileShader = (hui9)wglGetProcAddress("glCompileShader");
    hui10 glCreateProgram = (hui10) wglGetProcAddress("glCreateProgram");
    hui11 glAttachShader = (hui11) wglGetProcAddress("glAttachShader");
    hui12 glLinkProgram = (hui12) wglGetProcAddress("glLinkProgram");
    hui13 glUseProgram = (hui13) wglGetProcAddress("glUseProgram");
    hui14 glGenVertexArrays = (hui14) wglGetProcAddress("glGenVertexArrays");
    hui15 glGetAttribLocation = (hui15) wglGetProcAddress("glGetAttribLocation");
    hui16 glDisableVertexAttribArray = (hui16) wglGetProcAddress("glDisableVertexAttribArray");
    hui17 glGetShaderiv = (hui17) wglGetProcAddress("glGetShaderiv");
    hui18 glGetShaderInfoLog = (hui18) wglGetProcAddress("glGetShaderInfoLog");

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), v, GL_STATIC_DRAW);

    //glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
/*
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
*/

    GLuint vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &VSS, NULL);
    glShaderSource(fragmentShader, 1, &FSS, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    ///Error check
	GLint Result = GL_FALSE;
	int InfoLogLength = 0;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		char VertexShaderErrorMessage[InfoLogLength+1];
		glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		//printf("%s\n", &VertexShaderErrorMessage[0]);
		MessageBox(NULL, (LPCSTR)&VertexShaderErrorMessage[0],  "e", MB_ICONEXCLAMATION | MB_OK);
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		char FragmentShaderErrorMessage[InfoLogLength+1];
		glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		//printf("%s\n", &FragmentShaderErrorMessage[0]);
		MessageBox(NULL, (LPCSTR)&FragmentShaderErrorMessage[0],  "e", MB_ICONEXCLAMATION | MB_OK);
	}

	/// Check the program
	/*
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	*/

    GLuint sp = glCreateProgram();
    glAttachShader(sp, vertexShader);
    glAttachShader(sp, fragmentShader);
    glLinkProgram(sp);

    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    //MessageBox(NULL, (LPCSTR)version,  "e", MB_ICONEXCLAMATION | MB_OK);

    while (!_quit)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(sp);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);

        SwapBuffers(myHDC);

        loop();
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
    glViewport(0,0,800,600);
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
//    glLoadIdentity();

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

//	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.5f, 0.2f, 0.5f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
//	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
//	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);*/
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
