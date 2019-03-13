#ifndef IMGLOAD_H_INCLUDED
#define IMGLOAD_H_INCLUDED

#include <stdio.h>
#include <memory>
#include <zlib.h>

typedef struct
{
    long unsigned int width, height, sz;
    unsigned char bit_depth;
    unsigned char color_type;
    unsigned char compression_method;
    unsigned char filter_method;
    unsigned char interlace_method;

    unsigned char bytes_per_sample;
    unsigned char samples_per_pixel;
    unsigned char bytes_per_pixel;

    unsigned char path[1024];
    void* pixelData;
    unsigned long szPixelData;
}   ImageStruct;


ImageStruct* loadPNG();

#endif // IMGLOAD_H_INCLUDED
