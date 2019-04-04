#include "DDSLoad.h"

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
    bufsize = header.mipMapCount > 1 ? header.pitchOrLinearSize * 2 : header.pitchOrLinearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	fclose(fp);

	unsigned int components  = (header.ddspf.fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;

	switch(header.ddspf.fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
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
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	// load the mipmaps
	uint32_t mipMapCount = header.mipMapCount;
	uint32_t width = header.width;
	uint32_t height = header.height;
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		glCopyTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;https://gist.github.com/tilkinsc/13191c0c1e5d6b25fbe79bbd2288a673
		width  /= 2;
		height /= 2;

		if(width < 1) width = 1;
		if(height < 1) height = 1;
	}

	free(buffer);

	return textureID;
}

