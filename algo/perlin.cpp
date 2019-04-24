#include "perlin.h"

int permutation[256] =
{   151,160,137,91,90,15,                                                             // Hash lookup table as defined by Ken Perlin.  This is a randomly
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,    // arranged array of all numbers from 0-255 inclusive.
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

double lerp(float a0, float a1, float w)
{
    return (double)(1.0f - w)*a0 + w*a1;
}

double fade(double t)
{

    return t * t * t * (t * (t * 6 - 15) + 10);
}

/*
float dotGridGradient(int ix, int iy, float x, float y, vec2* vectors)
{
    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx*vectors[iy][ix].m[0] + dy*vectors[iy][ix].m[1]);
}
*/

double grad(int h, double x, double y)
{
    switch(h & 0xF)
    {
        case 0x0: return  x + y;
        case 0x1: return -x + y;
        case 0x2: return  x - y;
        case 0x3: return -x - y;
        case 0x4: return  x + y;
        case 0x5: return -x + y;
        case 0x6: return  x - y;
        case 0x7: return -x - y;
        case 0x8: return  x + y;
        case 0x9: return -x + y;
        case 0xA: return  x - y;
        case 0xB: return -x - y;
        case 0xC: return  x + y;
        case 0xD: return -x + y;
        case 0xE: return  x - y;
        case 0xF: return -x - y;
        default: return 0; // never happens
    }
}


double perlin(float x, float y)
{
    int p[512];
    for(int i=0;i<512;i++) {
        p[i] = permutation[i%256];
    }

    int ix = (int)floor(x) & 255;
    int iy = (int)floor(y) & 255;

    double dx = x - (int)floor(x);
    double dy = y - (int)floor(y);
    //int tx = (int)floor(x)/256;
    //int ty = (int)floor(y)/256;
    //double dx = (x - tx*256)/256.0;
    //double dy = (y - ty*256)/256.0;

    double u = fade(dx);
    double v = fade(dy);

    int aa, ab, ba, bb;
    aa = p[p[ix    ] + iy    ];
    ab = p[p[ix    ] + iy + 1];
    ba = p[p[ix + 1] + iy    ];
    bb = p[p[ix + 1] + iy + 1];

    double x1, x2, y1, y2;
    x1 = lerp(  grad (aa, dx  , dy),           // The gradient function calculates the dot product between a pseudorandom
                grad (ba, dx-1, dy),             // gradient vector and the vector from the input coordinate to the 8
                u);                                     // surrounding points in its unit cube.
    x2 = lerp(  grad (ab, dx  , dy-1),           // This is all then lerped together as a sort of weighted average based on the faded (u,v,w)
                grad (bb, dx-1, dy-1),             // values we made earlier.
                u);
    y1 = lerp(x1, x2, v);

    /*printf("X - %f, Y - %f\n", x, y);
    printf("ix - %d, iy - %d\n", ix, iy);
    printf("dx - %f, dy - %f, u - %f, v - %f\n", dx, dy, u, v);
    printf ("%d %d %d %d\n", aa, ab, ba, bb);
    printf("%f %f %f\n", x1, x2, y1);*/

    return y1;
}

double octavePerlin(float x, float y)
{
    double r=0.0;
    double a = 1.0;
    double freq = 1.0;
    double persistence = 0.7;
    double maxValue = 0.0;

    int imax = 2;
    //if ((x < 25.0) && (y < 25.0)) imax = 2;

    for (int i = 0; i < imax; i++)
    {
        r += perlin(x * freq, y * freq) * a;
        maxValue += a;

        a *= persistence;
        freq *= 2;
    }

    return r/maxValue;
}

double* makeArray(int w)
{
    int sz = w*w;
    double* ar = malloc(sz*sizeof(double));
    srand(time(NULL));

    for (int i = 0; i < sz; i++)
    {
        ar[i] = ((double) rand() / (RAND_MAX));
    }

    return ar;
}

void smoothArray(double* a, int w, int oct)
{
    int sp   = 1 << oct;
    double sf = 1.0f / sp;
    printf("w=%d %d %x\n", w, sp, a);

    for (int i = 0; i < w; i++)
    {
        int i1 = (i/sp)*sp;
        int i2 = (i1 + sp)%w;           ///%w - for wrap around
        double blend_i = (i - i1)*sf;

        for (int j = 0; j < w; j++)
        {
            int j1 = (j/sp)*sp;
            int j2 = (j1 + sp)%w;           ///%w - for wrap around
            double blend_j = (j - j1)*sf;

            double x1 = lerp(a[i1*w + j1], a[i2*w + j1], blend_i);
            double x2 = lerp(a[i1*w + j2], a[i2*w + j2], blend_i);
            a[i*(w-1) + j] = lerp(a[i1*w + j2], a[i2*w + j2], blend_i);
        }
    }
}

double* tperlin(int w, int oct)
{
    int sz = w*w;
    double* ar = malloc(sz*sizeof(double));
    double* octaves[oct];
    srand(time(NULL));

    for (int i = 0; i < oct; i++)
    {
        octaves[i] = makeArray(w);
    }

    for (int i = 1; i < oct; i++)
    {
        printf("#%d %x\n", i, octaves[i]);
        smoothArray(octaves[i], w, i);
    }

    float amp = 0.01;
    for (int i = 0; i < sz; i++)
    {
        ar[i] = 0;
        amp = 1.0;
        for (int o = 0; o < oct; o++)
        {
            ar[i] += amp * (*(octaves[o] + i));
            amp *= 2;
        }
    }

    return ar;
}

