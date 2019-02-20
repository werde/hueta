#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <GL/gl.h>
#include <GL/glext.h>

extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

class Model;
///
typedef struct
{
    Model* m;
    GLuint vbo;
    GLuint uvbo;
} ModelObj;


class Renderer
{
    public:
        Renderer();

        void registerModel(Model* m);

        void render();

        ~Renderer();
    protected:

    private:
        std::vector<ModelObj> mos;

        GLuint registerBuffer(int sz, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
};

#endif // RENDERER_H
