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

    protected:

    private:
        std::vector<vec3> v;
        std::vector<vec2> UVs;
        GLuint bsp;
        GLuint vbo;
};

#endif // QUAKECONSOLE_H
