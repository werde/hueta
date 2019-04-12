#include "Scene.h"
#include "shaders.h"
#include "../__trash.h"
#include "../MyWindow.h"
#include "../App.h"
#include "Camera.h"

Scene::Scene()
{
    int w = 101;
    int sz = w*w;
    GLfloat heights[sz];
    memset(heights, 0, sizeof(GLfloat)*sz);

    GLfloat stride = 0.1;

    for (int i = 0; i < sz; i++)
    {
        GLfloat x = (i%w) * stride;
        GLfloat y = 6*rand()/(GLfloat)RAND_MAX;
        GLfloat z = (i/w) * stride;

        _v.push_back({x,               y,          z              });
        _v.push_back({x,               y,          z + stride     });
        _v.push_back({x + stride,      y,          z              });


        _v.push_back({x,               y,               z + stride});
        _v.push_back({x + stride,      y,               z + stride});
        _v.push_back({x + stride,      y,               z         });

        //sprintf("%f %f %f \n", x, y, z);
    }

    /// Shader program
	_sp = glCreateProgram();
    compileShaderProgramm(&_sp, ".\\terrain.vert", ".\\terrain.frag");

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);
}

void Scene::render()
{
    RECT hwRect;
    a->_mw->GetSize(&hwRect);
    GLfloat hwratio = (hwRect.right - hwRect.left)/((GLfloat)hwRect.bottom - hwRect.top);
    glUseProgram(_sp);
    mat4 ModelMatrix = IDENTITY_MATRIX;
    mat4 ProjectionMatrix = perspective(45.0f, hwratio, 0.1f, 100.0f);
    mat4 ViewMatrix = lookAt(a->c->pos, a->c->focus);
    mat4 temp = multymat( &ModelMatrix, &ViewMatrix);
    mat4 MVP = multymat(&temp, &ProjectionMatrix);
    GLuint MatrixID = glGetUniformLocation(_sp, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(MVP.m[0]));

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glDrawArrays(GL_TRIANGLES, 0, _v.size());

    glDisableVertexAttribArray(0);
}

Scene::~Scene()
{
    //dtor
}
