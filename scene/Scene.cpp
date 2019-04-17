#include "Scene.h"
#include "shaders.h"
#include "../__trash.h"
#include "../MyWindow.h"
#include "../App.h"
#include "Camera.h"

int permutation[256] =
{ 151,160,137,91,90,15,                 // Hash lookup table as defined by Ken Perlin.  This is a randomly
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,    // arranged array of all numbers from 0-255 inclusive.
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

float lerp(float a0, float a1, float w)
{
    return (1.0f - w)*a0 + w*a1;
}

double fade(double t)
{

    return t * t * t * (t * (t * 6 - 15) + 10);
}

/*
float dotGridGradient(int ix, int iy, float x, float y, vec2* vectors)
{
    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx*vectors[iy][ix].m[0] + dy*vectors[iy][ix].m[1]);
}*/

void generateHeightMap(int w, int h)
{
    vec2 vectors[w][h];
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            vectors[i][j].m[0] = rand()/(float)RAND_MAX;
            vectors[i][j].m[1] = rand()/(float)RAND_MAX;
        }
    }


}

void perlin(float x, float y)
{
    int p[512];
    for(int i=0;i<512;i++) {
        p[i] = permutation[i%256];
    }

    int xi = (int)x % 255;
    int iy = (int)y % 255;

    double dx = x - (int)x;
    double dy = y - (int)y;

    double u = fade(dx);
    double v = fade(dy);

    int aa, ab, ba, bb;
    aaa = p[p[p[    xi ]+    yi ]];
    aba = p[p[p[    xi ]+inc(yi)]];
    aab = p[p[p[    xi ]+    yi ]];
    abb = p[p[p[    xi ]+inc(yi)]+inc(zi)];
    baa = p[p[p[inc(xi)]+    yi ]+    zi ];
    bba = p[p[p[inc(xi)]+inc(yi)]+    zi ];
    bab = p[p[p[inc(xi)]+    yi ]+inc(zi)];
    bbb = p[p[p[inc(xi)]+inc(yi)]+inc(zi)];



}

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
