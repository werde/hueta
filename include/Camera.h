#ifndef CAMERA_H
#define CAMERA_H

#include "GL/gl.h"

#include <math.h>

#include <../mat.h>

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        vec4 pos;
        vec4 focus;
        vec4 side;
        GLfloat yaw, pitch;

        void translate(vec3 d);
        void rotate();

        void forward(GLfloat d);
        void strafe(GLfloat d);
        void vert(GLfloat d);

        void rotate(GLfloat p, GLfloat y);

        mat4 mProj;
    protected:

    private:
        void proj_matrix();
};

#endif // CAMERA_H
