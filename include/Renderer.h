#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <GL/gl.h>
#include <GL/glext.h>

class App;
extern App* a;
class Model;
class Entity;

class Renderer
{
    public:
        Renderer();

        void registerEntity(Entity* e);
        void render(GLuint);

        ~Renderer();
    protected:

    private:
        std::vector<Entity*> _es;

        GLuint registerBuffer(int sz, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
        void registerModel(Model* m);
};

#endif // RENDERER_H
