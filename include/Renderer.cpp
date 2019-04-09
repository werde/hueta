#include "Renderer.h"
#include "../src/Model.h"
#include "../scene/Entity.h"
#include "../__trash.h"
#include "../App.h"
#include "../MyWindow.h"
#include "Camera.h"

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
    mo.registered = true;
}

void Renderer::registerEntity(Entity* e)
{
    Model* m = e->_m;
    GLuint vbo = registerBuffer(m->v.size()*sizeof(vec3), &(m->v[0]));
    GLuint uvbo = registerBuffer(m->vt.size()*sizeof(vec2), &(m->vt[0]));

    ModelObj mo;
    mo.vbo = vbo;
    mo.uvbo = uvbo;
    mo.m = m;
    mos.push_back(mo);
    _es.push_back(e);
}

void Renderer::render(GLuint sp)
{
    RECT hwRect;
    a->_mw->GetSize(&hwRect);
    GLfloat hwratio = (hwRect.right - hwRect.left)/((GLfloat)hwRect.bottom - hwRect.top);
    mat4 ProjectionMatrix = perspective(45.0f, hwratio, 0.1f, 100.0f);
    mat4 ViewMatrix = lookAt(a->c->pos, a->c->focus);



    for (int i = 0; i < _es.size(); i++)
    {
        mat4 ModelMatrix = IDENTITY_MATRIX;
        translate(&ModelMatrix, _es[i]->_pos.x, _es[i]->_pos.y, _es[i]->_pos.z);
        mat4 temp = multymat(&ViewMatrix, &ModelMatrix);
        mat4 MVP = multymat(&temp, &ProjectionMatrix);
        GLuint MatrixID = glGetUniformLocation(sp, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(MVP.m[0]));

        GLuint TextureID;
        Model* m = _es[i]->_m;
        GLuint tex = _es[i]->_t;

        glActiveTexture(tex);
        glBindTexture(GL_TEXTURE_2D, tex);
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
        _es[i]->_pos.x += 0.1;
    }
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}
