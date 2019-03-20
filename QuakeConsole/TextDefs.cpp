#include "TextDefs.h"

unsigned char convert(char c)
{
    static unsigned char ar[256];

    memset(ar, 9, 256);

    ar['a'] = SHZL_a;
    ar['b'] = SHZL_b;
    ar['c'] = SHZL_c;
    ar['d'] = SHZL_d;
    ar['e'] = SHZL_e;
    ar['f'] = SHZL_f;
    ar['g'] = SHZL_g;
    ar['h'] = SHZL_h;
    ar['i'] = SHZL_i;
    ar['j'] = SHZL_j;
    ar['k'] = SHZL_k;
    ar['l'] = SHZL_l;
    ar['m'] = SHZL_m;
    ar['n'] = SHZL_n;
    ar['o'] = SHZL_o;
    ar['p'] = SHZL_p;
    ar['q'] = SHZL_q;
    ar['r'] = SHZL_r;
    ar['s'] = SHZL_s;
    ar['t'] = SHZL_t;
    ar['u'] = SHZL_u;
    ar['v'] = SHZL_v;
    ar['w'] = SHZL_w;
    ar['x'] = SHZL_x;
    ar['y'] = SHZL_y;
    ar['z'] = SHZL_z;

    ar['A'] = SHZL_A;
    ar['B'] = SHZL_B;
    ar['C'] = SHZL_C;
    ar['D'] = SHZL_D;
    ar['E'] = SHZL_E;
    ar['F'] = SHZL_F;
    ar['G'] = SHZL_G;
    ar['H'] = SHZL_H;
    ar['I'] = SHZL_I;
    ar['J'] = SHZL_J;
    ar['K'] = SHZL_K;
    ar['L'] = SHZL_L;
    ar['M'] = SHZL_M;
    ar['N'] = SHZL_N;
    ar['O'] = SHZL_O;
    ar['P'] = SHZL_P;
    ar['Q'] = SHZL_Q;
    ar['R'] = SHZL_R;
    ar['S'] = SHZL_S;
    ar['T'] = SHZL_T;
    ar['U'] = SHZL_U;
    ar['V'] = SHZL_V;
    ar['W'] = SHZL_W;
    ar['X'] = SHZL_X;
    ar['Y'] = SHZL_Y;
    ar['Z'] = SHZL_Z;

    ar[' '] = SHZL_WHITESPACE;
    ar['\n'] = '\n';
    ar['.'] = 177;

    return ar[c];
}
