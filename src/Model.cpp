#include "Model.h"

#include "zlib.h"

void debug_is(ImageStruct* is)
{
    printf("bit_depth %d, color type %d, compress. method %d, filter %d, interlace %d \n", is->bit_depth, is->color_type, is->compression_method, is->filter_method, is->interlace_method);
    printf("%dX%d\n", is->width, is->height);
}

int zdecompress(void* dst, const void* src, int szDst, int szSrc)
{
    #define CHUNK 16384
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char* in = src;
    unsigned char* out = (unsigned char*) dst;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK) printf("ret != Z_OK\n");

    int times = 0;
    do
    {
        strm.avail_in = szSrc;
        strm.next_in = in;
        do
        {
            printf("times %d \n", times);
            times++;

            strm.avail_out = szDst;
            strm.next_out = out;

            for (int i = 0; i < szSrc; i++)
            {
                printf("%x ", *((unsigned char*)strm.next_in + i));
            }
            printf("szSrc %d \n", szSrc);

            ret = inflate(&strm, Z_NO_FLUSH);



           if(ret == Z_STREAM_ERROR) printf("Z_STREAM_ERROR\n");  /* state not clobbered */
            switch (ret)
            {
            case Z_NEED_DICT:
                printf("Z_NEED_DICT\n");
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
                printf("Z DATA ERROR\n");
            case Z_MEM_ERROR:
                printf("Z MEM ERROR\n");
                (void)inflateEnd(&strm);
                return ret;
            }

            have = CHUNK - strm.avail_out;
        } while (strm.avail_out == 0);
    } while (ret != Z_STREAM_END);

    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

GLuint decode()
{
    ImageStruct is;
    memset(&is, 0, sizeof(ImageStruct));

    unsigned long szImgDataRead=0;
    unsigned char signature[8];

    FILE* f = fopen(".\\test2.png","rb");
    fread(signature, sizeof(unsigned char), 8, f);
    printf("%u %d %d %d %d %d %d %d\n", signature[0],signature[1],signature[2],signature[3],signature[4],signature[5],signature[6],signature[7]);

    while (1)
    {
        unsigned long length=0;
        unsigned char buf[4];
        fread(&buf, 1, 4, f);
        length = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];

        unsigned char type[4];
        fread(type, 1, 4, f);

        void* data = malloc(length);
        fread(data, 1, length, f);

        void* crc = malloc(4);
        fread(crc, 1, 4, f);

        //memcmp
        printf("%c%c%c%c block of length: %d\n", type[0], type[1], type[2], type[3], length);
        if (memcmp("IEND", type, 4) == 0)
        {
            break;
        }
        else if (memcmp("IHDR", type, 4) == 0)
        {
            unsigned char buf2[4];
            unsigned char buf3[4];

            memcpy(buf2, data, 4);
            is.width = (buf2[0] << 24) | (buf2[1] << 16) | (buf2[2] << 8) | buf2[3];

            memcpy(buf3, data+4, 4);
            is.height = (buf3[0] << 24) | (buf3[1] << 16) | (buf3[2] << 8) | buf3[3];

            memcpy(&(is.bit_depth), data+8, 1);
            memcpy(&(is.color_type), data+9, 1);
            memcpy(&(is.compression_method), data+10, 1);
            memcpy(&(is.filter_method), data+11, 1);
            memcpy(&(is.interlace_method), data+12, 1);

            is.szImgData = is.width*is.height*4 + is.height;
            printf("is.szImgData: %d \n", is.szImgData);
            is.imgData = malloc(is.szImgData);
        }
        else if (memcmp("PLTE", type, 4) == 0)
        {
            //
        }
        else if ((memcmp("IDAT", type, 4) == 0) && (length != 0))
        {
            void* old = is.data;
            is.data = malloc(is.szData + length);
            memcpy(is.data, old, is.szData);

            void* dst = is.data + is.szData;
            memcpy(dst, data, length);
            is.szData += length;
            delete old;
        }
    }

    for (int i = 0; i < is.szData; i++)
    {
        printf("%x ", *((unsigned char*)is.data + i));
    }

    zdecompress(is.imgData, is.data, is.szImgData, is.szData);
    debug_is(&is);

    printf("decompressed data: \n");
    for (int i = 0; i < is.height; i++)
    {
        printf("scanline #%d ", i);
        for (int j = 0; j <= 4*is.width; j++)
        {
            printf("%x ",*((unsigned char*)is.imgData + j + i));
        }
        printf("\n");
    }
    printf("\n");

    void* d = malloc(is.szImgData - is.height);
    void* pd = d;
    void* p = is.imgData;
    const void* readDataPointer = pd;
    for (int i = 0; i < is.height; i++)
    {
        printf("filter method %x\n", *((unsigned char*)p));
        memcpy(pd, (p+1), is.width*4);
        pd += 4*is.width;
        p += (4*is.width + 1);
    }

    printf("after chomping filter byte: \n");
    for (int i = 0; i < is.height; i++)
    {
        printf("scanline #%d ", i);
        for (int j = 0; j < 4*is.width; j++)
        {
            printf("%x ",*((unsigned char*)readDataPointer + j + i*is.width*4));
        }
        printf("\n");
    }
    printf("\n");

    /*
    unsigned char* temp;
    temp = (unsigned char*) d;
    unsigned long tl;
    for (int i = 0; i < (is.szImgData - is.height)/4; i++)
    {
        tl = (temp[0] << 24) | (temp[1] << 16) | (temp[2] << 8) | temp[3];
        memcpy(temp, (void*)&tl, 4);
        temp += 4;
    }
    */

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, is.width, is.height, 0, GL_BGRA, GL_UNSIGNED_BYTE, readDataPointer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	switch (is.filter_method)
	{
    case 0:
        break;
    default:
        break;
	}

	return textureID;
}

GLuint loadBMP_custom(const char * imagepath){

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
		getchar();
		return 0;
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if ( fread(header, 1, 54, file)!=54 ){
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// A BMP files always begins with "BM"
	if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// Make sure this is a 24bpp file
	if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    fclose(file); return 0;}
	if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    fclose(file); return 0;}

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	data = new unsigned char [imageSize];
	fread(data,1,imageSize,file);
	fclose (file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	//delete [] data;

	// Poor filtering, or ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// ... nice trilinear filtering ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	//PFNGLGENERATEMIPMAPPROC glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmap");
	//glGenerateMipmap(GL_TEXTURE_2D);
    printf("********\n");
	// Return the ID of the texture we just created
	return textureID;
}


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

	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;

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

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
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
    v.reserve(100);
    vt.reserve(100);
    vn.reserve(100);
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

        if (strcmp(buf, "v") == 0)
        {
            vec3 vBuf;
            fscanf(f, "%f %f %f\n", &(vBuf.m[0]), &(vBuf.m[1]), &(vBuf.m[2]));
            v.push_back(vBuf);
            continue;
        }

        if (strcmp(buf, "vt") == 0)
        {
            vec2 vBuf;
            fscanf(f, "%f %f\n", &(vBuf.m[0]), &(vBuf.m[1]));
            vBuf.m[1] = 1 - vBuf.m[1];
            vt.push_back(vBuf);
            continue;
        }

        if (strcmp(buf, "vn") == 0)
        {
            vec3 vBuf;
            fscanf(f, "%f %f %f\n", &(vBuf.m[0]), &(vBuf.m[1]), &(vBuf.m[2]));
            vn.push_back(vBuf);
            continue;
        }

        if (strcmp(buf, "f") == 0)
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
            continue;
        }
        char ubuffer[1024];
        fgets(ubuffer, sizeof(ubuffer), f);
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

    for (int i = 0; i < m->v.size(); i++)
    {
        //printf("#%d %f %f %f \n", i, m->v[i].m[0],  m->v[i].m[1],  m->v[i].m[2]);
        //printf("    %f %f    \n", m->vt[i].m[0], m->vt[i].m[1]);
    }

    fclose(f);

    //
    m->tex = loadBMP_custom(".\\t.bmp");
    //m->tex = loadDDS(".\\t.dds");
    return true;
}

Model::~Model()
{
    //dtor
}
