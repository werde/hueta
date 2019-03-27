#ifndef IMAGELOAD_H_INCLUDED
#define IMAGELOAD_H_INCLUDED

#include "GL/gl.h"
#include "GL/glext.h"

#include "PNGLoad.h"

GLuint loadTex(const char* path);
GLuint texturePNG(PNGImageStruct* is);

#endif // IMAGELOAD_H_INCLUDED
