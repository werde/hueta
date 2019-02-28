#ifndef QUAKECONSOLE_H
#define QUAKECONSOLE_H

#include <vector>
#include <GL/gl.h>
#include <GL/glext.h>

#include "../mat.h"

#define QCXPAD 0.1f
#define QCYPAD 0.1f
#define YGAP 8
#define XGAP 1
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
        std::vector<vec3> v;
        std::vector<vec2> uvs;
        GLuint bsp;
        GLuint vbo;
        GLuint uvbo;

        char p1[1024], p2[1024];

        bool _enabled;

        GLuint _tex;
        char _buf[8];
        std::vector<vec3> vbuf;
};

#endif // QUAKECONSOLE_H
