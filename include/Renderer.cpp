#include "Renderer.h"
#include "../src/Model.h"
#include "../__trash.h"

GLuint Renderer::registerBuffer(int sz, const GLvoid* data, GLenum usage=GL_STATIC_DRAW)
{
    GLuint bo;
    glGenBuffers(1, &bo);
    glBindBuffer(GL_ARRAY_BUFFER, bo);
    glBufferData(GL_ARRAY_BUFFER, sz, data, usage);

    return bo;
}

void Renderer::registerModel(Model* m)
{
    GLuint vbo = registerBuffer(m->v.size()*sizeof(vec3), &(m->v[0]));
    GLuint uvbo = registerBuffer(m->vt.size()*sizeof(vec2), &(m->vt[0]));

    ModelObj mo;
    mo.vbo = vbo;
    mo.uvbo = uvbo;
    mo.m = m;
    mos.push_back(mo);
}

void Renderer::render()
{
    for (int i = 0; i < mos.size(); i++)
    {
        GLuint TextureID;
        Model* m = mos[i].m;

        glActiveTexture(m->activeTex);
        glBindTexture(GL_TEXTURE_2D, m->tex);
        glUniform1i(TextureID, 0);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, mos[i].vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, mos[i].uvbo);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, m->v.size());
        /*
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mos[i].vbo);
        int size;
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);*/

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}
