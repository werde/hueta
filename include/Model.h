#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>

#include <GL/gl.h>
#include <GL/glext.h>

#include "../mat.h"

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

#define GL_EXT_texture_compression_s3tc 1
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3

void decode();
GLuint loadBMP_custom(const char * imagepath);

typedef struct
{
    long unsigned int width, height, sz;
    char bit_depth;
    char color_type;
    char compression_method;
    char filter_method;
    char interlace_method;
    char path[1024];
    void* data;
    void* imgData;
}   ImageStruct;

class Model
{
    public:
        Model();
        virtual ~Model();

    static bool LoadObj(Model* m);

    std::vector<vec3> v;
    std::vector<vec2> vt;
    std::vector<vec3> vn;

    GLuint tex;
    GLenum activeTex;

    protected:

    private:
};

#endif // MODEL_H
