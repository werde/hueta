#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <stdio.h>
#include <vector>

#include "GL/gl.h"
#include "GL/glext.h"

#include "../mat.h"

typedef struct
{
    unsigned char type = 0;
    int pos = 0;
} Cursor;

class CommandLine
{
    public:
        CommandLine();
        virtual ~CommandLine();

        void render(GLuint sp);

    protected:

    private:
    GLuint _tex;
    GLuint _vbo;
    GLuint _uvbo;

    std::vector<vec3> _v;
    std::vector<vec2> _uv;
};

#endif // COMMANDLINE_H
