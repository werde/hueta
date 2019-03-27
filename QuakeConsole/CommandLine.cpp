#include "CommandLine.h"

#include "../src/PNGLoad.h"
#include "../__trash.h"
#include "../src/Model.h"
#include "TextArea.h"

CommandLine::CommandLine(Pos p, Font* f)
    : _f{f}, _curPos{0}, _szBuf{0}
{
    w = 800; h = 600;
    g = 6;
    fg = g*2.0/(GLfloat)w;

    _pos.x = p.x + fg;
    _pos.y = p.y - p.h + fg;
    _pos.h = 2*fg + f->fFH;
    _pos.w = p.w - 2*fg;
    bottomLine = _pos.y;
    leftLine = _pos.x;

    memset(_buf, 137, 10);
    _szBuf=10;

    fillvv();
}

void CommandLine::right()
{
    if (_curPos >= CL_MAX_BUF - 1) return;
    if (_curPos >= _szBuf) return;
    _curPos++;

    refillvv();
}

void CommandLine::left()
{
    if (_curPos < 1) return;
    _curPos--;

    refillvv();
}

void CommandLine::enter(TextArea* ta)
{
    if(_szBuf < 1) return;

    ta->appendBuffer(_buf, _szBuf);
    _szBuf = 0;
    _curPos = 0;

    refillvv();
}

void CommandLine::delet()
{
    if (_szBuf < 1) return;
    if (_curPos >= _szBuf) return;

    memcpy(_buf + _curPos, _buf + _curPos + 1, _szBuf - _curPos - 1);
    _szBuf--;

    refillvv();
}

void CommandLine::backspace()
{
    if (_curPos < 1) return;

    _curPos--;
    memcpy(_buf + _curPos, _buf + _curPos + 1, _szBuf - _curPos - 1);

    _szBuf--;
    refillvv();
}

void CommandLine::addLetter(char l)
{
    if (_szBuf >= CL_MAX_BUF)
    {
        memset(_buf + _curPos, l, 1);
        refillvv();
        return;
    }

    char* temp  = malloc(_szBuf - _curPos);
    memcpy(temp, _buf  + _curPos, _szBuf - _curPos);
    memset(_buf + _curPos, l, 1);
    memcpy(_buf + _curPos + 1, temp, _szBuf - _curPos);

    _szBuf++;
    right();
    refillvv();

    ///
    delete temp;
}

void CommandLine::fillvv()
{
    unsigned char* pEnd = _buf + _szBuf;
    unsigned char* pStart = _buf;

    unsigned char* p = _buf;
    int i = 0;
    while (p < pEnd)
    {

        GLfloat b = bottomLine;
        GLfloat t = bottomLine + fg + _f->fFH;
        GLfloat l = leftLine + (fg + i*_f->fFW);
        GLfloat r = leftLine + (fg + (i+1)*_f->fFW);

        _v.push_back({l, b, 0.0f});
        _v.push_back({r, b, 0.0f});
        _v.push_back({r, t, 0.0f});
        _v.push_back({l, t, 0.0f});

        int sIndex = _buf[i];
        _uv.push_back(_f->symbols[sIndex].uv[0]);
        _uv.push_back(_f->symbols[sIndex].uv[1]);
        _uv.push_back(_f->symbols[sIndex].uv[3]);
        _uv.push_back(_f->symbols[sIndex].uv[2]);

        i++;
        p++;
    }

    GLfloat b2 = bottomLine - 0.03;
    GLfloat t2 = bottomLine + fg + _f->fFH;
    GLfloat l2 = leftLine + (fg + _curPos*_f->fFW);
    GLfloat r2 = leftLine + (fg + (_curPos + 1)*_f->fFW);

    _curV.push_back({l2, b2, 0.0f});
    _curV.push_back({r2, b2, 0.0f});
    _curV.push_back({r2, t2, 0.0f});
    _curV.push_back({l2, t2, 0.0f});

    int sIndex2 = 186;
    _curUV.push_back(_f->symbols[sIndex2].uv[0]);
    _curUV.push_back(_f->symbols[sIndex2].uv[1]);
    _curUV.push_back(_f->symbols[sIndex2].uv[3]);
    _curUV.push_back(_f->symbols[sIndex2].uv[2]);


    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_cvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _cvbo);
    glBufferData(GL_ARRAY_BUFFER, _curV.size()*sizeof(vec3), &(_curV[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_cuvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _cuvbo);
    glBufferData(GL_ARRAY_BUFFER, _curUV.size()*sizeof(vec2), &(_curUV[0]), GL_DYNAMIC_DRAW);
}

void CommandLine::refillvv()
{
    _v.clear();
    _uv.clear();
    _curV.clear();
    _curUV.clear();

    fillvv();
}

void CommandLine::render(GLuint sp)
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
    ///
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, _cvbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glBindBuffer(GL_ARRAY_BUFFER, _cuvbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glDrawArrays(GL_QUADS, 0, _curV.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

CommandLine::~CommandLine()
{
}
