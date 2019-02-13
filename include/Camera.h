#ifndef CAMERA_H
#define CAMERA_H

#include <../mat.h>

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        vec4 pos;
        vec4 focus;
    protected:

    private:
};

#endif // CAMERA_H
