#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>

#include "GL/gl.h"

typedef union vec4
{
    GLfloat m[4];
    struct
    {
        GLfloat x, y, z, w;
    };
} vec4;

typedef union vec3
{
    GLfloat m[3];
    struct
    {
        GLfloat x, y, z;
    };
} vec3;

typedef union vec2
{
    GLfloat m[2];
    struct
    {
        GLfloat x, y;
    };
} vec2;


class Model
{
    public:
        Model();
        virtual ~Model();

    static bool LoadObj(Model* m);

    std::vector<vec3> v;
    std::vector<vec2> vt;
    std::vector<vec3> vn;
    protected:

    private:
};

#endif // MODEL_H
