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

    ar['0'] = SHZL_0;
    ar['1'] = SHZL_1;
    ar['2'] = SHZL_2;
    ar['3'] = SHZL_3;
    ar['4'] = SHZL_4;
    ar['5'] = SHZL_5;
    ar['6'] = SHZL_6;
    ar['7'] = SHZL_7;
    ar['8'] = SHZL_8;
    ar['9'] = SHZL_9;

    ar[','] = SHZL_COMMA;

    ar[' '] = SHZL_WHITESPACE;
    ar['\n'] = '\n';
    ar['.'] = 177;

    return ar[c];
}

char szlToStr(unsigned char uc)
{
    char ar[256];

    ar[SHZL_a] = 'a';
    ar[SHZL_b] = 'b';
    ar[SHZL_c] = 'c';
    ar[SHZL_d] = 'd';
    ar[SHZL_e] = 'e';
    ar[SHZL_f] = 'f';
    ar[SHZL_g] = 'g';
    ar[SHZL_h] = 'h';
    ar[SHZL_i] = 'i';
    ar[SHZL_j] = 'j';
    ar[SHZL_k] = 'k';
    ar[SHZL_l] = 'l';
    ar[SHZL_m] = 'm';
    ar[SHZL_n] = 'n';
    ar[SHZL_o] = 'o';
    ar[SHZL_p] = 'p';
    ar[SHZL_q] = 'q';
    ar[SHZL_r] = 'r';
    ar[SHZL_s] = 's';
    ar[SHZL_t] = 't';
    ar[SHZL_u] = 'u';
    ar[SHZL_v] = 'v';
    ar[SHZL_w] = 'w';
    ar[SHZL_x] = 'x';
    ar[SHZL_y] = 'y';
    ar[SHZL_z] = 'z';
    ar[SHZL_A] = 'A';
    ar[SHZL_B] = 'B';
    ar[SHZL_C] = 'C';
    ar[SHZL_D] = 'D';
    ar[SHZL_E] = 'E';
    ar[SHZL_F] = 'F';
    ar[SHZL_G] = 'G';
    ar[SHZL_H] = 'H';
    ar[SHZL_I] = 'I';
    ar[SHZL_J] = 'J';
    ar[SHZL_K] = 'K';
    ar[SHZL_L] = 'L';
    ar[SHZL_M] = 'M';
    ar[SHZL_N] = 'N';
    ar[SHZL_O] = 'O';
    ar[SHZL_P] = 'P';
    ar[SHZL_Q] = 'Q';
    ar[SHZL_R] = 'R';
    ar[SHZL_S] = 'S';
    ar[SHZL_T] = 'T';
    ar[SHZL_U] = 'U';
    ar[SHZL_V] = 'V';
    ar[SHZL_W] = 'W';
    ar[SHZL_X] = 'X';
    ar[SHZL_Y] = 'Y';
    ar[SHZL_Z] = 'Z';

    return ar[uc];
};

unsigned char* convertString(char* p, int sz)
{
    int i = 0;
    unsigned char* test = malloc(sz);
    while (i < sz)
    {
        test[i] = convert(p[i]);
        i++;
    }
    return test;
}
