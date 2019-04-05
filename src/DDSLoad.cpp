#include "DDSLoad.h"

#include "../__trash.h"

GLuint loadDDS(const char * imagepath)
{
	DDS_HEADER header;

	FILE *fp;

	/* try to open the file */
	fp = fopen(imagepath, "rb");
	if (fp == NULL){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

	/* verify the type of file */
	void *filecode = malloc(sizeof(uint32_t));
	fread(filecode, sizeof(uint32_t), 1, fp);
	if (strncmp(filecode, "DDS ", 4) != 0)
    {
        printf("Not a .DDS image!\n");
		fclose(fp);
		return 0;
	}

	/* get the surface desc */
	fread(&(header.size), sizeof(uint32_t), 1, fp);
	fread(&(header.flags), sizeof(uint32_t), 1, fp);
	fread(&(header.height), sizeof(uint32_t), 1, fp);
	fread(&(header.width), sizeof(uint32_t), 1, fp);
	fread(&(header.pitchOrLinearSize), sizeof(uint32_t), 1, fp);
	fread(&(header.depth), sizeof(uint32_t), 1, fp);
	fread(&(header.mipMapCount), sizeof(uint32_t), 1, fp);
	fread(&(header.reserved1[0]), sizeof(uint32_t), 11, fp);
	fread(&(header.ddspf), sizeof(DDS_PIXELFORMAT), 1, fp);
	fread(&(header.caps), sizeof(uint32_t), 1, fp);
	fread(&(header.caps2), sizeof(uint32_t), 1, fp);
	fread(&(header.caps3), sizeof(uint32_t), 1, fp);
	fread(&(header.caps4), sizeof(uint32_t), 1, fp);
	fread(&(header.reserved2), sizeof(uint32_t), 1, fp);

	printf(" h %d, w %d\n", header.height, header.width);

	if(header.ddspf.flags & DDPF_FOURCC)
    {
        if(memcmp(&(header.ddspf.fourCC), "DX10", 4) == 0)
        {
            printf("DX10\n");
        }
        printf("%d DX:%s\n", header.mipMapCount, &(header.ddspf.fourCC));
    }

	unsigned char * buffer;
	unsigned int bufsize;
	// how big is it going to be including all mipmaps?
    bufsize = file_size - 128;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	fclose(fp);

	//unsigned int components  = (header.ddspf.fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
    unsigned int blockSize = 16;
	switch(header.ddspf.fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		blockSize = 8;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		printf("GL_COMPRESSED_RGBA_S3TC_DXT5_EXT\n");
		break;
	default:
		free(buffer);
		return 0;
	}

	// Create one OpenGL texture*/
	GLuint tid = 0;
	glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, header.mipMapCount-1); // opengl likes array length of mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // don't forget to enable mipmaping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// load the mipmaps
	uint32_t mipMapCount = header.mipMapCount;
	uint32_t offset = 0;
	uint32_t size = 0;
	uint32_t width = header.width;
	uint32_t height = header.height;
	for (unsigned int i = 0; i < mipMapCount; i++) // && (width || height)
	{
        if(width == 0 || height == 0) // discard any odd mipmaps 0x1 0x2 resolutions
        {
            mipMapCount--;
            continue;
        }

		size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, i, format, width, height, 0, size, buffer + offset);
		offset += size;
		width  /= 2;
		height /= 2;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount-1);
	glBindTexture(GL_TEXTURE_2D, 0);

	free(buffer);

	return tid;
}

