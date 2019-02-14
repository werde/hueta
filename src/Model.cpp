#include "Model.h"
GLuint loadDDS(const char * imagepath)
{
	unsigned char header[124];

	FILE *fp;

	/* try to open the file */
	fp = fopen(imagepath, "rb");
	if (fp == NULL){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
		return 0;
	}

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp);

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);


	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	//unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int components  = 3;
	unsigned int format;
	/*
	switch(fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}
    */
    format = 33779;
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	//unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int blockSize = 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		glCopyTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;
		width  /= 2;
		height /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if(width < 1) width = 1;
		if(height < 1) height = 1;

	}

	free(buffer);

	return textureID;
}

Model::Model()
{
    tex = 0;
    v.reserve(10);
    vt.reserve(10);
    vn.reserve(10);
}

bool Model::LoadObj(Model* m)
{
    std::string path = ".\\t.obj";

    FILE * f = fopen(path.c_str(), "rb");
    if( f == NULL ){
        printf("Impossible to open the file !\n");
        printf("%s\n", path.c_str());
        return false;
    }


    printf("loadobj end !\n");

    std::vector<vec3> v;
    std::vector<vec2> vt;
    std::vector<vec3> vn;

    std::vector<GLuint> vi;
    std::vector<GLuint> uvi;
    std::vector<GLuint> ni;

    while (1)
    {
        char buf[256];
        int res = fscanf(f, "%s", buf);

        if (res == EOF)
            break;

        if (!strcmp(buf, "v"))
        {
            vec3 vBuf;
            fscanf(f, "%f %f %f\n", &(vBuf.m[0]), &(vBuf.m[1]), &(vBuf.m[2]));
            v.push_back(vBuf);
            continue;
        }

        if (!strcmp(buf, "vt"))
        {
            vec2 vBuf;
            fscanf(f, "%f %f\n", &(vBuf.m[0]), &(vBuf.m[1]));
            vt.push_back(vBuf);
            continue;
        }

        if (!strcmp(buf, "vn"))
        {
            vec3 vBuf;
            fscanf(f, "%f %f %f\n", &(vBuf.m[0]), &(vBuf.m[1]), &(vBuf.m[2]));
            vn.push_back(vBuf);
            continue;
        }

        if (!strcmp(buf, "f"))
        {
            GLuint viBuf[3], uviBuf[3], niBuf[3];
            fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &viBuf[0], &uviBuf[0], &niBuf[0],
                                                        &viBuf[1], &uviBuf[1], &niBuf[1],
                                                        &viBuf[2], &uviBuf[2], &niBuf[2]);

            vi.push_back(viBuf[0]);
            vi.push_back(viBuf[1]);
            vi.push_back(viBuf[2]);
            uvi.push_back(uviBuf[0]);
            uvi.push_back(uviBuf[1]);
            uvi.push_back(uviBuf[2]);
            ni.push_back(niBuf[0]);
            ni.push_back(niBuf[1]);
            ni.push_back(niBuf[2]);
        }
    }

	// For each vertex of each triangle
    for (unsigned int i = 0; i < vi.size(); i++ )
    {

        // Get the indices of its attributes
        unsigned int vit = vi[i];
        unsigned int uvit = uvi[i];
        unsigned int nit = ni[i];

        // Get the attributes thanks to the index
        vec3 vertex = v[vit-1];
        vec2 uv = vt[uvit-1];
        vec3 normal = vn[nit-1];

        // Put the attributes in buffers
        m->v.push_back(vertex);
        m->vt.push_back(uv);
        m->vn.push_back(normal);
    }

    fclose(f);

    //
    m->tex = loadDDS(".\\t.dds");
    return true;
}

Model::~Model()
{
    //dtor
}
