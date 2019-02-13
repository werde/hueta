#include "Camera.h"

Camera::Camera()
{
    pos = {{0.0, 0.0, -1.0, 0.0}};
	focus = {{1, 0, 1, 0}};
}

Camera::~Camera()
{

}
