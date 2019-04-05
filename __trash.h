#ifndef __TRASH_H
#define __TRASH_H

#include <GL/GL.h>
#include <GL/glext.h>

#define MKEY_A 0x41
#define MKEY_B 0x42
#define MKEY_C 0x43
#define MKEY_D 0x44
#define MKEY_E 0x45
#define MKEY_F 0x46
#define MKEY_G 0x47
#define MKEY_H 0x48
#define MKEY_I 0x49
#define MKEY_J 0x4A
#define MKEY_K 0x4B
#define MKEY_L 0x4C
#define MKEY_M 0x4D
#define MKEY_N 0x4E
#define MKEY_O 0x4F
#define MKEY_P 0x50
#define MKEY_Q 0x51
#define MKEY_R 0x52
#define MKEY_S 0x53
#define MKEY_T 0x54
#define MKEY_U 0x55
#define MKEY_V 0x56
#define MKEY_W 0x57
#define MKEY_X 0x58
#define MKEY_Y 0x59
#define MKEY_Z 0x5A

extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM2FPROC glUniform2f;
extern PFNGLUNIFORM3FPROC glUniform3f;
//extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
//extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
//extern PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;

GLboolean MyGLInit();
#endif

