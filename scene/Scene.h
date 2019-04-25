#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "GL/gl.h"
#include "GL/glext.h"

#include "../mat.h"
#include "Terrain.h"

class App;
extern App* a;

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        void render();
        Terrain* ter;
    protected:

    private:
        GLuint _sp;
};

#endif // SCENE_H
