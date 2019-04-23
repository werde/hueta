#include "Scene.h"
#include "shaders.h"
#include "../__trash.h"
#include "../MyWindow.h"
#include "../App.h"
#include "Camera.h"
#include "../src/IMAGELoad.h"

#include "../algo/perlin.h"

Scene::Scene()
{
    int w = 100;
    int sz = w*w;
    GLfloat heights[sz];
    double* hts;
    memset(heights, 0, sizeof(GLfloat)*sz);

    GLfloat stride = 10*0.11;

    for (int i = 0; i < sz; i++)
    {
        GLfloat x = (i%w) * stride;
        GLfloat z = (i/w) * stride;
        heights[i] = 10.0*octavePerlin(x, z);

        hts = tperlin(w, 4);
    }

    for (int i = 0; i < sz; i++)
    {
        GLfloat x = (i%w) * stride; //i = i/w + i%w
        GLfloat z = (i/w) * stride;
        GLfloat y = hts[i];//perlin(128*x, 128*y);//6*rand()/(GLfloat)RAND_MAX;


        _v.push_back({x,               heights[i],    z              });
        _v.push_back({x,               heights[i + w],z + stride     });
        _v.push_back({x + stride,      heights[i + 1],z              });


        _v.push_back({x,               heights[i + w],    z + stride});
        _v.push_back({x + stride,      heights[i + w + 1],z + stride});
        _v.push_back({x + stride,      heights[i + 1],    z         });

        _uv.push_back({0.0, 0.0});
        _uv.push_back({0.0, 1.0});
        _uv.push_back({1.0, 0.0});

        _uv.push_back({0.0, 1.0});
        _uv.push_back({1.0, 1.0});
        _uv.push_back({1.0, 0.0});

        //sprintf("%f %f %f \n", x, y, z);
    }

    /// Shader program
	_sp = glCreateProgram();
    compileShaderProgramm(&_sp, ".\\terrain.vert", ".\\terrain.frag");

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);

    _tex=loadTex(".\\assets\\ground.dds");
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

    GLuint TextureID = glGetUniformLocation(_sp, "myTextureSampler");
    glActiveTexture(_tex);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, _v.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

Scene::~Scene()
{
    //dtor
}
