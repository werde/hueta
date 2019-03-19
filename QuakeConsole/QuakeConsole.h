#ifndef QUAKECONSOLE_H
#define QUAKECONSOLE_H

#include <vector>

#include <GL/gl.h>
#include <GL/glext.h>

#include "../mat.h"
#include "TextDefs.h"
#include "QCBackplate.h"
#include "CommandLine.h"

typedef struct
{
    char c;
    vec2 uv[4];
} Symbol;

class QuakeConsole
{
    public:
        QuakeConsole();
        virtual ~QuakeConsole();


        void draw();
        void key(WPARAM wParam, bool zaglav);

        void toggle(){_enabled = !_enabled;};
        bool status(){return _enabled;};

        void TextArea();
        void calcOGLcoords(int i);
    protected:

    private:
        bool _enabled;

        std::vector<vec3> _v;
        std::vector<vec2> _uv;
        GLuint _bsp;
        GLuint _vbo;
        GLuint _uvbo;

        GLuint _tex;
        unsigned char _buf[900];
        int sz_Buf;

        QCBackplate* _qbc;
        CommandLine* _cl;
        std::vector<Symbol> _symbols;

        //
        Pos _pos;
        int fH, fW;
        int w, h;
        int g;
        int symPerStr;
        int numStrings;
};

#endif // QUAKECONSOLE_H
