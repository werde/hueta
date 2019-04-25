#ifndef TERRAIN_H
#define TERRAIN_H

#include <cstdlib>
#include <cstring>
#include <vector>

#include <GL/gl.h>

#include "../mat.h"

#define ALG_PERLIN 0
#define ALG_DIAMOND 1

class Terrain
{
friend class Scene;
public:
    Terrain(double stride, char htsgen);
    virtual ~Terrain();

protected:

private:
    int w, h, sz;
    double* hMap;

    double stride;

    GLuint _vbo;
    GLuint _uvbo;
    GLuint _tex;
    GLuint _szVert;

    vec3 _pos;
};

#endif // TERRAIN_H
