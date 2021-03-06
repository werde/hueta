#include "Camera.h"

#include "../App.h"
#include "../MyWindow.h"

Camera::Camera()
{
    pos   = {{0.0, 10.0, 0.0, 0.0}};
	focus = {{1, 0, 0, 0}};
	side  = crossvec4(focus, Y_AXIS);

    yaw = 0;
    pitch = 0;
}

Camera::~Camera()
{
}

void Camera::forward(GLfloat d)
{
    pos.x += focus.x * d;
    pos.y += focus.y * d;
    pos.z += focus.z * d;
}

void Camera::strafe(GLfloat d)
{
    pos.x += side.x * d;
    pos.y += side.y * d;
    pos.z += side.z * d;
}

void Camera::vert(GLfloat d)
{
    /*
    pos.x += focus.x * d;
    pos.y += focus.y * d;
    pos.z += focus.z * d;
    */
}

void Camera::rotate(GLfloat p, GLfloat y)
{
    pitch += p;
    yaw += y;
    const float hpi = 1.5707963;
    if(pitch > hpi) pitch = hpi;
    if(pitch < -hpi) pitch = -hpi;
    float cosp = cos(pitch);
    focus.x = cosp * sin(yaw);
    focus.y = sin(pitch);
    focus.z = -cosp * cos(yaw);
    side = crossvec4(focus, Y_AXIS);
    normalizevec4(&side);
}

void Camera::proj_matrix()
{
    /*RECT hwRect;
    a->_mw->GetSize(&hwRect);
    GLfloat hwratio = (hwRect.right - hwRect.left)/((GLfloat)hwRect.bottom - hwRect.top);
    mProj = perspective(45.0f, hwratio, 0.1f, 100.0f);*/
}
