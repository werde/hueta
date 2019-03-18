#ifndef QUAKECONSOLE_H
#define QUAKECONSOLE_H

#include <vector>

#include <GL/gl.h>
#include <GL/glext.h>

#include "../mat.h"
#include "QCBackplate.h"
#include "CommandLine.h"

#define QC_TOP 0.00f
#define QC_BOTTOM 0.00f
#define QC_LEFT 0.00f
#define QC_RIGHT 0.00f
#define YGAP 0
#define XGAP 0
#define QCROWS


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
        unsigned char _buf[10];

        QCBackplate* _qbc;
        CommandLine* _cl;
        std::vector<Symbol> _symbols;

        //
        int sWidth;
        int sHeight;

};

#endif // QUAKECONSOLE_H
