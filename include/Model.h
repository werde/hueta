#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>

#include "GL/gl.h"

template <typename T=GLfloat> union _vec4
{
    T m[4];
    struct
    {
        T x, y, z, w;
    };
};

template <typename T=GLfloat> union _vec3
{
    T m[3];
    struct
    {
        T x, y, z;
    };
};

template <typename T=GLfloat> union _vec2
{
    T m[2];
    struct
    {
        T x, y, z;
    };
};

template <typename T=GLfloat> struct _mat4
{
    T m[16];
};

typedef _vec4<GLfloat> vec4;
typedef _vec3<GLfloat> vec3;
typedef _vec2<GLfloat> vec2;

typedef _vec4<GLint> veci4;
typedef _vec3<GLint> veci3;
typedef _vec2<GLint> veci2;

typedef _mat4<GLfloat> mat4;
static const mat4 IDENTITY_MATRIX = {{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
}};

class Model
{
    public:
        Model();
        virtual ~Model();

    static bool LoadObj(Model* m);

    std::vector<vec3> v;
    std::vector<vec2> vt;
    std::vector<vec3> vn;

    /*std::vector<veci3> vi;
    std::vector<veci3> uvi;
    std::vector<veci3> ni;*/

    GLuint tex;

    protected:

    private:
};

#endif // MODEL_H
