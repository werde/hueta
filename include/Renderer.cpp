#include "Renderer.h"
#include "../src/Model.h"
#include "../scene/Entity.h"
#include "../__trash.h"
#include "../App.h"
#include "../MyWindow.h"
#include "Camera.h"
#include "../src/IMAGELoad.h"

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
    if (m->registered) return;

    m->vbo = registerBuffer(m->v.size()*sizeof(vec3), &(m->v[0]));
    m->uvbo = registerBuffer(m->vt.size()*sizeof(vec2), &(m->vt[0]));
    m->registered = true;
}

void Renderer::registerEntity(Entity* e)
{
    registerModel(e->_m);
    printf("\n1Renderer %x \n", e);
    _es.push_back(0);
    printf("\n2Renderer\n");
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
        printf("ren Renderer\n");
        mat4 ModelMatrix = IDENTITY_MATRIX;
        //translate(&ModelMatrix, _es[i]->_pos.x, _es[i]->_pos.y, _es[i]->_pos.z);

        mat4 temp = multymat( &ModelMatrix, &ViewMatrix);
        mat4 MVP = multymat(&temp, &ProjectionMatrix);
        GLuint MatrixID = glGetUniformLocation(sp, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(MVP.m[0]));

        GLuint TextureID;
        Model* m = _es[i]->_m;printf("t Renderer\n");
        GLuint tex = _es[i]->_t;

        glActiveTexture(tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(TextureID, 0);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m->uvbo);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, m->v.size());
        /*
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mos[i].vbo);
        int size;
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);*/

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        //_es[i]->_pos.z += 0.01;
        //_es[i]->_pos.y += 0.01;
    }
}

Renderer::Renderer()
{
    //_es.reserve(10);
    Model* m = new Model();
    m->LoadObj(m, ".\\assets\\meshes\\t.obj");
    GLuint t = loadTex(".\\assets\\uvmap.dds");
    for (int i = 0; i < 3; i++)
    {
        Entity* e = new Entity(m, t);
        registerEntity(e);
        GLfloat fx = 16*(std::rand()/(GLfloat)RAND_MAX);
        e->_pos.x = fx;
        e->_pos.y = 0.0;
        e->_pos.z = 0.0;
    }
}

Renderer::~Renderer()
{


}
