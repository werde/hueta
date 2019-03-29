#include "IMAGELoad.h"
#include "Model.h"
#include "PNGLoad.h"
#include "BMPLoad.h"

GLuint loadTex(const char* path)
{
    int pathLen = strlen(path);
    char* imgExt = path + pathLen - 3;

    char bmp[3] = {'b', 'm', 'p'};
    char png[3] = {'p', 'n', 'g'};
    char dds[3] = {'d', 'd', 's'};

    if (memcmp(imgExt, bmp, 3) == 0)
    {
        return loadBMP(path);
    }
    else if  (memcmp(imgExt, png, 3) == 0)
    {
        return texturePNG(makePNG_IS(path));
    }
    else if  (memcmp(imgExt, png, 3) == 0)
    {
        return 1;//loadDDS(path);
    };

    return 0;
};

GLuint texturePNG(PNGImageStruct* is)
{
    GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, is->width, is->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, is->pixelData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
};
