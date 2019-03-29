#ifndef TEXTDEFS_H_INCLUDED
#define TEXTDEFS_H_INCLUDED

#include <stdio.h>

#define SHZL_a 17
#define SHZL_b 29
#define SHZL_c 41
#define SHZL_d 53
#define SHZL_e 65
#define SHZL_f 77
#define SHZL_g 89
#define SHZL_h 101
#define SHZL_i 113
#define SHZL_j 125
#define SHZL_k 137
#define SHZL_l 149
#define SHZL_m 161
#define SHZL_n 173
#define SHZL_o 185
#define SHZL_p 4
#define SHZL_q 16
#define SHZL_r 28
#define SHZL_s 40
#define SHZL_t 52
#define SHZL_u 64
#define SHZL_v 76
#define SHZL_w 88
#define SHZL_x 100
#define SHZL_y 112
#define SHZL_z 124

#define SHZL_A 19
#define SHZL_B 31
#define SHZL_C 43
#define SHZL_D 55
#define SHZL_E 67
#define SHZL_F 79
#define SHZL_G 91
#define SHZL_H 103
#define SHZL_I 115
#define SHZL_J 127
#define SHZL_K 139
#define SHZL_L 151
#define SHZL_M 163
#define SHZL_N 175
#define SHZL_O 187
#define SHZL_P 6
#define SHZL_Q 18
#define SHZL_R 30
#define SHZL_S 42
#define SHZL_T 54
#define SHZL_U 66
#define SHZL_V 78
#define SHZL_W 90
#define SHZL_X 102
#define SHZL_Y 114
#define SHZL_Z 126

#define SHZL_0 8
#define SHZL_1 20
#define SHZL_2 32
#define SHZL_3 44
#define SHZL_4 56
#define SHZL_5 68
#define SHZL_6 80
#define SHZL_7 92
#define SHZL_8 104
#define SHZL_9 116

#define SHZL_WHITESPACE 9
#define SHZL_COMMA 153

#include "../mat.h"

typedef struct
{
    GLfloat x, y, w, h;
} Pos;

typedef struct
{
    char c;
    vec2 uv[4];
} Symbol;

unsigned char convert(char c);
char szlToStr(unsigned char uc);
unsigned char* convertString(char* p, int sz);

#endif // TEXTDEFS_H_INCLUDED
