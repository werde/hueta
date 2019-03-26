#include "TextArea.h"

#include "../__trash.h"
#include "../include/Model.h"

TextArea::TextArea(Pos p, Font* f)
    : _f{f}
{
    w = 800; h = 600;
    g = 6;
    fg = g*2.0/(GLfloat)w;

    _pos.x = p.x + fg;
    _pos.y = p.y - fg;
    _pos.h = p.h - 2*fg - f->fFH;
    _pos.w = p.w - 2*fg;

    bottom = _pos.y - _pos.h;
    left = _pos.x;

    symPerStr = (w - 2*g)/_f->fW;
    numStrings = (h/2 - g)/(g + _f->fH);

    /// Buffer
    char* str = "Based on your input, get \na\nrandom alpha numeric string.\n The random string \ngenerator creates a series of \nnumbers and letters \nthat have no pattern.\n These can be helpful for creating security \n codes.\n";
    int len = strlen(str);
    _szBuf = len;
    memcpy(_buf, str, len);

    for (int i = 0; i < _szBuf; i++)
    {
        _buf[i] = convert(_buf[i]);
    }

    fillvv();
}

void TextArea::appendBuffer(char* p, int len)
{
    if (_szBuf + len < TA_MAX_BUF)
    {
        memcpy(_buf + _szBuf, p, len);
        _szBuf += len;
        fillvv();
    }
    else
    {

    }
};

void TextArea::uv(int i)
{
    int sIndex = _buf[i];
    _uv.push_back(_f->symbols[sIndex].uv[0]);
    _uv.push_back(_f->symbols[sIndex].uv[1]);
    _uv.push_back(_f->symbols[sIndex].uv[3]);
    _uv.push_back(_f->symbols[sIndex].uv[2]);
}

void TextArea::ss(int strNum, int xpos)
{
    GLfloat bottomLine = bottom + fg;
    GLfloat leftLine = _pos.x;

    int n2 = strNum;

    GLfloat b = bottomLine + (fg + n2*_f->fFH + n2*fg);
    GLfloat t = bottomLine + (fg + (n2+1)*_f->fFH + n2*fg);
    GLfloat l = leftLine + (fg + xpos*_f->fFW);
    GLfloat r = leftLine + (fg + (xpos+1)*_f->fFW);

    _v.push_back({l, b, 0.0f});
    _v.push_back({r, b, 0.0f});
    _v.push_back({r, t, 0.0f});
    _v.push_back({l, t, 0.0f});
}

void TextArea::fillvv()
{
    _v.clear();
    _uv.clear();

    unsigned char* pEnd = _buf + _szBuf - 1;
    unsigned char* pStart = _buf;

    int curStr = 0;

    unsigned char* p = pEnd - 1;
    while (p >= pStart)
    {
        unsigned char* sEnd = p;

        do
        {
            p--;
        } while ((*p != '\n') && (p >= pStart));

        int i = 0;
        for (unsigned char* tPtr = p + 1; tPtr != sEnd; tPtr++)
        {
            ss(curStr, i);
            uv(tPtr - pStart);
            i++;
        }

        curStr++;
    }

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);
}

void TextArea::render(GLuint sp)
{
	GLuint TextureID = glGetUniformLocation(sp, "texSampler");

    glActiveTexture(_f->tex);
    glBindTexture(GL_TEXTURE_2D,_f->tex);
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glDrawArrays(GL_QUADS, 0, _v.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

TextArea::~TextArea()
{
    //dtor
}
