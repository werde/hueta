#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <GL/gl.h>
#include <GL/glext.h>

class App;
extern App* a;
class Model;
class Entity;

typedef struct
{
    Model* m;
    GLuint vbo;
    GLuint uvbo;
    bool registered=false;
} ModelObj;

class Renderer
{
    public:
        Renderer();

        void registerModel(Model* m);
        void registerEntity(Entity* e);

        void render(GLuint);

        ~Renderer();
    protected:

    private:
        std::vector<ModelObj> mos;
        std::vector<Entity*> _es;

        GLuint registerBuffer(int sz, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
};

#endif // RENDERER_H
