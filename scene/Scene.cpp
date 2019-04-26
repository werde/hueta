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
    /// Shader program
	_sp = glCreateProgram();
    compileShaderProgramm(&_sp, ".\\terrain.vert", ".\\terrain.frag");

    ter = new Terrain(11, 0);
}

void Scene::render()
{
    GLuint _tex = ter->_tex;
    GLuint _vbo = ter->_vbo;
    GLuint _uvbo = ter->_uvbo;
    vec3 pos = ter->_pos;

    RECT hwRect;
    a->_mw->GetSize(&hwRect);
    GLfloat hwratio = (hwRect.right - hwRect.left)/((GLfloat)hwRect.bottom - hwRect.top);
    glUseProgram(_sp);
    mat4 ModelMatrix = IDENTITY_MATRIX;
    translate(&ModelMatrix, pos.x, pos.y, pos.z);
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

    glDrawArrays(GL_TRIANGLES, 0, ter->_szVert);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    {
        GLfloat fw = ter->stride*(ter->w - 1);
        int w = ter->w - 1;
        GLfloat xc = a->c->pos.m[0];
        GLfloat yc = a->c->pos.m[1];
        GLfloat zc = a->c->pos.m[2];

        GLfloat x1 = xc - ter->_pos.m[0];
        //GLfloat y1 = a->c->pos.m[1];
        GLfloat z1 = zc - ter->_pos.m[2] + (0/2);



        int ix1 = x1/(fw/w);
        int iz1 = z1/(fw/w);
        //int ix2 = 1 + ix1;
        //int iz2 = 1 + iz1;
        int ipos = (iz1*w + ix1);
        printf("fw %f; x1 = %f; z1 = %f; ipos %d\n", fw, x1, z1, ipos);
        //printf("%f %f %d %f \n ", x1, z1, ipos, ter->hMap[ipos]);
        //a->c->pos.m[1] = ter->hMap[ipos] + 1.5;
    }
}

Scene::~Scene()
{
    //dtor
}
