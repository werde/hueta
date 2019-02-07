#ifndef MAT_H_INCLUDED
#define MAT_H_INCLUDED

#include <math.h>

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

static const vec4 X_AXIS =      {{1.0,  0.0, 0.0, 0.0}};
static const vec4 Y_AXIS =      {{0.0,  1.0, 0.0, 0.0}};
static const vec4 Z_AXIS =      {{0.0,  0.0, 1.0, 0.0}};
static const vec4 INV_X_AXIS =  {{-1.0, 0.0, 0.0, 0.0}};
static const vec4 INV_Y_AXIS =  {{0.0,  -1.0, 0.0, 0.0}};
static const vec4 INV_Z_AXIS =  {{0.0,  0.0, -1.0, 0.0}};

mat4 multymat(mat4* m1, mat4* m2);
vec4 multymatvec(const mat4* m, const vec4* v);
mat4 perspective(float fovy, float aspect_ratio, float near_plane, float far_plane) ;

#endif // MAT_H_INCLUDED
