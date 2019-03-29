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
        GLuint _sp;
        GLuint _vbo;
};

#endif // SCENE_H
