#ifndef SHADERS_H_INCLUDED
#define SHADERS_H_INCLUDED

#include <stdio.h>

#include "GL/gl.h"
#include "GL/glext.h"

void readShaderFile(const char* file_path, const GLchar* pShaderCode);
void compileShaderProgramm(GLuint* sp, const char* file_path_vert, const char* file_path_frag);

#endif // SHADERS_H_INCLUDED
