#ifndef QUAKECONSOLE_H
#define QUAKECONSOLE_H

#include <vector>
#include <GL/gl.h>
#include <GL/glext.h>

#include "../mat.h"
#include "QCBackplate.h"

#define QCXPAD 0.05f
#define QCYPAD 0.05f
#define YGAP 8
#define XGAP 8
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

        void toggle(){_enabled = !_enabled;};
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
};

#endif // QUAKECONSOLE_H
