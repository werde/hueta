#include "QuakeConsole.h"
#include "shaders.h"

#include "../__trash.h"
#include "../include/Model.h"

#include "TextDefs.h"

unsigned char convert(char c)
{
    static unsigned char ar[256];

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

    return ar[c];
}

QuakeConsole::QuakeConsole() : _enabled{false}
{
    /// Symbol table
    GLfloat offsetX = 16.0;
    GLfloat offsetY = 20.0;
	GLfloat dim = 256.0;

	char keyIndex = 0;
	for (int x = 0; x < dim; x+=16)
        for(int y = 16; y < 256; y+=20)
    {
        Symbol s;
        s.c = keyIndex;

        s.uv[0].x = x/          (GLfloat)dim;
        s.uv[0].y = y/          (GLfloat)dim;

        s.uv[1].x = (x+offsetX)/(GLfloat)dim;
        s.uv[1].y = y/          (GLfloat)dim;

        s.uv[2].x = x/          (GLfloat)dim;
        s.uv[2].y = (y+offsetY)/(GLfloat)dim;

        s.uv[3].x = (x+offsetX)/(GLfloat)dim;
        s.uv[3].y = (y+offsetY)/(GLfloat)dim;
/*
        s.uv[0].x = x/          (GLfloat)dim;
        s.uv[0].y = (y+offsetY)/(GLfloat)dim;

        s.uv[1].x = (x+offsetX)/(GLfloat)dim;
        s.uv[1].y = (y+offsetY)/(GLfloat)dim;

        s.uv[2].x = x/          (GLfloat)dim;
        s.uv[2].y = y/          (GLfloat)dim;

        s.uv[3].x = (x+offsetX)/(GLfloat)dim;
        s.uv[3].y =  y          /(GLfloat)dim;
*/
        _symbols.push_back(s);
        keyIndex++;

    }

    /// Shader program
	_bsp = glCreateProgram();
    compileShaderProgramm(&_bsp, ".\\billboard.vert", ".\\billboard.frag");

    /// rest
    _tex = loadTex(loadPNG(".\\shizzle.png"));
    //_tex = loadBMP_custom(".\\test.bmp");

    _buf[0] = 116;
    _buf[1] = 53;
    _buf[2] = 52;
    _buf[3] = 65;
    _buf[4] = 11;
    _buf[5] = 29;
    _buf[6] = 64;
    _buf[7] = 52;
    _buf[8] = 52;
    _buf[9] = 41;

    for (int i = 0; i < sizeof(_buf); i++)
    {
        int sIndex = _buf[i];
        calcOGLcoords(i);
        _uv.push_back(_symbols[sIndex].uv[0]);
        _uv.push_back(_symbols[sIndex].uv[1]);
        _uv.push_back(_symbols[sIndex].uv[2]);
        _uv.push_back(_symbols[sIndex].uv[3]);
    }

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);

    _qbc = new QCBackplate();
    _cl = new CommandLine();
}

void QuakeConsole::calcOGLcoords(int i)
{
    vec3 lt, lb, rt, rb;
    float w = 800.0/2;
    float h = 600.0/2;
    float cw= 16.0;
    float ch= 20.0;

    lt.x = -1.0 + (QCXPAD*w + XGAP + i*cw)/w;
    lt.y =  1.0 - (QCYPAD*h + YGAP)/h;
    lt.z =  0.0;

    lb.x = -1.0 + (QCXPAD*w + XGAP + i*cw)/w;
    lb.y =  1.0 - (QCYPAD*h + YGAP + ch)/h;
    lt.z =  0.0;

    rt.x = -1.0 + (QCXPAD*w + XGAP + cw + i*cw)/w;
    rt.y =  1.0 - (QCYPAD*h + YGAP)/h;
    lt.z =  0.0;

    rb.x = -1.0 + (QCXPAD*w + XGAP + cw + i*cw)/w;
    rb.y =  1.0 - (QCYPAD*h + YGAP + ch)/h;
    rb.z =  0.0;
/*
    _v.push_back(lb);
    _v.push_back(rb);
    _v.push_back(lt);
    _v.push_back(rt);
*/
    _v.push_back({lb.x, lb.y, 0.0f});
    _v.push_back({rb.x, rb.y, 0.0f});
    _v.push_back({lt.x,  lt.y, 0.0f});
    _v.push_back({rt.x,  rt.y, 0.0f});
}

void QuakeConsole::draw()
{
    if (!_enabled) return;

    glUseProgram(_bsp);

    _qbc->render(_bsp);
    _cl->render(_bsp);

	GLuint TextureID = glGetUniformLocation(_bsp, "texSampler");

    glActiveTexture(_tex);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, _v.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void QuakeConsole::key(WPARAM wParam, bool zaglav)
{
    if (zaglav)
        _buf[0] = convert(wParam);
    else
        _buf[0] = convert(wParam + 32);

    for (int i = 0; i < sizeof(_buf); i++)
    {
        int sIndex = _buf[i];
        calcOGLcoords(i);
        /*
        _uv.push_back(_symbols[sIndex].uv[0]);
        _uv.push_back(_symbols[sIndex].uv[1]);
        _uv.push_back(_symbols[sIndex].uv[2]);
        _uv.push_back(_symbols[sIndex].uv[3]);
        */
        _uv[4*i+0] = _symbols[sIndex].uv[0];
        _uv[4*i+1] = _symbols[sIndex].uv[1];
        _uv[4*i+2] = _symbols[sIndex].uv[2];
        _uv[4*i+3] = _symbols[sIndex].uv[3];
    }

    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);
}

QuakeConsole::~QuakeConsole()
{
    delete _qbc;
}
