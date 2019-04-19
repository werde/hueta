#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "GL/gl.h"
#include "GL/glext.h"

#include "../mat.h"

class App;
extern App* a;

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        void render();
    protected:

    private:
        std::vector<vec3> _v;
        std::vector<vec2> _uv;
        GLuint _sp;
        GLuint _vbo;
        GLuint _uvbo;

        GLuint _tex;
};

#endif // SCENE_H
