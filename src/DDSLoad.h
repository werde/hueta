#ifndef DDSLOAD_H_INCLUDED
#define DDSLOAD_H_INCLUDED

#include <stdio.h>

#include <ddraw.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include "dds.h"

typedef struct
{
    uint32_t            dwMagic;
    DDS_HEADER          header;
} DDSImage;

GLuint loadDDS(const char* imagepath);

#endif // DDSLOAD_H_INCLUDED
