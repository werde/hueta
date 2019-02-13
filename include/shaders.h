#ifndef SHADERS_H_INCLUDED
#define SHADERS_H_INCLUDED

#include <stdio.h>

#include "GL/gl.h"
#include "GL/glext.h"

extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

void readShaderFile(const char* file_path, const GLchar* pShaderCode);
void compileShaderProgramm(GLuint* sp);

#endif // SHADERS_H_INCLUDED
