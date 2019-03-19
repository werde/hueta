#include "QuakeConsole.h"
#include "shaders.h"

#include "../__trash.h"
#include "../include/Model.h"

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
    ar['.'] = 177;

    return ar[c];
}

QuakeConsole::QuakeConsole() : _enabled{false}
{
    _pos = {-1.0f, 1.0f, 2.0f, 1.0f}; // x y width height
    fH = 20; fW = 16;
    w = 800; h = 600;
    g = 10;
    symPerStr = (w - 2*g)/fW; //symbold per string
    numStrings = (h/2 - g)/(g + fH);

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
    _tex = loadTex(loadPNG(".\\shizzle_i.png"));
    //_tex = loadBMP_custom(".\\test.bmp");

    unsigned char* str = "Based on your input, get a random alpha numeric string.\n The random string generator creates a series of numbers and letters that have no pattern.\n These can be helpful for creating security codes.\n";
    int len = strlen(str);
    sz_Buf = len;
    memcpy(_buf, str, len);

    for (int i = 0; i < sz_Buf; i++)
    {
        _buf[i] = convert(_buf[i]);
    }

    for (int i = 0; i < sz_Buf; i++)
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

    _qbc = new QCBackplate(_pos);
    _cl = new CommandLine();

    printf("%s %s %d \n", _buf, str, len);
}

void pv(vec3 v)
{
    printf("%f %f %f \n", v.x, v.y, v.z);
}

void QuakeConsole::TextArea()
{
    unsigned char* pEnd;
    pEnd = _buf + sz_Buf;
    unsigned char pStart = _buf;

    int curStr = 0;

    while (*pEnd != )

}

void QuakeConsole::calcOGLcoords(int i)
{
    vec3 lt, lb, rt, rb;
    GLfloat fFH = fH*2.0/(GLfloat)h;
    GLfloat fFW = fW*2.0/(GLfloat)w;
    GLfloat fg = 2.0*g/(GLfloat)h;

    int n = i/symPerStr;    //string number
    i = i - n*symPerStr;    //position in string

    lt.x = -1.0 + (fg + fFW*i);
    lt.y =  1.0 - (fg + fFH*n + fg*n) ;
    lt.z =  0.0;

    lb.x = -1.0 + (fg + fFW*i);
    lb.y =  1.0 - (fg + fFH*(n + 1) + fg*n);
    lb.z =  0.0;

    rt.x = -1.0 + (fg + fFW*(i + 1));
    rt.y =  1.0 - (fg + fFH*n + fg*n);
    rt.z =  0.0;

    rb.x = -1.0 + (fg + fFW*(i + 1));
    rb.y =  1.0 - (fg + fFH*(n + 1) + fg*n);
    rb.z =  0.0;

    // from bottom line
    int numRows = 1 + sz_Buf/symPerStr;
    int  n2 = numRows - n; //numRowFromBottom

    GLfloat bottomLine = _pos.y - _pos.h;
    GLfloat leftLine = _pos.x;

    GLfloat b = bottomLine + (fg + n2*fFH + n2*fg);
    GLfloat t = bottomLine + (fg + (n2+1)*fFH + n2*fg);
    GLfloat l = leftLine + (fg + i*fFW);
    GLfloat r = leftLine + (fg + (i+1)*fFW);

    _v.push_back({l, b, 0.0f});
    _v.push_back({r, b, 0.0f});
    _v.push_back({l, t, 0.0f});
    _v.push_back({r, t, 0.0f});

/*
    _v.push_back(lb);
    _v.push_back(rb);
    _v.push_back(lt);
    _v.push_back(rt);
*/
/*
    _v.push_back({lb.x, lb.y, 0.0f});
    _v.push_back({rb.x, rb.y, 0.0f});
    _v.push_back({lt.x,  lt.y, 0.0f});
    _v.push_back({rt.x,  rt.y, 0.0f});
*/
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
