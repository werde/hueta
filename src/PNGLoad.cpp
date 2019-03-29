#include "PNGLoad.h"

///reapply filter 1-4
unsigned char paeth(unsigned char a, unsigned char b, unsigned char c)
{
    int p = a + b - c;
    int pa = abs(p - a);
    int pb = abs(p - b);
    int pc = abs(p - c);

    if ((pa <= pb) && (pa <= pc))
        return a;
    else if (pb <= pc)
        return b;
    else
        return c;
}

void refilter1(unsigned char* targetLine, unsigned char* srcLine, int w, unsigned char bpp)
{
    memcpy(targetLine, srcLine + 1, bpp);
    for (int i = bpp; i < w; i++)
    {
        unsigned char r = *(targetLine + i) + *(targetLine + i - bpp);
        memcpy(targetLine + i, &r, 1);
    }
};

void refilter2(unsigned char* targetLine, unsigned char* srcLine, int w, unsigned char bpp)
{
    for (int i = 0; i < w; i++)
    {
        unsigned char r = *(targetLine + i) + *(srcLine + i);
        memcpy(targetLine + i, &r, 1);
    }
};

void refilter4(unsigned char* targetLine, unsigned char* srcLine, unsigned char* srcPriorLine, int w, unsigned char bpp)
{
    for (int i = 0; i < w; i++)
    {
        unsigned char a, b, c;
        if (i < bpp)
        {
            a = 0;
            c = 0;
        }
        else
        {
            a = *(targetLine + i - bpp);

            if (srcPriorLine == NULL)
                c = 0;
            else
                c = *(srcPriorLine + i - bpp);
        }
        if (srcPriorLine == NULL)
            b = 0;
        else
            b = *(srcPriorLine + i);

        unsigned int r = *(targetLine + i) + paeth(a, b, c);
        unsigned char modR = r%256;
        memcpy(targetLine + i, &modR, 1);
    }
}

void* refilter(void* src, long unsigned int szScanline, long unsigned int height, unsigned char bpp)
{
    long unsigned int width = szScanline - 1;
    void* target = malloc((szScanline - 1)*height);

    for (int i = 0; i < height; i++)
    {
        void* targetLine = malloc(width);
        switch (*((unsigned char*)src + i*szScanline))
        {
        case 0:
            memcpy(targetLine, src + i*szScanline + 1, width);
            break;
        case 1:
            memcpy(targetLine, src + i*szScanline + 1, width);
            refilter1(targetLine, src + i*szScanline, width, bpp);
            break;
        case 2:
            memcpy(targetLine, src + i*szScanline + 1, width);
            refilter2(targetLine, target + (i-1)*width, width, bpp);
            break;
        case 3:
            break;
        case 4:
            memcpy(targetLine, src + i*szScanline + 1, width);
            refilter4(targetLine, src + i*szScanline + 1, target + (i-1)*width, width, bpp);
            break;
        default:
            break;
        };
        memcpy(target+i*width, targetLine, width);

        delete targetLine;
    }

    return target;
}

/// ZLib Decompress
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
            times++;

            strm.avail_out = szDst;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);

           if(ret == Z_STREAM_ERROR) printf("Z_STREAM_ERROR\n");
            switch (ret)
            {
            case Z_NEED_DICT:
                printf("Z_NEED_DICT\n");
                ret = Z_DATA_ERROR;
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

PNGImageStruct* makePNG_IS(const char* path)
{
    PNGImageStruct* is = new PNGImageStruct();
    memset(is, 0, sizeof(PNGImageStruct));

    unsigned long szImgDataRead=0;
    unsigned char signature[8];

    FILE* f = fopen(path, "rb");
    fread(signature, sizeof(unsigned char), 8, f);

    void* imgData = 0;
    unsigned long szImgData = 0;
    void* rawData = 0;
    unsigned long szRawData = 0;

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
        if (memcmp("IEND", type, 4) == 0)
        {
            break;
        }
        else if (memcmp("IHDR", type, 4) == 0)
        {
            unsigned char buf2[4];
            unsigned char buf3[4];

            memcpy(buf2, data, 4);
            is->width = (buf2[0] << 24) | (buf2[1] << 16) | (buf2[2] << 8) | buf2[3];

            memcpy(buf3, data+4, 4);
            is->height = (buf3[0] << 24) | (buf3[1] << 16) | (buf3[2] << 8) | buf3[3];

            memcpy(&(is->bit_depth), data+8, 1);
            memcpy(&(is->color_type), data+9, 1);
            memcpy(&(is->compression_method), data+10, 1);
            memcpy(&(is->filter_method), data+11, 1);
            memcpy(&(is->interlace_method), data+12, 1);

            is->bytes_per_sample = (is->bit_depth == 8) ? 1 : 2;

            switch (is->color_type)
            {
            case 0:
                is->samples_per_pixel = 1;
                break;
            case 2:
                is->samples_per_pixel = 3;
                break;
            case 3:
                is->samples_per_pixel = 1;
                break;
            case 4:
                is->samples_per_pixel = 2;
                break;
            case 6:
                is->samples_per_pixel = 4;
                break;
            }

            is->bytes_per_pixel = is->samples_per_pixel * is->bytes_per_sample;

            szImgData = is->width*is->height*is->bytes_per_pixel + is->height;
            imgData = malloc(szImgData);

            is->szPixelData = is->width*is->height*is->bytes_per_pixel;
        }
        else if (memcmp("PLTE", type, 4) == 0)
        {
            //
        }
        else if ((memcmp("IDAT", type, 4) == 0) && (length != 0))
        {
            void* old = rawData;
            rawData = malloc(szRawData + length);
            memcpy(rawData, old, szRawData);

            void* dst = rawData + szRawData;
            memcpy(dst, data, length);
            szRawData += length;
            if (old) delete old;
        }
    }

    zdecompress(imgData, rawData, szImgData, szRawData);

    void* trg = refilter(imgData, szImgData/is->height, is->height, is->bytes_per_pixel);
    void* trg2 = malloc(is->szPixelData);

    for (int i = 0; i < is->height; i++)
    {
        int o = i*is->bytes_per_pixel*is->width;
        int w = is->bytes_per_pixel*is->width;
        memcpy(trg2 + o, trg + is->szPixelData - o - w, w);
    }

    is->pixelData = trg2;

    return is;
}
