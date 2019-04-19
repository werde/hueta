#include "Renderer.h"
#include "../src/Model.h"
#include "../scene/Entity.h"
#include "../__trash.h"
#include "../App.h"
#include "../MyWindow.h"
#include "Camera.h"
#include "../src/IMAGELoad.h"

Renderer::Renderer()
{
    _es.reserve(10);
    printf("#%d \n", _es.size());
    Model* m = new Model();
    m->LoadObj(m, ".\\assets\\meshes\\t2.obj");
    GLuint t = loadTex(".\\assets\\t2.png");
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

GLuint Renderer::registerBuffer(int sz, const GLvoid* data, GLenum usage=GL_STATIC_DRAW)
{
    printf("sz %d, data %d\n", sz, data);
    GLuint bo = 0;
    glGenBuffers(1, &bo);
    glBindBuffer(GL_ARRAY_BUFFER, bo);
    glBufferData(GL_ARRAY_BUFFER, sz, data, usage);

    return bo;
}

void Renderer::registerModel(Model* m)
{
    printf("registereing model %d\n", m);
    if (m->registered) return;

    printf("%d %d\n", m->vbo, m->uvbo);

    m->vbo = registerBuffer(m->v.size()*sizeof(vec3), &(m->v[0]));
    m->uvbo = registerBuffer(m->vt.size()*sizeof(vec2), &(m->vt[0]));
    m->registered = true;
    printf("registered model %d\n", m);
}

void Renderer::registerEntity(Entity* e)
{
    registerModel(e->_m);
    _es.push_back(e);
    printf("#%d \n", _es.size());
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

        mat4 temp = multymat( &ModelMatrix, &ViewMatrix);
        mat4 MVP = multymat(&temp, &ProjectionMatrix);
        GLuint MatrixID = glGetUniformLocation(sp, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(MVP.m[0]));

        GLuint TextureID = glGetUniformLocation(sp, "myTextureSampler");
        Model* m = _es[i]->_m;
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
        _es[i]->_pos.z += 0.01;
        _es[i]->_pos.y += 0.01;
    }
}

Renderer::~Renderer()
{


}
