#ifndef APP_H
#define APP_H

#include <iostream>
#include <Windows.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/GL.h>
#include <GL/glext.h>

#include "__trash.h"

#include "MyWindow.h"

typedef void (__attribute__((__stdcall__))*hui )(GLsizei, GLuint*);
typedef void (__attribute__((__stdcall__))*hui2)(GLenum, GLuint);
typedef void (__attribute__((__stdcall__))*hui3)(GLenum, GLsizei, const void*, GLenum);
typedef void (__attribute__((__stdcall__))*hui4)(GLuint);
typedef void (__attribute__((__stdcall__))*hui5)(GLuint);
typedef void (__attribute__((__stdcall__))*hui6)(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);
typedef GLuint (__attribute__((__stdcall__))*hui7)(GLenum);
typedef void (__attribute__((__stdcall__))*hui8)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (__attribute__((__stdcall__))*hui9)(GLuint);
typedef GLuint (__attribute__((__stdcall__))*hui10)();
typedef void (__attribute__((__stdcall__))*hui11)(GLuint, GLuint);
typedef void (__attribute__((__stdcall__))*hui12)(GLuint);
typedef void (__attribute__((__stdcall__))*hui13)(GLuint);
typedef void (__attribute__((__stdcall__))*hui14 )(GLsizei, GLuint*);
typedef GLint (__attribute__((__stdcall__))*hui15 )(GLuint, const GLchar *);
typedef GLint (__attribute__((__stdcall__))*hui16 )(GLuint);
typedef void (__attribute__((__stdcall__))*hui17 )(GLuint, GLenum, GLint*);
typedef void (__attribute__((__stdcall__))*hui18 )(GLuint, GLsizei, GLsizei, GLchar*);


//typedef void

extern HINSTANCE hInst;



class App
{
    public:
        App();
        void cfgInit();
        void run();

    private:
        void* cfg;
        void* state;
        bool _quit = false;

        bool SetContext();
        bool InitGLVars();
        void loop();
        int _counter = 0;

        MyWindow* _mw;
        HGLRC _ctx;
};

#endif // APP_H
