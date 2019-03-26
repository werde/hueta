#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <stdio.h>
#include <vector>

#include "GL/gl.h"
#include "GL/glext.h"

#include "../mat.h"
#include "TextDefs.h"
#include "Font.h"

#define CL_MAX_BUF 12

class TextArea;

typedef struct
{
    unsigned char type = 0;
    int pos = 0;
} Cursor;

class CommandLine
{
    public:
        CommandLine(Pos p, Font *f);
        virtual ~CommandLine();

        void render(GLuint sp);
        void right();
        void left();
        void enter(TextArea* ta);
        void delet();
        void backspace();
        void addLetter(char l);
    private:
        GLuint _vbo;
        GLuint _uvbo;
        GLuint _cvbo;
        GLuint _cuvbo;

        std::vector<vec3> _v;
        std::vector<vec2> _uv;

        Font* _f;
        unsigned char _buf[CL_MAX_BUF];
        int _szBuf;

        //
        Pos _pos;
        int w, h;
        int g;
        GLfloat fg;
        GLfloat bottomLine, leftLine;

        std::vector<vec3> _curV;
        std::vector<vec2> _curUV;

        int _curPos;

        void fillvv();
        void refillvv();
};

#endif // COMMANDLINE_H
