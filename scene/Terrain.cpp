#include "Terrain.h"
#include "../src/IMAGEload.h"
#include "../algo/perlin.h"
#include "../_trash.h"


Terrain::Terrain(double strideA, char htsgen)
    : stride{strideA}
{
    w = h = 11;
    sz = w*h;
    hMap = malloc(sizeof(double)*sz);

    switch(htsgen)
    {
    case 0:
        hMap = tperlin(w, 3);
        hMap = testHMap(w, 999);
        break;
    case 1:
    default:
        memset(hMap, 0, sizeof(double)*sz);
        break;
    }

    std::vector<vec3> _v;
    std::vector<vec2> _uv;
    for (int i = 0; i < sz; i++)
    {
        GLfloat x = (i%w) * stride; //i = i/w + i%w
        GLfloat z = (i/w) * stride;
        GLfloat y = hMap[i];//perlin(128*x, 128*y);//6*rand()/(GLfloat)RAND_MAX;

        _v.push_back({x,               hMap[i],    z              });
        _v.push_back({x,               hMap[i + w],z + stride     });
        _v.push_back({x + stride,      hMap[i + 1],z              });


        _v.push_back({x,               hMap[i + w],    z + stride});
        _v.push_back({x + stride,      hMap[i + w + 1],z + stride});
        _v.push_back({x + stride,      hMap[i + 1],    z         });

        _uv.push_back({0.0, 0.0});
        _uv.push_back({0.0, 1.0});
        _uv.push_back({1.0, 0.0});

        _uv.push_back({0.0, 1.0});
        _uv.push_back({1.0, 1.0});
        _uv.push_back({1.0, 0.0});
    }

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);

    _tex=loadTex(".\\assets\\ground.dds");

    _szVert = _v.size();
    _pos.x = -(stride * (w - 1))/2;
    _pos.y = 0;
    _pos.z = -(stride * (w - 1))/2;

    delete hMap;
}

Terrain::~Terrain()
{
    //dtor
}
