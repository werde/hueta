#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <stdio.h>
#include <vector>

#include "GL/gl.h"
#include "GL/glext.h"

#include "../mat.h"
#include "TextDefs.h"
#include "Font.h"

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

    private:
        GLuint _vbo;
        GLuint _uvbo;

        std::vector<vec3> _v;
        std::vector<vec2> _uv;

        Font* _f;

        void fillvv();
        char _buf[25];
        int sz_Buf;

        //
        Pos _pos;
        int w, h;
        int g;
        GLfloat fg;
        GLfloat bottomLine, leftLine;
};

#endif // COMMANDLINE_H
