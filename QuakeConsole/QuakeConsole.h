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

        char p1[1024], p2[1024];
};

#endif // QUAKECONSOLE_H
