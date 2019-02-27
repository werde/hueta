#ifndef QUAKECONSOLE_H
#define QUAKECONSOLE_H

#include <vector>
#include <GL/gl.h>
#include <GL/glext.h>

#include "../mat.h"

class QuakeConsole
{
    public:
        QuakeConsole();
        virtual ~QuakeConsole();

        void draw();

        void toggle(){_enabled = !_enabled;};
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
};

#endif // QUAKECONSOLE_H
